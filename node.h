#include <iostream>
#include <vector>
using namespace std;

/* 
This is a class to keep track of each individual node (aka spot on grid)
This class takes in only the generated board that was given by generator.
This class will not change any labels or markings on the game board. It is designed to
know everything about the surrounding area of one specific node.
*/

class Node {
    public:
    // constructor, takes in node's location, what the spot is labeled, and the generated board itself
    Node(signed int xcoord, signed int ycoord, const string & label_, vector<string> & generatedboard);

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
    bool is_pit_adjacent(); // checks if the next spot in any direction is a pit
    bool is_wumpus_adjacent(); // checks if the next spot in any direction is the wumpus
    bool is_gold_adjacent(); // checks if the next spot in any direction is the gold

    private:

    // private helper functions used in copy constructor and destructor
    void deallocate_generated_board();
    void copy(const Node & n);

    // other private helper functions used within the classs
    vector<string> find_adjacent_spots(signed int x, signed int y);

    // private variables
    int x_coord;
    int y coord;
    string label;
    vector<string> generated_board;

};
