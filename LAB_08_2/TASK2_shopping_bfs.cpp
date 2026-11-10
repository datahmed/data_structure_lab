#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;
    Node(string n) {
        name = n;
        left = right = NULL;
    }
};

void bfs(Node* root) {
    if (root == NULL) {
        cout << "No categories" << endl;
        return;
    }
    queue<Node*> q;
    q.push(root);
    int level = 0;
    while (!q.empty()) {
        int size = q.size();
        cout << "Level " << level << ": ";
        for (int i = 0; i < size; i++) {
            Node* cur = q.front();
            q.pop();
            cout << cur->name << "  ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << endl;
        level++;
    }
}

int main() {
    Node* shop = new Node("Shop");
    shop->left = new Node("Electronics");
    shop->right = new Node("Clothing");
    shop->left->left = new Node("Mobiles");
    shop->left->right = new Node("Laptops");
    shop->right->left = new Node("Men");
    shop->right->right = new Node("Women");
    shop->left->left->left = new Node("Accessories");

    cout << "Product categories in BFS order (level by level)" << endl;
    bfs(shop);

    cout << endl << "BFS order in one line: ";
    queue<Node*> q;
    q.push(shop);
    while (!q.empty()) {
        Node* t = q.front();
        q.pop();
        cout << t->name << " ";
        if (t->left != NULL) q.push(t->left);
        if (t->right != NULL) q.push(t->right);
    }
    cout << endl;
    return 0;
}
