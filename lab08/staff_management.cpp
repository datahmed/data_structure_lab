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

void showStaff(Node* n) {
    if (n == NULL) return;
    cout << n->name << " | left: ";
    if (n->left != NULL) cout << n->left->name;
    else cout << "NULL";
    cout << " | right: ";
    if (n->right != NULL) cout << n->right->name;
    else cout << "NULL";
    cout << endl;
    showStaff(n->left);
    showStaff(n->right);
}

void freeStaff(Node* n) {
    if (!n) return;
    freeStaff(n->left);
    freeStaff(n->right);
    delete n;
}

class BNode {
public:
    int id;
    BNode* left;
    BNode* right;
    BNode(int v) {
        id = v;
        left = right = NULL;
    }
};

class BST {
    BNode* root;

    BNode* ins(BNode* r, int v, bool& ok) {
        if (r == NULL) {
            ok = true;
            return new BNode(v);
        }
        if (v < r->id) r->left = ins(r->left, v, ok);
        else if (v > r->id) r->right = ins(r->right, v, ok);
        else ok = false;
        return r;
    }

    BNode* del(BNode* r, int v, bool& found) {
        if (r == NULL) return NULL;
        if (v < r->id) r->left = del(r->left, v, found);
        else if (v > r->id) r->right = del(r->right, v, found);
        else {
            found = true;
            if (r->left == NULL) {
                BNode* t = r->right;
                delete r;
                return t;
            }
            if (r->right == NULL) {
                BNode* t = r->left;
                delete r;
                return t;
            }
            BNode* s = r->right;
            while (s->left != NULL) s = s->left;
            r->id = s->id;
            bool f2 = false;
            r->right = del(r->right, s->id, f2);
        }
        return r;
    }

    BNode* copyTree(BNode* r) {
        if (r == NULL) return NULL;
        BNode* n = new BNode(r->id);
        n->left = copyTree(r->left);
        n->right = copyTree(r->right);
        return n;
    }

    void inorder(BNode* r) {
        if (r == NULL) return;
        inorder(r->left);
        cout << r->id << " ";
        inorder(r->right);
    }

    void clear(BNode* r) {
        if (r == NULL) return;
        clear(r->left);
        clear(r->right);
        delete r;
    }

public:
    BST() { root = NULL; }

    BST(const BST& other) {
        root = copyTree(other.root);
    }

    ~BST() { clear(root); }

    bool insert(int v) {
        bool ok = false;
        root = ins(root, v, ok);
        return ok;
    }

    bool search(int v) {
        BNode* cur = root;
        int visits = 0;
        while (cur != NULL) {
            visits++;
            if (v == cur->id) {
                cout << "ID " << v << " found. Node visits: " << visits << endl;
                return true;
            }
            if (v < cur->id) cur = cur->left;
            else cur = cur->right;
        }
        cout << "ID " << v << " not found. Node visits: " << visits << endl;
        return false;
    }

    bool remove(int v) {
        bool found = false;
        root = del(root, v, found);
        return found;
    }

    void show() {
        if (root == NULL) {
            cout << "(empty)";
        }
        inorder(root);
        cout << endl;
    }
};

int readInt() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a number: ";
    }
    return x;
}

int main() {
    Node* root = new Node("Dr. Hassan");
    root->left = new Node("Prof. Sara");
    root->right = new Node("Prof. Imran");
    root->left->left = new Node("Mr. Bilal");
    root->left->right = new Node("Ms. Hina");
    root->right->left = new Node("Mr. Usman");
    root->right->right = new Node("Ms. Ayesha");
    root->left->left->left = new Node("Mr. Farhan");

    cout << "--- General Binary Tree ---" << endl;
    showStaff(root);
    cout << endl;

    int start[7] = {48, 28, 68, 18, 38, 58, 78};
    BST original;
    for (int i = 0; i < 7; i++) original.insert(start[i]);

    BST staff(original);

    cout << "--- Add 3 more staff IDs ---" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Enter staff ID " << i + 1 << ": ";
        int id = readInt();
        if (staff.insert(id)) cout << id << " inserted." << endl;
        else cout << id << " already exists, tree not changed." << endl;
    }
    cout << "IDs now: ";
    staff.show();
    cout << endl;

    cout << "--- Search tests ---" << endl;
    staff.search(58);
    staff.search(99);
    staff.search(5);
    cout << endl;

    cout << "--- Deletion tests on fresh copies of the original BST ---" << endl;
    BST c1(original);
    cout << "Leaf (38): ";
    c1.remove(38);
    c1.show();

    BST c2(original);
    c2.insert(20);
    cout << "One child (18 after adding 20 under it): ";
    c2.remove(18);
    c2.show();

    BST c3(original);
    cout << "Two children (28): ";
    c3.remove(28);
    c3.show();
    cout << endl;

    cout << "Enter a staff ID to delete: ";
    int d = readInt();
    if (staff.remove(d)) cout << d << " deleted." << endl;
    else cout << d << " not found, nothing deleted." << endl;

    cout << "Remaining IDs (in-order): ";
    staff.show();
    cout << endl;

    cout << "--- Why in-order differs ---" << endl;
    cout << "A general binary tree has no rule about where values go, so left, root, right" << endl;
    cout << "order can come out in any order. In a BST every value in the left subtree is" << endl;
    cout << "smaller than the node and every value in the right subtree is bigger, so" << endl;
    cout << "visiting left, node, right always gives ascending order." << endl;

    freeStaff(root);
    return 0;
}
