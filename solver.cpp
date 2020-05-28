/* 
Assume one 4x4 array is given to the solver from the generator. This grid is has any spot 
with a wumpus labeled "wumpus", pit with "pit", and gold with "gold". Robot will always 
start in the lower left corner of the grid (4,0).
*/

/* Potential smaller functions to be called in main:

- expanding rule function:
    - bool for if the robot is adjacent to a pit, if bool = false then label spot "np"
    - bool for if the robot is adjacent to a wumpus, if bool = false then label spot "nw"
    - any spot visited gets a "v" added to the end of its label (if it is already labeled, if not just a v)

- function to update markings on grids

- shooting the arrow function to remove Wumpus

*/


int main() { // main code will go here

// two grids will be used, visited and waiting

}