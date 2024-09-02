
Strategy
====

This directory consists of an explanation and diagrams of our strategy for both the open and obstacle rounds.

## Open Challenge Strategy

In the open challenge, the only variations to the field are the size of the interior walls. To adapt to these changes, we employ IR distance sensors to measure the distance from the walls. With multiple sensors, the robot can accurately calculate its distance from the surrounding walls, enabling it to correct its course and maintain a parallel trajectory. The robot will know when to turn when the RGB sensor detects the colored lines at the corners. This also allows us to track the number of laps completed, ensuring we know when to finish. 

| Straight Movement | Turning |
| ----------------- | ------- |
| ![image](https://drive.google.com/uc?id=1sl-HCauvqxThJZm0eeGbrZbrhHrH50nJ) | ![image](https://drive.google.com/uc?id=1nIDDyOZn28JYcaWRNiBgwWf6LNt0vX17) |

| Open Challenge Flowchart |
| ------------------------ |
| ![image](https://drive.google.com/uc?id=1_4qiJSqqLnAqw7ilf54cnIb5HE8X9X17) |

## Obstacle Challenge Strategy

Our strategy for the obstacle challenge is to maintain the closest detected color on the designated side of the robot. This is achieved by monitoring the x-position of objects identified by the camera and adjusting the steering accordingly to ensure that the object remains on the correct side. The turning and stopping mechanisms will utilize the same logic that was successfully implemented in the open challenge.

To optimize our steering adjustments, we employ a proportional control loop, which will allow for precise maneuvering as the robot encounters obstacles. This approach ensures that our movements are both accurate and responsive to the environment.

| Obstacle Challenge Simple Approach |
| ---------------------------------- |
| ![image](https://drive.google.com/uc?id=18gsX1JlRYennzsx7GrNMAYbRCy7gM8yc) |
