## Open Challenge Code

In the open challenge, our approach leverages gyro and infrared (IR) sensor feedback to ensure precise navigation along a defined path. The robot is designed to maintain a straight course using continuous sensor readings to make real-time adjustments.

## Gyro-Based Steering:
Initially, before reaching the first corner, the robot has no reference for its direction, so it relies on gyro-based steering. The gyro sensor monitors the robot's angular orientation, and we calculate the steering adjustment by comparing the target angle with the current angle. This difference, or error, is then used to steer the robot accordingly:  `int error = targetAngle - mpu.getAngleZ();
int steer = map(error, -30, 30, 40, 130);` . 

The map() function translates the error into an appropriate steering angle, ensuring that the robot corrects its course smoothly.

## Color-Based Direction Setting:
As the robot navigates, it needs to establish and maintain its direction. We use an RGB color sensor to detect specific colors on the track, which helps the robot determine its heading. If the direction isn't set, it assigns the current color as the reference:

`if (direction == 0) {
    direction = tcs.getColor();
    }` . 

This ensures the robot is aligned with the track's color cues, setting a baseline for subsequent maneuvers.

## Corner Detection and Handling:
The robot’s cornering logic activates when it detects a change in color, indicating a corner or junction. The system checks if the color matches the established direction and if sufficient time has passed since the last turn. If these conditions are met, the robot adjusts its target angle and prepares to execute a turn:
` if (tcs.getColor() == direction && millis() - lastTurnTime > 2000) {
    delay(60);  // brief pause to stabilize
    cornerCount++;
    targetAngle += (direction == 1) ? 90 : -90;
    lastTurnTime = millis();
}`. 

This method allows the robot to dynamically adjust its path based on real-time sensor feedback, ensuring accurate navigation through complex paths.

## Wall Following:
In tight corridors or when close to walls, the robot employs a wall-following algorithm to maintain a safe distance. The IR sensors measure the distance to the nearest wall, and if the robot gets too close, it adjusts its course to steer away:
`
if (caughtOnWall) {
    int error = 20 - (direction == 1 ? sensorR.distance() : sensorL.distance());
    steer = constrain(error * (direction == 1 ? -2.0 : 2.0), -15, 15);
}
`. 

Here, the constrain() function ensures that the steering adjustments remain within safe limits, preventing the robot from making overly sharp turns.

## Final Control Adjustments:
Throughout its run, the robot continuously monitors its surroundings and adjusts both its steering and speed to stay on track. The system is designed to avoid abrupt movements, maintaining smooth and controlled navigation until it reaches the end of its path.

By integrating gyro stabilization, color-based direction setting, corner detection, and wall following, the robot effectively navigates the course with precision and adaptability, responding dynamically to its environment.
