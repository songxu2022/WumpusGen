#include <iostream>
#include <vector>
using namespace std;

/* 
This is a class to keep track of each individual node (aka spot on game board)
This class will not change any labels or markings on the game board. It is designed to
know everything about one specific node.
*/

class Node {
    public:
    /*
    constructor, takes in node's location, what the spot is labeled, 
    and the size of each wall (ex: if it's a 4x4 board the wall size would be 4)
    */
    Node(int xcoord, int ycoord, const string & label_, int wall_size);

    Node(const Node& n); //copy constructor
    Node& operator=(const Node & n); // assignment operator
    ~Node(); // destructor

    // getters
    int get_x_coord() const; // gets x coordinate
    int get_y_coord() const; // gets y coordinate
    int get_wall_size() const; //gets the wall size
    const string & get_label() const; // gets the node's label

    // bools for what's around the node
    bool is_start_spot(); // checks if node is the starting location
    bool next_to_right_wall(); // checks if the node is next to the right wall
    bool next_to_left_wall(); // checks if the node is next to the left wall
    bool next_to_upper_wall(); // checks if node is next to the upper wall
    bool next_to_lower_wall(); // checks if node is next to the lower wall
    bool is_corner_spot(); // checks if the node is in a corner of the board

    bool is_pit(); // checks if the node is a pit
    bool is_wumpus(); // checks if the node is the wumpus
    bool is_gold(); // checks if the node is the gold
    bool is_notpit_marked(); // checks if the node is marked as not having a pit
    bool is_notwumpus_marked(); // checks if the node is marked as not having a wumpus

    private:

    // private helper functions used in copy constructor and destructor
    void copy(const Node & n);
    void delete_node();

    // private variables
    int x_coord;
    int y coord;
    string label;
    int wall_size; 

};
