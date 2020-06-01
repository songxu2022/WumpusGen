#include <iostream>
#include <vector>
#include "node.h"
using namespace std;

Node::Node(int xcoord, int ycoord, string & label_, vector<string> & generatedboard) {
    // constructor function
    x_coord = xcoord;
    y_coord = ycoord;
    label = label_;
    generated_board = generatedboard;
}

Node::~Node() { // destuctor will call the function that deallocates the generated board
    deallocate_generated_board();
}

void Node::deallocate_generated_board() {
    // function to delete the generated board and prevent memory leaks
    for (int i = 0; i < generated_board.size(); i++){
        for (int j = 0; j < generated_board[i].size(); j++) {
            delete generated_board[i][j];
        }
        delete [] generated_board[i];
    }
    delete [] generated_board;
}

Node::Node(const Node& n) { //calls copy constructor function
    copy(b);
}

void Node::copy(const Node &n) {// function that copies the generated board
    // copy over variables
    this->x_coord = n.x_coord;
    this->y_coord = n.y_coord;
    this->label = n.label;
    // loop through the generated board and copy everything over
    this->generated_board = new string*[this->generated_board.size()]
    for (int i = 0; i < this->generated_board.size(); i++){
        this->generated_board[i] = new string[generated_board[i].size()]
        for (int j = 0; j < this->generated_board[0].size(); j++) {
            this->generated_board[i][j] = n.generated_board[i][j];
        }
    }
}

Node& Node::operator=(const Node & n) { // assigment operator function
    // check if the two node objects are equal
    if (this != &n) { 
        // if two node objects are not equal, call destructor and copy the new board
        deallocate_generated_board();
        this->copy(n);
    }
    // return pointer to object
    return *this;
}

int Node::get_x_coord() const {
    return x_coord;
}

int Node::get_y_coord() const {
    return y_coord;
}

const string& Node::get_label() const {
    return label;
}

bool Node::is_start_spot() {
    /* 
    A node is at the starting location if it is at the bottom left corner of the generated board. This
    means that the x coordinate should be in the last row of the generated board (its size) and the y
    coordinate should be in the first spot in the last row (that spot is index 0).
    */

    return x_coord == generated_board.size() && y_coord == 0
}

bool Node::next_to_vertical_wall() {
    // if node is at the start, its at a corner, so its definitely next to a vertical wall
    if (is_start_spot) {
        return true;
    }
    //A node is next to a vertical wall if its y coordinate is in the first or last spot in a row 
    if ( y_coord == 0 || y_coord == (generated_board[0].size() - 1)) {
        return true;
    }
    // if it fits neither of these then the node is not next to a vertical wall
    return false;
}

bool Node::next_to_horizontal_wall() {
    // if node is at the start, its at a corner, so its definitely next to a horizontal wall
    if (is_start_spot) {
        return true;
    }
    // A node is next to a horizontal wall if its x coordinate is in the top or bottom row
    if (x_coord == 0 || x_coord == (generated_board.size() - 1)) {
        return true;
    }
    // if it fits neither of these then the node is not next to a horizontal wall
    return false;
}

 bool Node::is_corner_spot() {
     //A node is in a corner if it is next to a vertical wall AND a horizontal wall
     return next_to_vertical_wall() && next_to_horizontal_wall()
 }

 
vector<string> find_adjacent_spots(signed int x, signed int y) {
    //checks that going any which way on a node is still in the bounds of the board

    vector<string> adjacent_spots; // keeps track of the spots that surround the node
    if (x + 1 < generated_board.size()) {
        adjacent_spots.push_back(generated_board[x + 1][y]);
    }
    if (x - 1 >= 0) {
        adjacent_spots.push_back(generated_board[x - 1][y]);
    }
    if (y + 1 < generated_board[0].size()) {
        adjacent_spots.push_back(generated_board[x][y + 1])
    }
    if (y - 1 >= 0) {
        adjacent_spots.push_back(generated_board[x][y - 1])
    }

    // return the vector of all the possible adjacent spots around
    return adjacent_spots;
}


bool Node::is_pit_adjacent() {
    /* 
    This function assumes that any spot on the generated board with a pit is labeled "pit". This
    may need to be changed if the pits are labeled differently.
    */

    vector<string> possible_spots = find_adjacent_spots(x_coord, y_coord);
    for (int i = 0; i < possible_spots.size(); i++) {
        if (possible_spots[i] == "pit") {
            return true;
        }
    }
    // no pit is in the surrounding spots so return false
    return false;
}

bool Node::is_wumpus_adjacent() {
    /* 
    This function assumes that any spot on the generated board with a wumpus is labeled "wumpus". This
    may need to be changed if the wumpus spot is labeled differently.
    */

    vector<string> possible_spots = find_adjacent_spots(x_coord, y_coord);
    for (int i = 0; i < possible_spots.size(); i++) {
        if (possible_spots[i] == "wumpus") {
            return true;
        }
    }
    // no wumpus is in the surrounding spots so return false
    return false;
}

bool Node::is_gold_adjacent() {
    /* 
    This function assumes that any spot on the generated board with the gold is labeled "gold". This
    may need to be changed if the gold spot is labeled differently.
    */

    vector<string> possible_spots = find_adjacent_spots(x_coord, y_coord);
    for (int i = 0; i < possible_spots.size(); i++) {
        if (possible_spots[i] == "gold") {
            return true;
        }
    }
    // no gold is in the surrounding spots so return false
    return false;
}