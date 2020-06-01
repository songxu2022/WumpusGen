#include <iostream>
using namespace std;

/* 
This is a class to keep track of each individual node (aka spot on grid)
This class will not change any labels or markings on the game board. It is designed to
know everything about the surrounding area of one specific node.
*/

class Node {
    public:
    // constructor, takes in node's location, what the spot is labeled, and the generated board itself
    Node(int x_coord, int y_coord, string & label, arr<string> & generated_board);

    Node(const Node& n); //copy constructor
    Node& operator=(const Node & n); // assignment operator
    ~Node(); // destructor

    // getters
    int get_x_coord() const; // gets x coordinate
    int get_y_coord() const; // gets y coordinate
    const string & get_label() const; // gets the node's label

    // bools for what's around the node
    bool is_pit_adjacent(); // checks if the next spot in any direction is a pit
    bool is_wumpus_adjacent(); // checks if the next spot in any direction is the wumpus
    bool is_gold_adjacent(); // checks if the next spot in any direction is the gold

    private:
    // helper functions that will only be called inside the class
    bool is_start_spot(); // checks if node is the starting location
    bool next_to_vertical_wall(); // checks if node is next to a vertical wall
    bool next_to_horizontal_wall(); // checks if node is next to a horizontal wall

    // private variables
    int x_coord;
    int y coord;
    string label;
    arr<string> generated_board;

};
