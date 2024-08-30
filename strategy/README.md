
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

