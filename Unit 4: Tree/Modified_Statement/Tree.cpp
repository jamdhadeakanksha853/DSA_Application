#program
// MODIFIED - Employee ID Management using BST (Full Records)
// Features: Insert, Search, Delete (3 cases), Inorder, Preorder, Postorder, Min/Max, Count

#include <iostream>
using namespace std;

struct Employee {
    int empID;
    string name;
    string dept;
    int salary;
    Employee* left;
    Employee* right;

    Employee(int id, string n, string d, int s) {
        empID = id;
        name = n;
        dept = d;
        salary = s;
        left = right = NULL;
    }
};

Employee* insertEmp(Employee* root, int id, string name, string dept, int salary) {
    if (root == NULL) return new Employee(id, name, dept, salary);
    if (id < root->empID) root->left = insertEmp(root->left, id, name, dept, salary);
    else if (id > root->empID) root->right = insertEmp(root->right, id, name, dept, salary);
    else cout << "Duplicate ID not allowed!" << endl;
    return root;
}

Employee* searchEmp(Employee* root, int id) {
    if (root == NULL || root->empID == id) return root;
    if (id < root->empID) return searchEmp(root->left, id);
    return searchEmp(root->right, id);
}

Employee* findMin(Employee* root) {
    while (root && root->left != NULL) root = root->left;
    return root;
}

Employee* deleteEmp(Employee* root, int id) {
    if (root == NULL) return root;
    if (id < root->empID) root->left = deleteEmp(root->left, id);
    else if (id > root->empID) root->right = deleteEmp(root->right, id);
    else {
        // Found node
        if (root->left == NULL) { // One child or leaf
            Employee* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Employee* temp = root->left;
            delete root;
            return temp;
        }
        // Two children: inorder successor
        Employee* temp = findMin(root->right);
        root->empID = temp->empID;
        root->name = temp->name;
        root->dept = temp->dept;
        root->salary = temp->salary;
        root->right = deleteEmp(root->right, temp->empID);
    }
    return root;
}

void inorder(Employee* root) {
    if (root) {
        inorder(root->left);
        cout << root->empID << " | " << root->name << " | " << root->dept << " | " << root->salary << endl;
        inorder(root->right);
    }
}
void preorder(Employee* root) {
    if (root) {
        cout << root->empID << " | " << root->name << endl;
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Employee* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->empID << " | " << root->name << endl;
    }
}

int countNodes(Employee* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void displayMinMax(Employee* root) {
    if (root == NULL) { cout << "Tree empty!" << endl; return; }
    Employee* minNode = findMin(root);
    Employee* maxNode = root;
    while (maxNode->right != NULL) maxNode = maxNode->right;
    cout << "Min ID Employee: " << minNode->empID << " - " << minNode->name << endl;
    cout << "Max ID Employee: " << maxNode->empID << " - " << maxNode->name << endl;
}

int main() {
    Employee* root = NULL;
    int ch, id, sal;
    string name, dept;
    
    do {
        cout << "\n====== EMPLOYEE MANAGEMENT - MODIFIED ======" << endl;
        cout << "1. Insert Employee\n2. Search\n3. Delete\n4. Display Inorder (Sorted)\n5. Display Preorder\n6. Display Postorder\n7. Min/Max ID\n8. Count Employees\n9. Exit\nEnter choice: ";
        cin >> ch;
        switch(ch) {
            case 1: cout << "Enter ID Name Dept Salary: "; cin >> id >> name >> dept >> sal; root = insertEmp(root, id, name, dept, sal); break;
            case 2: cout << "Enter ID to search: "; cin >> id; {
                Employee* r = searchEmp(root, id);
                if(r) cout << "Found: " << r->empID << " " << r->name << " " << r->dept << " " << r->salary << endl; else cout << "Not Found!" << endl; } break;
            case 3: cout << "Enter ID to delete: "; cin >> id; root = deleteEmp(root, id); cout << "Deleted if existed!" << endl; break;
            case 4: cout << "\n--- Inorder (Sorted) ---\n"; inorder(root); break;
            case 5: cout << "\n--- Preorder ---\n"; preorder(root); break;
            case 6: cout << "\n--- Postorder ---\n"; postorder(root); break;
            case 7: displayMinMax(root); break;
            case 8: cout << "Total Employees: " << countNodes(root) << endl; break;
            case 9: cout << "Exiting..." << endl; break;
            default: cout << "Invalid!" << endl;
        }
    } while(ch != 9);
    return 0;
}
