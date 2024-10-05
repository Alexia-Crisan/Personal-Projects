Arduino Minesweeper: LCD Keypad Game

This project is a simplified version of the classic Minesweeper game,
built using an Arduino Uno and a 16x2 LCD Keypad Shield. The objective
is to navigate through the 16x2 grid, uncovering safe spots while
avoiding a single hidden bomb placed randomly in one of the 32 cells.
Using the buttons on the shield, the player moves a cursor around the
screen to \"mine\" each spot. The goal is to successfully mine all 31
safe spots without triggering the bomb.

Key Features:  - Grid Navigation: The 16x2 LCD display represents a
simple 2D grid, and the keypad allows you to move the cursor up, down,
left, and right to select different spots.  - Randomized Bomb Location:
Each time the game starts, the bomb is placed randomly in one of the 32
cells. This ensures a new challenge for every round.  - Safe Spots:
There are 31 safe spots, which the player must uncover to win. The game
is won when all non-bomb cells are mined.  - Game Over Condition: If the
player accidentally mines the bomb cell, the game is lost, and the
screen displays a "You lost :(" message.  - Learning Experience: The
project helped me practice integrating the LCD Keypad Shield with
Arduino, learning how to handle button input, display updates, and
random number generation to add an element of unpredictability.

How It Works: Button Controls:  - Left/Right/Up/Down: These buttons
allow the player to move the cursor around the grid.  - Select: Pressing
the select button \"mines\" the current cell. Gameplay:  - At the start
of the game, the bomb is randomly placed in one of the 32 cells.  - The
player then moves around the grid, selecting cells to mine.  - If a safe
spot is mined, the player can continue.  - If the bomb is mined, the
game ends, and a "You lost :(" message is displayed.

This project was a great learning experience, helping me gain hands-on
experience with LCD screens, button input, and basic game logic using
the Arduino environment.


Here is a GIF demonstrating the system in action:

![Bomb game](video_bomb_game.gif)