# sudoku   

A tiny sudoku game on linux. 

## install  
``` bash  
cd path/to/sudoku
mkdir build
cd build
cmake ..
make .

```
## run 
The game has two mode.  
1. ```./sudoku``` to run the game which generate a new puzzle.  
2. ```./sodoku -l path/to/txt``` to load the txt file that saved the game before.
3. Certainly ,you can use ```-h``` option to get help information. 

## play  
- 'w' 'a' 's' 'd' for $\uparrow$ $\leftarrow$ $\downarrow$ $\rightarrow$ ,you will move the cursor on the screen  
- '1-9' to assign the grid the cursor pointing and 0 to refresh it .  
- 'u' to undo the operation you made.  
- 'space' to check whether solved.  
- 'esc' to exit and save the game if needed.
  



