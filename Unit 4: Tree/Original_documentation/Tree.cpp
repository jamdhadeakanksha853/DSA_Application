#program 
// ORIGINAL - Employee ID Management using BST
// Features: Insert, Search, Display Sorted (Inorder)

#include <iostream>
using namespace std;

struct Node {
    int empID;
    string empName;
    Node* left;
    Node* right;
    
    Node(int id, string name) {
        empID = id;
        empName = name;
        left = right = NULL;
    }
};

Node* insertNode(Node* root, int id, string name) {
    if (root == NULL) {
        return new Node(id, name);
    }
    if (id < root->empID) {
        root->left = insertNode(root->left, id, name);
    } else if (id > root->empID) {
        root->right = insertNode(root->right, id, name);
    } else {
        cout << "Duplicate ID not allowed!" << endl;
    }
    return root;
}

Node* searchNode(Node* root, int id) {
    if (root == NULL || root->empID == id) {
        return root;
    }
    if (id < root->empID) {
        return searchNode(root->left, id);
    }
    return searchNode(root->right, id);
}

void inorderDisplay(Node* root) {
    if (root != NULL) {
        inorderDisplay(root->left);
        cout << "ID: " << root->empID << ", Name: " << root->empName << endl;
        inorderDisplay(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, id;
    string name;

    do {
        cout << "\n===== EMPLOYEE ID MANAGEMENT (ORIGINAL) =====" << endl;
        cout << "1. Insert Employee" << endl;
        cout << "2. Search Employee" << endl;
        cout << "3. Display All (Sorted by ID)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Employee ID: ";
                cin >> id;
                cout << "Enter Employee Name: ";
                cin >> name;
                root = insertNode(root, id, name);
                cout << "Employee Inserted!" << endl;
                break;
            case 2:
                cout << "Enter ID to search: ";
                cin >> id;
                {
                    Node* result = searchNode(root, id);
                    if (result != NULL) {
                        cout << "Found -> ID: " << result->empID << ", Name: " << result->empName << endl;
                    } else {
                        cout << "Employee ID " << id << " not found!" << endl;
                    }
                }
                break;
            case 3:
                cout << "\n--- Employee List (Sorted) ---" << endl;
                inorderDisplay(root);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    return 0;
}
