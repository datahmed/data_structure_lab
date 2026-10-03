#include <iostream>
using namespace std;

class Node {
public:
    string name;
    Node *prev, *next;
    Node(string n) {
        name = n;
        prev = next = NULL;
    }
};

class Gallery {
    Node *head, *tail;
public:
    Gallery() { head = tail = NULL; }

    void insert(string img) {
        Node* n = new Node(img);
        if (head == NULL) {
            head = tail = n;
        }
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }

    void showForward() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->name << "  ";
            temp = temp->next;
        }
        cout << endl;
    }

    void showBackward() {
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->name << "  ";
            temp = temp->prev;
        }
        cout << endl;
    }

    // go to 3rd image then move both ways
    void navigate() {
        Node* cur = head->next->next;
        cout << "Current image: " << cur->name << endl;
        cout << "Using next: " << cur->next->name << endl;
        cout << "Using prev: " << cur->prev->name << endl;
    }
};

int main() {
    Gallery g;
    g.insert("beach.jpg");
    g.insert("mountain.jpg");
    g.insert("city.png");
    g.insert("sunset.jpg");
    g.insert("forest.png");

    cout << "First to last:" << endl;
    g.showForward();

    cout << "\nLast to first:" << endl;
    g.showBackward();

    cout << endl;
    g.navigate();

    return 0;
}
