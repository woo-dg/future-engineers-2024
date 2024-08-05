

#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <MPU6050_light.h>
#include "SharpIR.h"

// Define model and input pin:
#define IRPin A0
#define model 1080

// Create variable to store the distance:
int distance_cm;

MPU6050 mpu(Wire);
unsigned long timer = 0;


  int dA = 0;
  int dist = 0;
Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);

int pos = 90;    // variable to store the servo position

int left_tick = 0;

bool left_flag = HIGH;

#define mlp 3
#define mld 4   // motor port 3
#define mlf 2

SharpIR mySensor = SharpIR(IRPin, model);
88
void setup() {
  Serial.begin(9600);
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); 
   if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);  
    Wire.begin();
  
  }

  // put your setup code here, to run once:
   myservo.attach(9); 
   myservo.write(90);
Serial.begin(9600);
pinMode(mlp, OUTPUT); 
pinMode(mld, OUTPUT); 

//
attachInterrupt(digitalPinToInterrupt(mlf), left_wheel_pulse, RISING);
 myservo.write(90);
// 
//    analogWrite(mlp, 255 ); 
//    digitalWrite(mld,true);
// delay(5000);

//
//for (int i = 0; i<4;i++){
//
//move_degree(true, 50,4500,0);
//move_degree(true,50,1600,90);
//}

}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;
  mpu.update();
  dist = mySensor.distance();
  
  int str = map(mpu.getAngleZ()-dA,30,-30,35,135);

    myservo.write(str);
    tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);
    analogWrite(mlp, 255 ); 
    digitalWrite(mld,true);
    if (lux <= 11){
      dA += 90;
      while (mpu.getAngleZ() < dA-3){
        mpu.update();
          Serial.println(mpu.getAngleZ());
        myservo.write(125);
        analogWrite(mlp, 50 ); 
        digitalWrite(mld,true);
      }
      
        analogWrite(mlp, 100 ); 
      delay(100);
        

      
    }
    

//  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.println(mpu.getAngleZ());
  Serial.println(dA);
//  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
//  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
//  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
//  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
//  Serial.println(" ");
}



void move_degree( bool dir, int pace, float dis, int steer){
  left_tick = 0;
  int str = map(steer,-100,100,35,135);
    myservo.write(str);
    left_flag = dir;
    analogWrite(mlp, pace ); 
    digitalWrite(mld,left_flag);
  while( abs(left_tick)<dis*0.75)
  {
    
//    continue;
//    Serial.println("moving");
delayMicroseconds(1);
    Serial.println(left_tick);
    
  }
  analogWrite(mlp, 255); 
    digitalWrite(mld, !left_flag);
    delay(10);
    left_tick=0;
  
}




void left_wheel_pulse() {
   
  // Read the value for the encoder for the right wheelanalogWrite(mlp, pace ); 
    digitalWrite(mld,left_flag);

 if (left_flag){
  left_tick++;
} 
else{
   left_tick--;
}
}
