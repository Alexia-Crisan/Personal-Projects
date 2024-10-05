Hand Gesture LED Controller: Arduino & Python Mediapipe Project

This project uses Mediapipe hand tracking with Python to count the
number of fingers raised on your right hand, and controls a set of LEDs
connected to an Arduino Uno based on the finger count. The setup
demonstrates real-time interaction between Python and Arduino via serial
communication, where the number of fingers raised determines how many
LEDs light up.

Key Features:  
    - Finger Counting with Mediapipe: A Python script uses
Google's Mediapipe library to track the right hand in real-time and
count the number of fingers that are raised. The camera captures the
hand gestures, and Mediapipe accurately detects how many fingers are
extended.  
    - LED Control with Arduino: The number of raised fingers is
transmitted from the Python script to the Arduino Uno over a serial
connection. The Arduino is responsible for controlling 4 LEDs based on
the number of fingers detected: 0 fingers = No LEDs lit, 1 finger = 1
LED lit, 2 fingers = 2 LEDs lit, 3 fingers = 3 LEDs lit, 4 or 5 fingers
= All 4 LEDs lit (since there are only 4 LEDs available).  
    - Serial Communication: The Python script sends the detected finger 
count via the COM port to the Arduino. The Arduino listens to the serial 
data and adjusts the number of lit LEDs accordingly.

This project helped me explore the integration of computer vision using
Mediapipe with hardware control through Arduino. It demonstrated how
Python can handle hand tracking and communicate with an Arduino over
serial to control LEDs. I learned about real-time data transmission,
serial communication, and how to combine different technologies to
create interactive projects.

Here is a GIF demonstrating the system in action:

![Finger Counter](video_fingers_LED.gif)