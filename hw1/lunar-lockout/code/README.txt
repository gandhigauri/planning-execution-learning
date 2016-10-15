Lunar Lockout Game

Game Pieces
The lunar lockout game has several pieces. First, we have a 5x5 game board with a red square marked in the middle. Next, we have 5 helper spacecraft in various colors and then 1 red spacecraft. We are also given cards that specify initial setup position for some subset of spacecraft. On the back of each card is a solution.

Game Description
The goal of this game it to move the red spacecraft to the center red square. One can move any spacecraft but they are limited to moving up-down or left-right. Whenever a spacecraft moves, it continues moving until it hits another spacecraft. Note that it is not legal for the spacecraft to move off the board. Therefore, all spacecraft need to cooperate together to stay on the board and help the red spacecraft reach the goal.

Code Description
The state at each instant has been represented as the location of all the pieces at that time instant. The location corresponds to the grid_id corresponding to the grid x,y location(The lower left corner of the board ie x=0 y=0 corresponds to grid id 0).
The code implements a Breadth First Search to explore new feasible states and to find a feasible plan to the goal.

Running Instructions:
The code is accompanied with a problem_file.txt with the following information:
(The problem number)problem 36
(The dimension of board)board dimensions 5
(The number of pegs on board)number of objects 6
(The order of spaceships with the letter corresponding to the first letter of color)spaceships ryopgb
(The start state; locations for each spaceship written as x,y)start r 4,2 y 1,4 o 3,0 p 1,0 g 3,4 b 0,2
(The goal state)goal r 2,2

Change the above mentioned details as per your requirements.
On the terminal, run the executable lunar-lockout as follows:
./lunar-lockout problem_file.txt

The plan to the goal is printed on the screen.
