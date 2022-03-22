# Line Follower Robot


## Information 
Line Follower Robot has many applications such as transportation in warehouse of factory, serving food in restaurant, direction or location information in mall or museum.
It has the ability to move on its own according to a given line controlled by a feedback mechanism.


## Component
- IR sensor module
- Servo geared motors
- Motor drive L298N 
- Microcontroller: Arduino Uno R3
- Power supply
- Robot frame
- Two wheels


## Algorithm
IR sensor module gets data from the LED of each sensor. The two motors rotate together in one dirrection to go forward or backward. When robot deviates to the right from the line, set the speed of the right motor to be faster than that of the left motor and vice versa. If not the above cases, reverse at a slow speed to find the line again.


## Product 
![Robot] (https://github.com/Julme02/LineFollowerRobot/blob/main/product.jpg)






