#include <iostream>
#include <string>
#include "node.h"
using namespace std;

/* 
This program is to test every single way the node class could be misused or produce
an error. It tests things like giving the class an invalid input like negative numbers 
(which would be bad because the coordinates and wall size should always be positive) and
it also tests if the bool functions are consistent with the node label, even after the
label gets changed.
*/

bool invalid_input_test() { 
/* 
tests that giving the program negative numbers will not work and be corrected to 0
*/

// the mistake for n1 is that the y coordinate is negative
Node n1(2, -1, "e", 4);
// the mistake for n2 is that the x coordinate is negative
Node n2(-7, 0, "p", 4);
// the mistake for n3 is that the wall size is less than 4
Node n3(1, 2 , "nw", 2);
// the mistake for n4 is that the wall size is a negative number
Node n4(4, 0, "s", -4);

if (n1.get_y_coord() != 0 ) {
    return false;
}
if (n2.get_x_coord() != 0) {
    return false;
}
if (n3.get_wall_size() != 4 || n4.get_wall_size() != 4) {
    return false;
}
// if function makes it to the end then everything worked so return true;
return true;
}

bool change_label_test() {
    // changes the label multiple times
    Node test(4, 0 , "s", 4);
    if (test.get_label() != "s") {
        return false;
    }
    if (!test.is_start_spot()) {
        return false;
    }
    test.set_label("np");
    if (test.get_label() != "np") {
        return false;
    }
    if (!test.is_notpit_marked()) {
        return false;
    }
    test.set_label("w");
    if (test.get_label() != "w") {
        return false;
    }
    if (!test.is_wumpus()) {
        return false;
    }
    // if function made it to the end then everything worked!
    return true;
    }

bool wall_test() {
    // node v_wall is next to an upper wall
    Node u_wall(0, 2, "e", 4);
    // node h_wall is next to a right wall
    Node r_wall(1, 3 , "e", 4);
    // node corner_node is in a corner spot, next to left and bottom wall
    Node corner_node(3, 0 , "e", 4);
    // node middle is not near any walls
    Node middle(2, 2, "g", 4);

    // test that the wall functions that describe each of these nodes come out true
    if (!u_wall.next_to_upper_wall()) {
        return false;
    }
    if (!r_wall.next_to_right_wall()) {
        return false;
    }
    if (!corner_node.next_to_left_wall()) {
        return false;
    }
    if (!corner_node.next_to_lower_wall()) {
        return false;
    }
    if (!corner_node.is_corner_spot()) {
        return false;
    }
    // the middle node is next to no walls so it should return false for everything
    if (middle.next_to_upper_wall() || middle.is_corner_spot() || middle.next_to_lower_wall()) {
        return false;
    }
    // if the function made it to the end then everything worked as planned
    return true;
}


int main() 
{
//variable to keep track of number of tests ran
int tests = 0;
// variable to keep track of number of tests that passed
int successes = 0;

// runs invalid input test and prints results
tests += 1;
if (invalid_input_test()) {
    successes += 1;
    cout << "Invalid input test passed!" << endl;
} else {
    cout << "Error, invalid input test failed!" << endl;
}
// runs changing the label test and prints results
tests += 1;
if (change_label_test()) {
    successes += 1;
    cout << "Change label test passed!" << endl;
} else {
    cout << "Error, change label test failed!" << endl;
}
// runs wall test and prints results
tests += 1;
if (wall_test()) {
    successes += 1;
    cout<< "Wall test passed!" << endl;
} else {
    cout << "Error, wall test failed!" << endl;
}
// if the number of successes matches the number of tests we ran, then we know everything passed
if (successes == tests) {
    cout << "All tests passed!" << endl;
}
return 0;
}