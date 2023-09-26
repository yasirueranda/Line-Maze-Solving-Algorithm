# Line-Maze-Solving-Algorithm
The algorithm is based on the right hand rule.
## Main functions
- Maze
  : Explore the Line Maze and Store the Maze in Linear Array 
- shortpath
  : Calculate the Shortest Path by looking at the Path Array
- gomaze
  : Support function
- revmaze
  : move back in the maze through the shortest path
- revpath
  : maintaining the Reverse Path Stack

## Other function used by the robot
- read_IR
  : store the IR readings in IR_val[5:0] array
- pid_forward(count)
  : pid activated move forward with varible delay
- turn_leftn
  : turn left until it detects a line
- turn_rightn
  : turn right until it detects a line
- force_forward
  : mix of blind forward action and a pid activated forward action

Note: 'other functions' are robot physical capabilities dependant. it can be implemented to suit the design specs of the robot.

![Line Maze](https://github.com/yasirueranda/Line-Maze-Solving-Algorithm/assets/129848234/36d1b533-bf61-47ed-8fd9-67bc14b0fb7e)

