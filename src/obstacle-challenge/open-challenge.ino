#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <MPU6050_light.h>
#include "SharpIR.h"

// Define model and input pin:
#define model 1080
const int buttonPin = 5;  // Pin for the button

MPU6050 mpu(Wire);  // Initialize MPU6050 sensor
unsigned long timer = 0;  // Timer for MPU6050 updates

// Variables for different sensor readings and control states
int dA = 0;
int bc = 0;
int str = 0;
int oc = 0;
int distR = 0;
int distL = 0;
bool o = false;
bool bl = false;

Servo myservo;  // Create Servo object to control a servo

// Initialize TCS34725 color sensor with specific integration time and gain
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_1X);

int pos = 90;  // Variable to store the servo position
int left_tick = 0;  // Counter for left wheel encoder ticks
bool left_flag = HIGH;  // Direction flag for left wheel

// Define motor control pins
#define mlp 3
#define mld 4   // Motor port 3
#define mlf 2

// Initialize Sharp IR sensors for distance measurement
SharpIR sensorR(A2, 20150);
SharpIR sensorL(A0, 20150);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize MPU6050 and calculate offsets
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {
    // Stop everything if the MPU6050 could not connect
  }
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();  // Calculate MPU6050 offsets
  
  // Initialize TCS34725 color sensor
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Initialize servo and motor control pins
  myservo.attach(9);
  myservo.write(85);
  pinMode(mlp, OUTPUT);
  pinMode(mld, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(mlf), left_wheel_pulse, RISING);

  // Setup button pin and wait for button press
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  int buttonState = digitalRead(buttonPin);
  while (buttonState == 1) {
    buttonState = digitalRead(buttonPin);
  }
  delay(200);
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  // Read raw color data from the TCS34725 sensor
  tcs.getRawData(&r, &g, &b, &c);
  mpu.update();  // Update MPU6050 sensor readings
  
  // Measure distances using the Sharp IR sensors
  distR = sensorR.distance();
  Serial.print("DistR: ");
  Serial.print(distR);
  
  distL = sensorL.distance();
  Serial.print("DistL: ");
  Serial.println(distL);
  
  // Calculate color temperature and lux
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
  
  // Map the Z-axis angle to a steering angle and adjust if necessary
  str = map(mpu.getAngleZ() - dA, 30, -30, 40, 130);
  if (str > 130) {
    str = 130;
  } else if (str < 40) {
    str = 40;
  }
  myservo.write(str);  // Control the servo for steering
  
  // Stop the motor temporarily
  analogWrite(mlp, 0);
  digitalWrite(mld, true);
  
  // Logic for handling obstacle detection and avoidance based on lux and color readings
  if (lux < 6 && r < 10) {
    if (o == false) {
      dA = dA + 90;
      bl = true;
      bc++;
      while (mpu.getAngleZ() < dA - 15) {
        mpu.update();
        myservo.write(115);
        analogWrite(mlp, 0);
        digitalWrite(mld, true);
      }
    }
  }
  
  if (lux < 6 && r > 15) {
    if (bl == false) {
      dA = dA - 90;
      o = true;
      oc++;
      while (mpu.getAngleZ() > dA + 15) {
        mpu.update();
        myservo.write(55);
        analogWrite(mlp, 0);
        digitalWrite(mld, true);
      }
    }
  }
  
  // Adjust steering based on distance readings
  if (bl) {
    mpu.update();
    str = map(mpu.getAngleZ() - dA, 30, -30, 40, 130);
    myservo.write(str);
    distR = sensorR.distance();
    Serial.print("DistR: ");
    Serial.println(distR);
    
    if (distR > 35) {
      myservo.write(75);
    } else if (distR < 25) {
      myservo.write(95);
    }
  }
  
  if (o) {
    mpu.update();
    str = map(mpu.getAngleZ() - dA, 30, -30, 40, 130);
    myservo.write(str);
    distL = sensorL.distance();
    Serial.print("DistL: ");
    Serial.println(distL);
    
    if (distL > 35) {
      myservo.write(95);
    } else if (distL < 25) {
      myservo.write(75);
    }
  }
  
  // End loop if a certain condition is met (e.g., number of turns)
  if (oc == 12 || bc == 12) {
    move_degree(true, 50, 1600, 0);
    analogWrite(mlp, 255);
    digitalWrite(mld, false);
    delay(100000);  // Consider reducing or handling this delay differently
  }
}

// Function to move the robot a certain distance with a specific speed and steering angle
void move_degree(bool dir, int pace, float dis, int steer) {
  left_tick = 0;
  int str = map(steer, -100, 100, 35, 135);
  myservo.write(str);
  left_flag = dir;
  analogWrite(mlp, pace);
  digitalWrite(mld, left_flag);
  
  while (abs(left_tick) < dis * 0.75) {
    delayMicroseconds(1);
    Serial.println(left_tick);
  }
  
  analogWrite(mlp, 255);
  digitalWrite(mld, !left_flag);
  delay(10);
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
