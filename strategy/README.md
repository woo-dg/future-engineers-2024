
Strategy
====

This directory consists of an explanation and diagrams of our strategy for both the open and obstacle rounds.

## Open Challenge Strategy

In the open challenge, the only changes to the field are the size of the interior walls. In order to combat these changes, we will be using IR distance sensors to identify the distance from the walls. By having multiple distance sensors, the robot can accurately calculate the distance to the surrounding walls. The robot can use these sensor readings to correct itself and make sure it goes parallel to the wall. The robot will know when to turn due to the usage of a RGB sensor which detects the colored lines in the corner. This will also allow us to keep track of the number of laps we complete so we know when to end.
