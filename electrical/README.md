Electrical
====

This directory consists of schematic diagrams demonstrating the connections between different components as well as datasheets for the components. It also consists of the reasoning behind the choice of components.

## Parts Explanation

| Part Name | Explanation | Image | Datasheet |
| ----------- | ----------- | ----------- | ----------- |
| 1.5V Rechargeable Lithium Ion Battery | We are using this battery to power all of our electronics as it is compact and easy to get. They are also efficient for us as they are rechargeable and do not have to be replaced. | ![image](https://drive.google.com/uc?id=1UbblTDuwNBWmHWpU6mRvyXTKtvxOBNcG) | [Battery Info](https://drive.google.com/file/d/1sINeE1pQsb4mYleB1K3RjQIi_3ilcRdc/view?usp=sharing) |
| DC 6V Micro Gear Box Speed Reduction Motor, 300RPM | We are using this specific motor to drive the robot as it contains a gearbox that can reach a maximum speed of 300RPM. The compact size of these motors, coupled with a high RPM, allowed for our smaller compact design to succeed. | ![image](https://drive.google.com/uc?id=1eZ35c58Pk-_ApFsSc1q7nTVgRgd4GYDa) | [DC Motor Info](https://drive.google.com/file/d/1ovx4JvY0TAlGeaWuEGIg9i7RbAIlBQif/view?usp=drive_link) |
| CJMCU34725 TCS34725 RGB Light Color Sensor | By using this RGB color sensor, our robot can accurately detect the blue and orange lines at the mat's corners. This capability enables us to monitor the number of laps completed and ensures the robot makes precise turns when needed. | ![image](https://drive.google.com/uc?id=1HwD53e-_Z1O0NMvL_F8MH8kT12Ib7TSx) | [Color Sensor Info](https://www.waveshare.com/w/upload/b/bb/TCS34725_Color_Sensor_user_manual_en.pdf) |
| Arduino Nano |To process sensor data and make real-time decisions, we are utilizing the Arduino Nano, programmed through the Arduino IDE. This board is user-friendly, with a wide range of readily available libraries. It features 14 digital input/output pins, allowing us to connect various devices, and eight analog pins, two of which are dedicated to I2C communication. | ![image](https://drive.google.com/uc?id=1ERXHTrRA3PYL4czZBXZ7JULcs135V1fg)| [Arduino Nano Info](https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf) |
| ES08MA Metal Analog Servo | To steer our vehicle, we use a servo motor with a torque of 2.0 kilogram-force centimeters and a speed of 0.10 sec/60°. Given the substantial torque required for steering, this motor offers ample power for our needs. Additionally, its quick response time enables us to execute sharp turns with precision. | ![image](https://drive.google.com/uc?id=1PW3WRTPNTWx5we4OpXFKie0twWL3cDdZ) | [Servo Info](https://m.media-amazon.com/images/I/61ZU3A84tYS._AC_SL1000_.jpg) |
| GP2Y0A02YK0F IR Range Sensor | The IR sensors deliver information about the distance to the walls at a fast rate. These sensors accurately detect distances ranging from 20 to 150 cm. We use one sensor to gauge how close the robot is to any wall in front, while the other two help the robot maintain a centered position on the track by following the walls on either side. | ![image](https://drive.google.com/uc?id=1bApZ4N1XzXHOSyB5rUVcOve753p3ip8T) | [GP2Y0A02YK0F IR Range Sensor Info](https://cdn.robotshop.com/media/d/dem/rb-dem-02/pdf/datasheet-gp2y0a02yk0f.pdf) |
| L3G4200D Triple Axis Gyro Angular Velocity Sensor Module |We use a gyro angular velocity sensor to determine our vehicle's angular direction and precisely measure the change in angle during each turn. For accurate angle measurements, we integrate the yaw angular velocity after calibrating the gyro, allowing us to determine the robot's angle relative to its starting position. | ![image](https://drive.google.com/uc?id=1YB_kWYPEaFlx49eQdC9Qf1M95aLCoaWm) | [Gyro Info](https://www.elecrow.com/download/L3G4200_AN3393.pdf) |
| PixyCam Pixy 2.1 Robot Vision Image Sensor | Since the Arduino Nano lacks sufficient computing power for image processing, we offload this task to the Pixy 2.1 camera. This camera efficiently provides the microcontroller with the necessary data, enabling the robot to plan and follow an optimal path. | ![image](https://drive.google.com/uc?id=1V1Nqks-wj--PqYVI9ksZawQXJftz3UOQ) | [Pixy 2.1 Info](https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:start) |

## Parts Bill Of Materials (BOM)
| Part Name | Quantity |
| ----------| -------- |
| 1.5V Rechargeable Lithium Ion Battery | 4 |
| DC 6V Micro Gear Box Speed Reduction Motor, 300RPM | 2 |
| CJMCU34725 TCS34725 RGB Light Color Sensor | 1 |
| Arduino Nano | 1 |
| ES08MA Metal Analog Servo | 1 |
| GP2Y0A02YK0F IR Range Sensor | 3 |
| L3G4200D Triple Axis Gyro Angular Velocity Sensor Module | 1 |
| PixyCam Pixy 2.1 Robot Vision Image Sensor | 1 |
