#include <iostream>
using namespace std;

class Node {
public:
    string player;
    Node* next;
    Node(string p) {
        player = p;
        next = NULL;
    }
};

class Game {
    Node *head, *tail;
public:
    Game() { head = tail = NULL; }

    void addPlayer(string name) {
        Node* n = new Node(name);
        if (head == NULL) {
            head = tail = n;
        }
        else {
            tail->next = n;
            tail = n;
        }
        tail->next = head;   // makes it circular
    }

    void showTurns() {
        Node* temp = head;
        int turn = 1;
        do {
            cout << "Turn " << turn << ": " << temp->player << endl;
            temp = temp->next;
            turn++;
        } while (temp != head);
    }

    void backToFirst() {
        cout << "After " << tail->player << " the turn goes to "
             << tail->next->player << endl;
    }
};

int main() {
    Game g;
    g.addPlayer("Ali");
    g.addPlayer("Sara");
    g.addPlayer("Hamza");
    g.addPlayer("Ayesha");
    g.addPlayer("Bilal");

    g.showTurns();
    cout << endl;
    g.backToFirst();

    return 0;
}
