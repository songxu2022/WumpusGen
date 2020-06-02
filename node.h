#include <iostream>
#include <vector>
using namespace std;

/* 
This is a class to keep track of each individual node (aka spot on grid)
This class will not change any labels or markings on the game board. It is designed to
know everything about one specific node.
*/

class Node {
    public:
    // constructor, takes in node's location, what the spot is labeled
    Node(signed int xcoord, signed int ycoord, const string & label_);

    Node(const Node& n); //copy constructor
    Node& operator=(const Node & n); // assignment operator
    ~Node(); // destructor

    // getters
    signed int get_x_coord() const; // gets x coordinate
    signed int get_y_coord() const; // gets y coordinate
    const string & get_label() const; // gets the node's label

    // bools for what's around the node
    bool is_start_spot(); // checks if node is the starting location
    bool next_to_vertical_wall(); // checks if node is next to a vertical wall
    bool next_to_horizontal_wall(); // checks if node is next to a horizontal wall
    bool is_corner_spot(); // checks if the node is in the corner of the board
    
    bool next_to_right_wall(); // checks if the node is next to the right wall
    bool next_to_left_wall(); // checks if the node is next to the left wall
    bool next_to_upper_wall(); // checks if node is next to the upper wall
    bool next_to_lower_wall(); // checks if node is next to the lower wall

    bool is_pit(); // checks if the next spot in any direction is a pit
    bool is_wumpus(); // checks if the next spot in any direction is the wumpus
    bool is_gold(); // checks if the next spot in any direction is the gold
    bool is_notpit_marked(); // checks if the spot is marked as not having a pit
    bool is_notwumpus_marked(); // checks if the spot is marked as not having a wumpus

    private:

    // private helper functions used in copy constructor and destructor
    void copy(const Node & n);

    // private variables
    int x_coord;
    int y coord;
    string label;

};
