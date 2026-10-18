#Linked List Modified.cpp
#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int coeff;
    int exp;
    Node* next;
};

// Insert term - sorted descending by exponent
void insertTerm(Node* &head, int coeff, int exp) {
    if (coeff == 0) return;
    Node* newNode = new Node();
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    if (head == NULL || head->exp < exp) {
        newNode->next = head;
        head = newNode;
        return;
    }
    if (head->exp == exp) {
        head->coeff += coeff;
        delete newNode;
        if (head->coeff == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        return;
    }
    Node* temp = head;
    while (temp->next != NULL && temp->next->exp > exp) {
        temp = temp->next;
    }
    if (temp->next != NULL && temp->next->exp == exp) {
        temp->next->coeff += coeff;
        delete newNode;
        if (temp->next->coeff == 0) {
            Node* del = temp->next;
            temp->next = del->next;
            delete del;
        }
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void createPoly(Node* &head) {
    int n, coeff, exp;
    cout << "Enter number of terms: ";
    cin >> n;
    head = NULL;
    for (int i = 0; i < n; i++) {
        cout << "Term " << i+1 << " (coeff exp): ";
        cin >> coeff >> exp;
        insertTerm(head, coeff, exp);
    }
}

void displayPoly(Node* head) {
    if (head == NULL) {
        cout << "0" << endl;
        return;
    }
    Node* temp = head;
    bool first = true;
    while (temp != NULL) {
        if (!first && temp->coeff > 0) cout << " + ";
        else if (temp->coeff < 0) cout << " ";
        cout << temp->coeff << "x^" << temp->exp;
        first = false;
        temp = temp->next;
    }
    cout << endl;
}

Node* addPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    Node* t = p1;
    while (t != NULL) {
        insertTerm(result, t->coeff, t->exp);
        t = t->next;
    }
    t = p2;
    while (t != NULL) {
        insertTerm(result, t->coeff, t->exp);
        t = t->next;
    }
    return result;
}

Node* subPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    Node* t = p1;
    while (t != NULL) {
        insertTerm(result, t->coeff, t->exp);
        t = t->next;
    }
    t = p2;
    while (t != NULL) {
        insertTerm(result, -t->coeff, t->exp);
        t = t->next;
    }
    return result;
}

Node* mulPoly(Node* p1, Node* p2) {
    Node* result = NULL;
    for (Node* t1 = p1; t1 != NULL; t1 = t1->next) {
        for (Node* t2 = p2; t2 != NULL; t2 = t2->next) {
            int newCoeff = t1->coeff * t2->coeff;
            int newExp = t1->exp + t2->exp;
            insertTerm(result, newCoeff, newExp);
        }
    }
    return result;
}

int evaluatePoly(Node* head, int x) {
    int result = 0;
    Node* temp = head;
    while (temp != NULL) {
        result += temp->coeff * pow(x, temp->exp);
        temp = temp->next;
    }
    return result;
}

int main() {
    Node *p1 = NULL, *p2 = NULL;
    int choice, x;

    cout << "===== POLYNOMIAL CALCULATOR =====" << endl;
    cout << "\n--- Create First Polynomial P1 ---" << endl;
    createPoly(p1);
    cout << "\n--- Create Second Polynomial P2 ---" << endl;
    createPoly(p2);

    do {
        cout << "\n====== MENU ======" << endl;
        cout << "1. Add Polynomials (P1+P2)" << endl;
        cout << "2. Subtract Polynomials (P1-P2)" << endl;
        cout << "3. Multiply Polynomials (P1*P2)" << endl;
        cout << "4. Evaluate Polynomial" << endl;
        cout << "5. Display Polynomials" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        Node* result = NULL;
        switch (choice) {
            case 1:
                result = addPoly(p1, p2);
                cout << "\nP1 + P2 = ";
                displayPoly(result);
                break;
            case 2:
                result = subPoly(p1, p2);
                cout << "\nP1 - P2 = ";
                displayPoly(result);
                break;
            case 3:
                result = mulPoly(p1, p2);
                cout << "\nP1 * P2 = ";
                displayPoly(result);
                break;
            case 4:
                cout << "Enter value of x to evaluate P1: ";
                cin >> x;
                cout << "P1(" << x << ") = " << evaluatePoly(p1, x) << endl;
                cout << "Enter value of x to evaluate P2: ";
                cin >> x;
                cout << "P2(" << x << ") = " << evaluatePoly(p2, x) << endl;
                break;
            case 5:
                cout << "\nP1: "; displayPoly(p1);
                cout << "P2: "; displayPoly(p2);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}
