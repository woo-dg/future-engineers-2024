
Strategy
====

This directory consists of an explanation and diagrams of our strategy for both the open and obstacle rounds.

## Open Challenge Strategy

In the open challenge, the only variations to the field are the size of the interior walls. To adapt to these changes, we will employ IR distance sensors to measure the distance from the walls. With multiple sensors, the robot can accurately calculate its distance from the surrounding walls, enabling it to correct its course and maintain a parallel trajectory. The robot will know when to turn when the RGB sensor detects the colored lines at the corners. This also allows us to track the number of laps completed, ensuring we know when to finish. 
