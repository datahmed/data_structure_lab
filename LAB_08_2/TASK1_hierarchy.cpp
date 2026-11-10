#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;
    Node(string n) {
        name = n;
        left = NULL;
        right = NULL;
    }
};

void display(Node* n) {
    if (n == NULL) return;
    cout << n->name << "  |  left child: ";
    if (n->left) cout << n->left->name;
    else cout << "NULL";
    cout << "  |  right child: ";
    if (n->right) cout << n->right->name;
    else cout << "NULL";
    cout << endl;
    display(n->left);
    display(n->right);
}

int main() {
    Node* hod = new Node("Dr. Kamran (HOD)");
    Node* c1 = new Node("Dr. Sana (Coordinator BS)");
    Node* c2 = new Node("Dr. Imran (Coordinator MS)");
    Node* f1 = new Node("Ms. Ayesha");
    Node* f2 = new Node("Mr. Bilal");
    Node* f3 = new Node("Ms. Hira");
    Node* f4 = new Node("Mr. Usman");

    hod->left = c1;
    hod->right = c2;
    c1->left = f1;
    c1->right = f2;
    c2->left = f3;
    c2->right = f4;

    cout << "Department Hierarchy" << endl;
    cout << "--------------------" << endl;
    display(hod);

    return 0;
}
