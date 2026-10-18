#linked list original.cpp
#include <iostream>
using namespace std;

struct Node {
    int coeff;
    int exp;
    Node* next;
};

// Insert term at end
void insertTerm(Node* &head, int coeff, int exp) {
    Node* newNode = new Node();
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    
    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Create polynomial
void createPoly(Node* &head) {
    int n, coeff, exp;
    cout << "Enter number of terms: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter coeff and exp for term " << i+1 << ": ";
        cin >> coeff >> exp;
        insertTerm(head, coeff, exp);
    }
}

// Add two polynomials
Node* addPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    Node *t1 = p1, *t2 = p2;
    
    while (t1 != NULL && t2 != NULL) {
        if (t1->exp == t2->exp) {
            int sum = t1->coeff + t2->coeff;
            if (sum != 0) insertTerm(result, sum, t1->exp);
            t1 = t1->next;
            t2 = t2->next;
        }
        else if (t1->exp > t2->exp) {
            insertTerm(result, t1->coeff, t1->exp);
            t1 = t1->next;
        }
        else {
            insertTerm(result, t2->coeff, t2->exp);
            t2 = t2->next;
        }
    }
    while (t1 != NULL) {
        insertTerm(result, t1->coeff, t1->exp);
        t1 = t1->next;
    }
    while (t2 != NULL) {
        insertTerm(result, t2->coeff, t2->exp);
        t2 = t2->next;
    }
    return result;
}

// Display polynomial
void displayPoly(Node* head) {
    if (head == NULL) {
        cout << "0";
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->coeff << "x^" << temp->exp;
        if (temp->next != NULL) cout << " + ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Node *p1 = NULL, *p2 = NULL, *res = NULL;
    
    cout << "--- Create First Polynomial P1 ---" << endl;
    createPoly(p1);
    
    cout << "\n--- Create Second Polynomial P2 ---" << endl;
    createPoly(p2);
    
    cout << "\nP1: ";
    displayPoly(p1);
    cout << "P2: ";
    displayPoly(p2);
    
    res = addPoly(p1, p2);
    
    cout << "\nResultant (P1 + P2): ";
    displayPoly(res);
    
    return 0;
}
