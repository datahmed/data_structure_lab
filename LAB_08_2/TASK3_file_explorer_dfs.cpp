#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string folder;
    Node* left;
    Node* right;
    Node(string f) {
        folder = f;
        left = NULL;
        right = NULL;
    }
};

void inorder(Node* n) {
    if (n == NULL) return;
    inorder(n->left);
    cout << n->folder << "  ";
    inorder(n->right);
}

void preorder(Node* n) {
    if (n == NULL) return;
    cout << n->folder << "  ";
    preorder(n->left);
    preorder(n->right);
}

void postorder(Node* n) {
    if (!n) return;
    postorder(n->left);
    postorder(n->right);
    cout << n->folder << "  ";
}

int main() {
    Node* root = new Node("C:");
    root->left = new Node("Documents");
    root->right = new Node("Programs");
    root->left->left = new Node("Assignments");
    root->left->right = new Node("Pictures");
    root->right->left = new Node("Games");
    root->right->right = new Node("Office");

    cout << "In-order   : ";
    inorder(root);
    cout << endl;
    cout << "Pre-order  : ";
    preorder(root);
    cout << endl;
    cout << "Post-order : ";
    postorder(root);
    cout << endl << endl;

    cout << "Visiting order of each traversal" << endl;
    cout << "In-order   -> Left, Root, Right" << endl;
    cout << "Pre-order  -> Root, Left, Right" << endl;
    cout << "Post-order -> Left, Right, Root" << endl;

    return 0;
}
