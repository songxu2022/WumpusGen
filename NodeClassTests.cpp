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


int main() 
{
// runs invalid input test and prints results
if (invalid_input_test()) {
    cout << "Invalid input test passed!" << endl;
} else {
    cout << "Error, invalid input test failed!" << endl;
}
// runs changing the label test and prints results
if (change_label_test()) {
    cout << "Change label test passed!" << endl;
} else {
    cout << "Error, change label test failed!" << endl;
}
return 0;
}