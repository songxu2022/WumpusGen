#include <iostream>
using namespace std;

/* 
This is a class to keep track of each individual node (aka spot on grid)
*/

class Node {
    public:
    // constructor, takes in node's location and what the spot is labeled
    Node(int x_coord, int y_coord, string & label);

    Node(const Node& n); //copy constructor
    Node& operator=(const Node & n); // assignment operator
    ~Node(); // destructor

    // getters
    int get_x_coord() const; // gets x coordinate
    int get_y_coord() const; // gets y coordinate
    const string & get_label() const; // gets the node's label

    // bools for what's around the node
    bool is_pit_adjacent();
    bool is_wumpus_adjacent();
    bool is_gold_adjacent();

    private:
    int x_coord;
    int y coord;
    string label;

};
