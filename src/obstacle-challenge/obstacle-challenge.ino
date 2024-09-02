#include <MPU6050_light.h>
#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Pixy2.h>
#include <SharpIR.h>

Pixy2 pixy;

// Define model and input pin
const int buttonPin = 5;
MPU6050 mpu(Wire);  // Initialize MPU6050 sensor
unsigned long t = 0;

// Variables for various sensor readings and control states
int dA = 0;
int str = 0;
int distR = 0;
int distL = 0;
int sig, x, y;
int dG = 0, dR = 0, dP = 0, dD = 0;
int pr = 0;
bool o = false;
bool bl = false;
bool p = false;
int bc = 0, oc = 0;
Servo myservo;  // Create Servo object to control a servo motor

// Initialize TCS34725 color sensor with specific integration time and gain
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X);

int left_tick = 0;
bool left_flag = HIGH;

// Define motor control pins
#define mlp 3
#define mld 4
#define mlf 2

// Initialize Sharp IR sensors
SharpIR sensor1(A1, 20150);
SharpIR sensor2(A2, 20150);
SharpIR sensor3(A0, 20150);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize MPU6050 and calculate offsets
  byte status = mpu.begin();
  if (status != 0) {
    while (true) {}  // Stop if MPU6050 fails to initialize
  }
  mpu.calcOffsets();
  
  // Initialize color sensor
  if (!tcs.begin()) {
    Serial.println("No TCS34725 found ... check your connections");
    while (true) {}
  }
  
  // Initialize servo and motor control pins
  myservo.attach(9);
  myservo.write(85);
  pinMode(mlp, OUTPUT);
  pinMode(mld, OUTPUT);
  pixy.init();
  
  // Set up left wheel encoder interrupt
  attachInterrupt(digitalPinToInterrupt(mlf), left_wheel_pulse, RISING);

  // Wait for button press to start
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  while (digitalRead(buttonPin) == 1) {}
  delay(1000);
}

void loop(void) {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  mpu.update();
  
  int distF = sensor1.distance();
  distR = sensor2.distance();
  distL = sensor3.distance();
  
  // Steering control based on gyro readings
  str = map(mpu.getAngleZ() - dA - dG + dR - dP + dD, 30, -30, 35, 135);
  str = constrain(str, 45, 125);
  myservo.write(str);
  analogWrite(mlp, 0);
  digitalWrite(mld, true);

  // Obstacle and color detection logic
  if (c < 10 && r < 15) {
    // Handle specific conditions for red color detection and turning
    if (!o) {
      bl = true;
      bc++;
      while (true) {
        mpu.update();
        distF = sensor1.distance();
        if (distF < 25) {
          distR = sensor2.distance();
          analogWrite(mlp, 255);
          digitalWrite(mld, true);
          break;
        }
      }
      dA += 89;
      myservo.write(35);
      move_str(false, 100, 1600);
      myservo.write(85);
      if (sensor2.distance() > 35) {
        move_str(false, 0, 200);
      }
      move_str(true, 0, 200);
    }
  } else if (g > 1024 && b > 1024 && c < 100) {
    // Handle specific conditions for blue color detection and turning
    if (!bl) {
      o = true;
      oc++;
      while (true) {
        mpu.update();
        distF = sensor1.distance();
        if (distF < 25) {
          distL = sensor3.distance();
          analogWrite(mlp, 255);
          digitalWrite(mld, true);
          break;
        }
      }
      dA -= 88;
      myservo.write(130);
      move_str(false, 0, 1800);
      myservo.write(85);
      if (distL < 150) {
        move_str(true, 0, 400);
      }
      move_str(true, 0, 50);
    }
  }

  // Pixy2 block detection logic
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    sig = pixy.ccc.blocks[0].m_signature;
    x = pixy.ccc.blocks[0].m_x;
    y = pixy.ccc.blocks[0].m_y;
    
    // Handle different signatures detected by Pixy2
    if (sig == 1 && !p) {
      dG = 0;
      if (y > 35) {
        t = millis();
        pr = 1;
        if (x > 70) {
          dR = 75;
        }
      } else if (x < 70) {
        dR = 0;
      } else {
        dR = 0;
        e = 40;
      }
    } else if (sig == 2 && !p) {
      dR = 0;
      if (y > 75) {
        t = millis();
        pr = 2;
        if (x < 280) {
          dG = 75;
        }
      } else if (x > 280) {
        dG = 0;
      } else if (y > 200) {
        dG = 0;
      } else {
        dG = 0;
        e = 40;
      }
    } else if (sig == 3 && !p) {
      if (bl && y > 65 && x > 120) {
        dP = 75;
      } else if (x < 100) {
        dP = 0;
      }
      if (o && y > 65 && x > 150) {
        dP = -75;
      } else if (y > 200) {
        dP = 0;
      }
    }
  }

  // Wall detection and adjustment based on IR sensor readings
  distR = sensor2.distance();
  distL = sensor3.distance();
  if (bl) {
    if (distL < 30 && distR > 30) {
      dD = 30;
    } else if (distR < 30 && distL > 30) {
      dD = -30;
    } else {
      dD = 0;
    }
  } else if (o) {
    if (distR < 30 && distL > 30) {
      dD = 20;
    } else if (distL < 30 && distR > 30) {
      dD = -20;
    } else {
      dD = 0;
    }
  }

  // Handling turns and movement based on obstacle detection
  int rev = 8;
  if (oc == rev || bc == rev) {
    if (pr == 1 && o && oc == rev) {
      move_str(true, 0, 1400);
      myservo.write(130);
      move_str(false, 0, 2200);
      myservo.write(65);
      move_str(true, 0, 1300);
      dA = -8783;
      bl = true;
      o = false;
      oc++;
      bc = oc;
    } else if (pr == 1 && bl && bc == rev) {
      move_str(true, 0, 2000);
      myservo.write(40);
      move_str(false, 0, 2200);
      myservo.write(105);
      move_str(true, 0, 1300);
      dA = 783;
      o = true;
      bl = false;
      bc++;
      oc = bc;
    }
  }

  // Parking logic if necessary
  if (oc > 11 || bc > 11) {
    int tick = 0;
    while (tick++ < 1000) {
      mpu.update();
      str = map(mpu.getAngleZ() - dA, 30, -30, 35, 135);
      str = constrain(str, 40, 130);
      myservo.write(str);
      analogWrite(mlp, 0);
      digitalWrite(mld, true);
    }
    analogWrite(mlp, 255);
    digitalWrite(mld, true);
    delay(2000);
    p = true;
  }
}

// Function to move the robot straight for a certain distance
void move_str(bool dir, int pace, float dis) {
  left_tick = 0;
  left_flag = dir;
  analogWrite(mlp, pace);
  digitalWrite(mld, left_flag);
  while (abs(left_tick) < dis * 0.75) {
    mpu.update();
    delayMicroseconds(1);
  }
  analogWrite(mlp, 255);
  digitalWrite(mld, !left_flag);
  left_tick = 0;
}

// Interrupt service routine for left wheel encoder pulse
void left_wheel_pulse() {
  if (left_flag) {
    left_tick++;
  } else {
    left_tick--;
  }
}
