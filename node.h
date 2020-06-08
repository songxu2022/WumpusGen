#include <iostream>
#include <string>
using namespace std;

/* 
This is a class to keep track of each individual node (aka spot on game board)
It is designed to know everything about one specific node.
*/

class Node {
    public:
    /*
    constructor, takes in node's location, what the spot is labeled, 
    and the size of each wall (ex: if it's a 4x4 board the wall size would be 4)
    */
    Node(int xcoord, int ycoord, string &label_, int wall_size);

    // getters
    int get_x_coord() const; // gets x coordinate
    int get_y_coord() const; // gets y coordinate
    int get_wall_size() const; //gets the wall size
    string& get_label() const; // gets the node's label

    // setters
    void set_label(string new_label); // sets the label of the node
	
    // bools for what's around the node
    bool is_start_spot(); // checks if node is the starting location
    bool next_to_right_wall(); // checks if the node is next to the right wall
    bool next_to_left_wall(); // checks if the node is next to the left wall
    bool next_to_upper_wall(); // checks if node is next to the upper wall
    bool next_to_lower_wall(); // checks if node is next to the lower wall
    bool is_corner_spot(); // checks if the node is in a corner of the board

    bool is_empty(); // checks if the node is labeled as being empty
    bool is_pit(); // checks if the node is a pit
    bool is_wumpus(); // checks if the node is the wumpus
    bool is_gold(); // checks if the node is the gold
    bool is_notpit_marked(); // checks if the node is marked as not having a pit
    bool is_notwumpus_marked(); // checks if the node is marked as not having a wumpus
    bool marked_as_visited(); // checks if the node was marked as having been visited
	
	/*below functions need to be implemented or add a way to initialize*/
	bool is_breeze();
	bool is_stench();
	// bools for
	//shoot arrow 
	void killw(); // shoot at this node 
	// bool for markings for algorithm
	bool nw=false;
	bool np=false;
	bool visited=false;
	
    private:

    int x_coord;
    int y_coord;
    string label;
    int wall_size; 

};
