## Obstacle Challenge Code Explanation

For our obstacle challenge, we use a combination of sensors, including an RGB sensor, IR sensors, a gyro sensor, and a Pixy2 camera. These sensors help the robot navigate the course, avoid obstacles, and execute precise turns. Our code is divided into two main parts: normal navigation and obstacle detection logic. Additionally, we have parking logic to ensure the robot parks correctly within the boundaries.

## Normal Navigation: 
The robot starts by using the RGB sensor, IR sensors, and gyro to maintain a straight path and avoid obstacles. The Pixy2 camera identifies objects and assists with steering adjustments. The Pixy2 camera detects blocks in the robot’s path. If a block is close enough (i.e., its y-coordinate is greater than 35), the robot stores this block as the current target:

`if (pixy.ccc.numBlocks) {
    sig = pixy.ccc.blocks[0].m_signature;
    x = pixy.ccc.blocks[0].m_x;
    y = pixy.ccc.blocks[0].m_y;
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
        }
    }
}` . 

Based on the block’s position and color, the robot adjusts its steering to follow the block closely. This helps the robot maintain a path that avoids obstacles and keeps it on course.

## Wall Following::
When no blocks are detected or when the robot needs to avoid obstacles on its sides, it uses IR sensors for wall following. The robot measures the distance to the walls on its left and right and adjusts its course accordingly:
`if (bl) {
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
    } else if (distL < 30 and distR > 30) {
        dD = -20;
    } else {
        dD = 0;
    }
}` . 

The robot also checks for obstacles directly in front. If it detects something too close, it stops and backs up slightly before continuing. This prevents crashes and allows the robot to navigate around unexpected obstacles.

## Turning Logic 
When the robot approaches a corner and detects the designated color (either orange or blue), it moves forward until it sees the wall. Once the wall is detected and the color is still in view, the robot begins its turning maneuver using the gyro sensor to ensure a precise turn:
`dA += 89;
myservo.write(35);
move_str(false, 100, 1600);
myservo.write(85);`. 

The robot carefully checks its surroundings and only turns after confirming both the presence of the wall and the designated color. This helps the robot avoid premature turns and ensures that it follows the intended path accurately.

If the robot reaches a point where it needs to make a 180-degree turn (reverse lap), it uses the gyro to rotate until it’s aligned with the new direction:
`
dA = -8783;
bl = true;
o = false;`

This code adjusts the robot’s internal angle tracking, ensuring it’s ready to continue in the opposite direction after the turn.


## Parking Logic:
Parking Detection: The robot enters the parking phase when it has completed the the 3 laps. It slows down and aligns itself precisely before stopping:
`   else if (p== true){
    if (bl == true){
      if (sig == 1||sig == 2){
        dR =75;
      }
      else if (sig == 3){
        if (y>65){
          myservo.write(50);
          analogWrite(mlp,0);
          digitalWrite(mld,true);
          delay(500);
          analogWrite(mlp,255);
          delay(1000000);
        }
      }
    }
    if (o == true){
      if (sig == 1||sig == 2){
        dG =75;
      }
      else if (sig == 3){
        if (y>65){
          myservo.write(120);
          analogWrite(mlp,0);
          digitalWrite(mld,true);
          delay(500);
          analogWrite(mlp,255);
          delay(1000000);
        }
      }
    }
  }
`. 

