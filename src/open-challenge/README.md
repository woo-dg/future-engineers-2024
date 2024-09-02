## Open Challenge Code

In our open challenge approach, we focus on utilizing gyro and infrared (IR) sensors to maintain a precise navigation path. The robot continuously reads sensor data to make real-time adjustments, ensuring it stays on course.

## Gyro-Based Steering:
Before the robot reaches the first corner, it relies on the gyro sensor to maintain a straight path, as it doesn't yet have a fixed directional reference. The robot computes the steering adjustment by mapping the difference between the current angle and the desired target angle:
`str = map(mpu.getAngleZ() - dA, 30, -30, 40, 130);
if (str > 130) {
    str = 130;
} else if (str < 40) {
    str = 40;
}
myservo.write(str);  // Adjust steering` . 

This code continuously updates the servo position, ensuring that the robot corrects any drift from its intended path by adjusting the steering angle.

## Color-Based Direction Setting:
As the robot navigates, it needs to establish and maintain its direction. We use an RGB color sensor to detect specific colors on the track, which helps the robot determine its heading. If the direction isn't set, it assigns the current color as the reference:

`if (lux < 6 && r < 10) {
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
}` . 

This ensures the robot is aligned with the track's color cues, setting a baseline for subsequent maneuvers.

## Corner Detection and Handling:
The robot’s cornering logic activates when it detects a change in color, indicating a corner or junction. The system checks if the color matches the established direction and if sufficient time has passed since the last turn. If these conditions are met, the robot adjusts its target angle and prepares to execute a turn:
`if (lux < 6 && r > 15) {
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
}`. 

This code allows the robot to make precise turns based on real-time sensor data, ensuring it navigates corners accurately.

## Wall Following:
In tight corridors or when close to walls, the robot employs a wall-following algorithm to maintain a safe distance. The IR sensors measure the distance to the nearest wall, and if the robot gets too close, it adjusts its course to steer away:
`if (bl) {
    mpu.update();
    str = map(mpu.getAngleZ() - dA, 30, -30, 40, 130);
    myservo.write(str);
    distR = sensorR.distance();
    if (distR > 35) {
        myservo.write(75);
    } else if (distR < 25) {
        myservo.write(95);
    }
}
`. 

This block ensures that the robot maintains an optimal distance from the wall by making fine adjustments to its steering, thus avoiding collisions.

## Final Control Adjustments:
Throughout its run, the robot continuously monitors its surroundings and adjusts both its steering and speed to stay on track. The system is designed to avoid abrupt movements, maintaining smooth and controlled navigation until it reaches the end of its path.

By integrating gyro stabilization, color-based direction setting, corner detection, and wall following, the robot effectively navigates the course with precision and adaptability, responding dynamically to its environment.
