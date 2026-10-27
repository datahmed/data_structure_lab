#include <iostream>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;
    Node(int v) {
        id = v;
        left = NULL;
        right = NULL;
    }
};

class BST {
    Node* root;

    Node* add(Node* r, int v, bool& ok) {
        if (r == NULL) {
            ok = true;
            return new Node(v);
        }
        if (v < r->id) r->left = add(r->left, v, ok);
        else if (v > r->id) r->right = add(r->right, v, ok);
        else ok = false;
        return r;
    }

    Node* del(Node* r, int v, bool& found) {
        if (r == NULL) return NULL;
        if (v < r->id) r->left = del(r->left, v, found);
        else if (v > r->id) r->right = del(r->right, v, found);
        else {
            found = true;
            if (r->left == NULL) {
                Node* t = r->right;
                delete r;
                return t;
            }
            else if (r->right == NULL) {
                Node* t = r->left;
                delete r;
                return t;
            }
            Node* s = r->right;
            while (s->left) s = s->left;
            r->id = s->id;
            bool f = false;
            r->right = del(r->right, s->id, f);
        }
        return r;
    }

    void in(Node* r) {
        if (!r) return;
        in(r->left);
        cout << r->id << " ";
        in(r->right);
    }

    void pre(Node* r) {
        if (!r) return;
        cout << r->id << " ";
        pre(r->left);
        pre(r->right);
    }

    void post(Node* r) {
        if (!r) return;
        post(r->left);
        post(r->right);
        cout << r->id << " ";
    }

    int count(Node* r) {
        if (r == NULL) return 0;
        return 1 + count(r->left) + count(r->right);
    }

    int height(Node* r) {
        if (r == NULL) return 0;
        int a = height(r->left);
        int b = height(r->right);
        return 1 + (a > b ? a : b);
    }

    void freeAll(Node* r) {
        if (r == NULL) return;
        freeAll(r->left);
        freeAll(r->right);
        delete r;
    }

public:
    BST() { root = NULL; }
    ~BST() { freeAll(root); }

    void insertId(int v) {
        bool ok = false;
        root = add(root, v, ok);
        if (ok) cout << v << " inserted." << endl;
        else cout << v << " already exists. Tree not changed." << endl;
    }

    void searchId(int v) {
        if (root == NULL) {
            cout << "Tree is empty." << endl;
            return;
        }
        Node* cur = root;
        while (cur != NULL) {
            if (v == cur->id) {
                cout << v << " found." << endl;
                return;
            }
            if (v < cur->id) cur = cur->left;
            else cur = cur->right;
        }
        cout << v << " not found." << endl;
    }

    void deleteId(int v) {
        if (root == NULL) {
            cout << "Tree is empty, nothing to delete." << endl;
            return;
        }
        bool found = false;
        root = del(root, v, found);
        if (found) {
            cout << v << " deleted. Updated IDs: ";
            in(root);
            cout << endl;
        }
        else cout << v << " does not exist, nothing deleted." << endl;
    }

    void inorder() {
        if (root == NULL) { cout << "Tree is empty." << endl; return; }
        in(root);
        cout << endl;
    }

    void preorder() {
        if (root == NULL) { cout << "Tree is empty." << endl; return; }
        pre(root);
        cout << endl;
    }

    void postorder() {
        if (root == NULL) { cout << "Tree is empty." << endl; return; }
        post(root);
        cout << endl;
    }

    void showCount() {
        cout << "Total nodes: " << count(root) << endl;
    }

    void showHeight() {
        cout << "Height of BST: " << height(root) << endl;
    }
};

int getNum() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Numbers only, try again: ";
    }
    return x;
}

int main() {
    BST tree;
    int first[9] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int i = 0; i < 9; i++) {
        bool dummy;
        tree.insertId(first[i]);
    }

    int choice = 0;
    while (choice != 9) {
        cout << endl;
        cout << "1. Insert an ID" << endl;
        cout << "2. Search for an ID" << endl;
        cout << "3. Delete an ID" << endl;
        cout << "4. In-order traversal" << endl;
        cout << "5. Pre-order traversal" << endl;
        cout << "6. Post-order traversal" << endl;
        cout << "7. Count nodes" << endl;
        cout << "8. Height of BST" << endl;
        cout << "9. Exit" << endl;
        cout << "Choice: ";
        choice = getNum();

        if (choice == 1) {
            cout << "ID to insert: ";
            tree.insertId(getNum());
        }
        else if (choice == 2) {
            cout << "ID to search: ";
            tree.searchId(getNum());
        }
        else if (choice == 3) {
            cout << "ID to delete: ";
            tree.deleteId(getNum());
        }
        else if (choice == 4) tree.inorder();
        else if (choice == 5) tree.preorder();
        else if (choice == 6) tree.postorder();
        else if (choice == 7) tree.showCount();
        else if (choice == 8) tree.showHeight();
        else if (choice == 9) cout << "Bye." << endl;
        else cout << "Invalid choice, pick 1 to 9." << endl;
    }
    return 0;
}
