
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

class Treenode {
public:
    string ID;
    string NAME;
    Treenode* left;
    Treenode* right;
    int height;

    Treenode(const string& k, const string& n, Treenode* l = nullptr, Treenode* r = nullptr)
            : ID(k), NAME(n), left(l), right(r), height(1) {}

    string toString() const {
        return "(" + ID + ", h=" + to_string(height) + ")";
    }
};

class AVLTree {
public:
    Treenode* root; // Root node of the tree

    // Constructor to initialize an empty AVL tree
    AVLTree() : root(nullptr) {}

    // Function to get the height of a node
    int getHeight(Treenode* node) {
        return node ? node->height : 0;
    }

    // Function to get the balance factor of a node
    int getBalanceFactor(Treenode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Right rotation
    Treenode* rotateRight(Treenode* y) {
        Treenode* left_subtree = y->left;
        Treenode* left_right_subtree = left_subtree->right;  // Correctly track the right subtree of left_subtree

        // Perform rotation
        left_subtree->right = y;
        y->left = left_right_subtree;  // Ensure y's left now correctly points to left_right_subtree

        // Update heights
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        left_subtree->height = max(getHeight(left_subtree->left), getHeight(left_subtree->right)) + 1;

        return left_subtree;
    }

// Left rotation
    Treenode* rotateLeft(Treenode* x) {
        Treenode* right_subtree = x->right;
        Treenode* right_left_subtree = right_subtree->left;  // Correctly track the left subtree of right_subtree

        // Perform rotation
        right_subtree->left = x;
        x->right = right_left_subtree;  // Ensure x's right now correctly points to right_left_subtree

        // Update heights
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        right_subtree->height = max(getHeight(right_subtree->left), getHeight(right_subtree->right)) + 1;

        return right_subtree;
    }

    Treenode* rotateLeftRight(Treenode* node) {
        node->left = rotateLeft(node->left);  // Step 1: Left Rotation on left child
        return rotateRight(node);             // Step 2: Right Rotation on node
    }

    Treenode* rotateRightLeft(Treenode* node) {
        node->right = rotateRight(node->right); // Step 1: Right Rotation on right child
        return rotateLeft(node);                // Step 2: Left Rotation on node
    }

    // Recursive function to insert a new node into the AVL tree
    Treenode* insertNode(Treenode* node, const string& key, const string& name) {
        if (!node) return new Treenode(key, name);

        // Insert node in the correct position
        if (key < node->ID)
            node->left = insertNode(node->left, key, name);
        else if (key > node->ID)
            node->right = insertNode(node->right, key, name);
        else
            return node; // Duplicate keys are not allowed

        // Update height of the current node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor to check if rotation is needed
        int balance = getBalanceFactor(node);

        // Left-heavy case
        if (balance > 1 && key < node->left->ID)
            return rotateRight(node);
        // Right-heavy case
        if (balance < -1 && key > node->right->ID)
            return rotateLeft(node);
        // Left-Right case
        if (balance > 1 && key > node->left->ID) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left case
        if (balance < -1 && key < node->right->ID) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Public function to insert a new student into the AVL tree
    void insert(const string& key, const string& name) {
        // Ensure the ID is valid (exactly 8 digits long)
        if (key.length() != 8) {
            cout << "unsuccessful" << endl;  // Invalid ID length
            return;
        }

        // Ensure no duplicate ID
        if (!search(root, key)) {
            root = insertNode(root, key, name);
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // Function to search for a node with a specific ID
    bool search(Treenode* node, const string& key) {
        if (!node) return false;
        if (node->ID == key) return true;
        return key < node->ID ? search(node->left, key) : search(node->right, key);
    }

    // Function to find the inorder successor (smallest node in the right subtree)
    Treenode* getInorderSuccessor(Treenode* node) {
        Treenode* current = node->right; // Start with the right child of the node

        // Keep going left until we reach the leftmost child
        while (current && current->left) {
            current = current->left;
        }

        return current; // This is the inorder successor
    }

    // Function to perform the actual node deletion
    Treenode* deleteNode(Treenode* root, const string& key) {
        if (!root) return root;

        // Find the node to delete
        if (key < root->ID)
            root->left = deleteNode(root->left, key);
        else if (key > root->ID)
            root->right = deleteNode(root->right, key);
        else {
            // Node to be deleted found
            if (!root->left && !root->right) {
                // Case 1: Node has no children (leaf node)
                delete root;
                return nullptr;
            }
            if (!root->left) {
                // Case 2: Node has one child
                Treenode* temp = root->right;
                delete root;
                return temp;
            }
            if (!root->right) {
                Treenode* temp = root->left;
                delete root;
                return temp;
            }

            // Case 3: Node has two children
            // Get the inorder successor
            Treenode* temp = getInorderSuccessor(root);

            // Replace the node's ID and NAME with the inorder successor's values
            root->ID = temp->ID;
            root->NAME = temp->NAME;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->ID);
        }

        // Update the height of the current node
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Rebalance the tree if needed
        return rebalance(root);
    }

    // Function to balance the tree after deletion
    Treenode* rebalance(Treenode* node) {
        int balance = getBalanceFactor(node);

        // Left-heavy case
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);
        // Right-heavy case
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);
        // Left-Right case
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right-Left case
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Public function to remove a student by ID
    void remove(const string& key) {
        if (search(root, key)) {
            root = deleteNode(root, key);
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    // Function to check if the name is valid (only contains alphabets and spaces)
    bool isValidName(const string& name) {
        for (char c : name) {
            if (!isalpha(c) && c != ' ') {
                return false; // If any character is not alphabet or space, return false
            }
        }
        return true;
    }

    // Function to parse input and insert a student
    void parseInputAndInsert(const string& command) {
        stringstream ss(command);
        string name;
        string id;

        // Extract the name (which should be enclosed in double quotes)
        if (getline(ss, name, '"')) {
            if (getline(ss, name, '"')) {  // If we have two quotes, the name is valid
                // Ensure the name is valid
                if (!isValidName(name)) {
                    cout << "unsuccessful" << endl;
                    return;
                }
            }
        }

        // Extract the ID after the name
        ss >> id;

        // Check if the ID is numeric and has a length of 8 digits
        if (id.find_first_not_of("0123456789") != string::npos || id.length() != 8) {
            cout << "unsuccessful" << endl;  // ID is invalid
            return;
        }


        // Perform insertion into AVL Tree
        insert(id, name);
    }



    void search(const string& ID_or_Name) {
        // Check if the input is a name (surrounded by double quotes)
        if (ID_or_Name.front() == '"' && ID_or_Name.back() == '"') {
            // Remove the quotes and treat the rest as a name
            string name = ID_or_Name.substr(1, ID_or_Name.size() - 2);
            bool found = false;
            searchByNameHelper(root, name, found);

            if (!found) {
                cout << "unsuccessful" << endl;
            }
        }
            // Otherwise, treat the input as an ID (8 integers)
        else if (ID_or_Name.size() == 8 && all_of(ID_or_Name.begin(), ID_or_Name.end(), ::isdigit)) {
            // Check if the ID exists and print the NAME
            Treenode* result = searchNode(root, ID_or_Name);
            if (result) {
                cout << result->NAME << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }

// Helper function to search for a node with a specific ID
    Treenode* searchNode(Treenode* node, const string& ID) {
        if (!node) return nullptr;
        if (node->ID == ID) return node;
        return ID < node->ID ? searchNode(node->left, ID) : searchNode(node->right, ID);
    }

// Helper function to search in a pre-order manner by name
    void searchByNameHelper(Treenode* node, const string& name, bool& found) {
        if (!node) return;

        // Check if the current node's name matches the search name
        if (node->NAME == name) {
            cout << node->ID << endl;  // Print the ID in pre-order traversal
            found = true;
        }

        // Recursively search in the left and right subtree
        searchByNameHelper(node->left, name, found);
        searchByNameHelper(node->right, name, found);
    }

    // Function to print an in-order traversal of the names in the tree
    void printInOrder(Treenode* node, bool &isFirst) {
        if (!node) return;  // If the node is null, return.

        // Traverse the left subtree first
        printInOrder(node->left, isFirst);

        // Print a comma if this is not the first element being printed
        if (!isFirst) {
            cout << ", ";
        }

        // Print the current node's name
        cout << node->NAME;
        isFirst = false;  // Mark that the first element has been printed

        // Traverse the right subtree
        printInOrder(node->right, isFirst);
    }

    // Public function to call the recursive printInOrder
    void printInOrder() {
        bool isFirst = true;  // Track if this is the first element
        printInOrder(root, isFirst);
        cout << endl;  // Move to the next line after printing
    }


    // Function to print a pre-order traversal of the names in the tree
    void printPreOrder(Treenode* node) {
        if (!node) return;  // Base case

        cout << node->NAME;  // Print the current node's name

        // Only print a comma **after** a node, if there are more nodes to print
        if (node->left || node->right) {
            cout << ", ";
        }

        printPreOrder(node->left);

        // Ensure a comma only prints **between** nodes
        if (node->left && node->right) {
            cout << ", ";
        }

        printPreOrder(node->right);
    }


    // Public function to call the recursive printPreOrder
    void printPreOrder() {
        printPreOrder(root);  // Start the traversal from the root
        cout << endl;  // Move to the next line after printing
    }

    // Function to print a post-order traversal of the names in the tree
    void printPostOrder(Treenode* node, vector<string>& result) {
        if (!node) return;

        // Traverse left and right first
        printPostOrder(node->left, result);
        printPostOrder(node->right, result);

        // Store the name instead of printing immediately
        result.push_back(node->NAME);
    }

// Public function to start from the root
    void printPostOrder() {
        vector<string> result;
        printPostOrder(root, result);

        // Print names with correct comma placement
        for (size_t i = 0; i < result.size(); i++) {
            if (i > 0) cout << ", ";
            cout << result[i];
        }
        cout << endl;
    }





    // Public function to print the number of levels in the tree
    void printLevelCount() {
        int height = getHeight(root);  // Get the height of the tree
        cout << height <<endl;  // Print the height as the number of levels
    }

    // Function to print inorder traversal
    void inorderTraversal(Treenode* node, vector<Treenode*>& inorderList) {
        if (node) {
            inorderTraversal(node->left, inorderList);
            inorderList.push_back(node);
            inorderTraversal(node->right, inorderList);
        }
    }

    // Function to remove N-th element in inorder traversal
    void removeInorder(int N) {
        vector<Treenode*> inorderList;
        inorderTraversal(root, inorderList);

        if (N < 0 || N >= inorderList.size()) {
            cout << "unsuccessful" << endl;
            return;
        }

        // Get the N-th node in inorder
        Treenode* targetNode = inorderList[N];

        // Delete the node from the tree
        remove(targetNode->ID);
    }


};

int main() {
    AVLTree tree;  // Create an instance of the AVLTree

    int numCommands;  // To store the number of commands
    cin >> numCommands;  // Read the number of commands
    cin.ignore();  // Ignore the newline after the number input

    // Process each command
    for (int i = 0; i < numCommands; ++i) {
        string command;
        getline(cin, command);  // Read the next command

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "insert") {  // Insert command
            command = command.substr(action.length() + 1);  // Skip "insert" and the space
            tree.parseInputAndInsert(command);
        } else if (action == "remove") {  // Remove command
            string number;
            ss >> number;

            // Remove from the AVL tree
            tree.remove(number);
        } else if (action == "search") {  // Search command
            string id_or_name;
            ss >> ws;  // Ignore any leading whitespace
            getline(ss, id_or_name);  // Read the ID or name

            // Determine if it's a number (ID) or name and call the appropriate search method
            if (id_or_name.find_first_not_of("0123456789") == string::npos) {
                // It's a number, search by ID
                tree.search(id_or_name);
            } else {
                // It's a name, search by name
                tree.search(id_or_name);
            }
        } else if (action == "printInorder") {  // Inorder traversal
            tree.printInOrder();
        } else if (action == "printPreorder") {  // Preorder traversal
            tree.printPreOrder();
        } else if (action == "printPostorder") {  // Postorder traversal
            tree.printPostOrder();
        } else if (action == "printLevelCount") {  // Print tree height (level count)
            tree.printLevelCount();
        } else if (action == "removeInorder") {  // Remove N-th element in inorder traversal
            int N;
            ss >> N;
            tree.removeInorder(N);
        } else {
            cout << "unsuccessful" << endl;  // Invalid command
        }
    }

    return 0;
}