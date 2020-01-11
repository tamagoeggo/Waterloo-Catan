# Waterloo-Catan
A Waterloo themed game based on the Settlers of Catan game.
Board based on the environment of the University of Waterloo. As per University regulations and rules only the header files and object files are included.

# Compilation
Makefile is included. Use the command `make` in unix environment. It will compiled with the program name Watan and can excecuted with the command `./Watan`

# Command Line Interface
* `-seed xxx` sets the random number generator’s seed to xxx
* `-load xxx` loads the game saved in file xxx
* `-board xxx` loads the game with the board specified in the file xxx instead of using random generation
* `-enhance` adds color to the board
* `-bank` adds the bank trading option to the game

# Commands For Beginning of Turn
* `load`: sets the dice of the current student to be loaded dice
* `fair`: sets the dice of the current student to be fair dice
* `roll`: rolls the current student’s dice

# Commands For End of Turn
* `board`: prints the current board
* `status`: prints the current status of all students in order from student 0 to 3
* `criteria`: prints the criteria the current student has currently completed
* `achieve <#>`: attempts to achieve the goal at <#>
* `complete <#>`: attempts to complete the criterion at <#>
* `improve <#>`: attempts to improve the criterion at <#>
* `trade <colour> <give> <take>`: attempts to trade with student <colour> giving one resource of type <give> and receiving one resource of type <take>
* `next`: passes control onto the next student in the game.
* `save <file>`: saves the current game state to <file>
* `help`: prints out the list of commands
  
<!-- ![alt text](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png "Logo Title Text 1") -->
  
