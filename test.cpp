/*#include <iostream>
#include <sstream>
#include <cassert>
#include "main.cpp"  // Include main.cpp to access AVLTree and Treenode classes

using namespace std;

void testInsert(AVLTree& tree) {
    cout << "Testing insert:" << endl;
    tree.insert(12345678, "Alice");  // Expected: successful
    tree.insert(87654321, "Bob");    // Expected: successful
    tree.insert(12345678, "Charlie"); // Expected: unsuccessful (duplicate ID)
}

void testRemove(AVLTree& tree) {
    cout << "\nTesting remove:" << endl;
    tree.remove(12345678);  // Expected: successful
    tree.remove(99999999);  // Expected: unsuccessful (ID not found)
}

void testSearchByID(AVLTree& tree) {
    cout << "\nTesting search by ID:" << endl;
    tree.search(87654321);  // Expected: Bob
    tree.search(11111111);  // Expected: unsuccessful
}

void testSearchByName(AVLTree& tree) {
    cout << "\nTesting search by Name:" << endl;
    tree.search("Bob");  // Expected: 87654321
    tree.search("Charlie");  // Expected: unsuccessful
}

void testPrintTraversals(AVLTree& tree) {
    cout << "\nTesting traversals:" << endl;
    tree.printInOrder();   // Expected: Alice, Bob
    tree.printPreOrder();  // Expected: Alice, Bob
    tree.printPostOrder(); // Expected: Bob, Alice
}

int main() {
    AVLTree tree;

    // Running the test functions
    testInsert(tree);
    testRemove(tree);
    testSearchByID(tree);
    testSearchByName(tree);
    testPrintTraversals(tree);

    return 0;
}*/
