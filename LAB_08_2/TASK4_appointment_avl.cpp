#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int token;
    int height;
    Node* left;
    Node* right;
    Node(int t) {
        token = t;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

int balance(Node* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

void fixHeight(Node* n) {
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t = x->right;
    x->right = y;
    y->left = t;
    fixHeight(y);
    fixHeight(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* t = y->left;
    y->left = x;
    x->right = t;
    fixHeight(x);
    fixHeight(y);
    return y;
}

Node* insert(Node* root, int key) {
    if (root == NULL) return new Node(key);
    if (key < root->token) root->left = insert(root->left, key);
    else if (key > root->token) root->right = insert(root->right, key);
    else return root;

    fixHeight(root);
    int bf = balance(root);

    if (bf > 1 && key < root->left->token) {
        cout << "LL case at " << root->token << " -> right rotation" << endl;
        return rightRotate(root);
    }
    if (bf < -1 && key > root->right->token) {
        cout << "RR case at " << root->token << " -> left rotation" << endl;
        return leftRotate(root);
    }
    if (bf > 1 && key > root->left->token) {
        cout << "LR case at " << root->token << " -> left rotation on child, then right rotation" << endl;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && key < root->right->token) {
        cout << "RL case at " << root->token << " -> right rotation on child, then left rotation" << endl;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder(Node* n) {
    if (!n) return;
    inorder(n->left);
    cout << n->token << " ";
    inorder(n->right);
}

void nodeInfo(Node* n) {
    if (n == NULL) return;
    nodeInfo(n->left);
    cout << "Token " << n->token << "  height = " << n->height << "  balance factor = " << balance(n) << endl;
    nodeInfo(n->right);
}

void printTree(Node* n, int space) {
    if (n == NULL) return;
    printTree(n->right, space + 6);
    for (int i = 0; i < space; i++) cout << " ";
    cout << n->token << endl;
    printTree(n->left, space + 6);
}

void demo(int a, int b, int c, const char* name) {
    Node* r = NULL;
    cout << name << " test, inserting " << a << ", " << b << ", " << c << endl;
    r = insert(r, a);
    r = insert(r, b);
    r = insert(r, c);
    cout << "root is now " << r->token << ", inorder: ";
    inorder(r);
    cout << endl << endl;
}

int main() {
    int tokens[7] = {15, 25, 35, 45, 55, 65, 75};
    Node* root = NULL;

    cout << "Inserting appointment tokens" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "insert " << tokens[i] << endl;
        root = insert(root, tokens[i]);
    }

    cout << endl << "Height and balance factor of each node" << endl;
    nodeInfo(root);

    cout << endl << "In-order traversal: ";
    inorder(root);
    cout << endl;

    cout << endl << "Final balanced tree (root on the left, right side on top)" << endl;
    printTree(root, 0);

    cout << endl << "---- All four rotation cases ----" << endl;
    demo(30, 20, 10, "LL");
    demo(10, 20, 30, "RR");
    demo(30, 10, 20, "LR");
    demo(10, 30, 20, "RL");

    return 0;
}
