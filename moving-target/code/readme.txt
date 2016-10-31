THE MOVING TARGET PROBLEM

Problem Description
In this problem a point robot has to catch a moving target.  Both the robot and the target live in a NxN 4-connected 2D gridworld. This means they can only move up, down, left or right.  Additionally, both the robot and the target can also decide to remain in the current position.  However, neither the robot nor the target can move through the outer walls of the grid.
Each cell in the gridworld is associated with the cost of visiting it.  This cost is an integer that ranges from 1 to 1,000.  Note that when the robot chooses to remain in the same cell, it will pay the cost of the visit again.
The  robot  knows  in  advance  the  predicted  trajectory  of  the  moving  target,  as  a  sequence  of positions in the grid (for example:  (3,3), (2,3), (2,2)).  The  first element of this trajectory is the initial position of the target at time step 0.  Both the robot and the target move at the speed of one cell per timestep.
After  the  last  cell  on  its  trajectory,  the  target  disappears.   So,  if  the  given  target's trajectory  is  of  length  40,  then  at  timestep  =  40 (assuming  timesteps  begin  with  0)  the  object disappears and the robot can no longer catch it.

Approach
Two  planners have been implemented to help the robot catching the moving target. The task of the planners is to generate the path the robot should follow in order to catch the target.  In other words, this path should make sure that the robot arrives at one of the cells visited by the moving target either before or at the exact same timestep the target gets there.
Planner A: Finds the least cost path to catch the target
Planner B: Finds a computationally faster path at the expense of optimality to catch the target

Code Description
Both the planners implement a forward 3D Astar assuming each state to be (x,y,time). The heuristic cost is calculated by implementing a 2D backward Dijkstra for  the complete grid. The planner B implements a weighted AStar to return a faster and suboptimal path.

Running Instructions:
There are 2 problem files in the folder: problem_0 and problem_1.
The code can be executed by simply running the executable file with the problem file name as follows:
./moving-target-a <problem_file>
./moving-target-b <problem_file>

 

