Chicken Run: Arduino LCD Keypad Game

Chicken Run is a fun, interactive game built using an Arduino Uno and a
16x2 LCD Keypad Shield. The goal of the game is to control a chicken on
the screen, avoiding randomly appearing obstacles---mushrooms and
clouds---as they move toward the player. The game draws inspiration from
the offline Google Chrome Dinosaur game, where the player must dodge
obstacles to keep going.

Gameplay Overview:  - Objective: Move the chicken and dodge the
obstacles (mushrooms and clouds) that randomly appear on the screen. The
score increases each time the chicken successfully passes an obstacle.
 - Increasing Difficulty: The speed of the game increases as your score
reaches multiples of 10, making it progressively harder to dodge
obstacles.  - Win Condition: The game ends when the player reaches a
score of 100, at which point the message "You are so cool!" is displayed
on the screen, celebrating your victory.

Key Features:  - LCD Display & Controls: The game is displayed on a 16x2
LCD screen. The chicken is controlled using the buttons on the Keypad
Shield to move up or down.  - Random Obstacles: Mushrooms and clouds
appear randomly on the screen, simulating obstacles the chicken must
avoid. As each obstacle moves across the screen, it gets \"passed\" by
the chicken, and the score increments.  - Score System: You gain 1 point
every time an obstacle is passed. When your score reaches a multiple of
10, the game\'s speed increases, adding a layer of challenge. Upon
reaching 100 points, the game ends with a special congratulatory
message: "You are so cool!"  - Progressive Difficulty: As the score
increases, the speed at which the mushrooms and clouds appear increases,
making it more difficult to dodge them. This keeps the gameplay dynamic
and challenging as you progress toward the goal of 100 points.

This project allowed me to dive deeper into handling user input,
controlling dynamic screen elements, and managing game state transitions
on a limited display. It was also a fun way to practice random number
generation, timing logic, and speed scaling in an Arduino-based
environment.

Here is a GIF demonstrating the system in action:

![Chicken RUn](video_chicken_run.gif)