#include <iostream>
using namespace std;

class Node {
public:
    string song;
    Node* next;
    Node(string s) {
        song = s;
        next = NULL;
    }
};

class Playlist {
    Node *head, *tail;
public:
    Playlist() { head = tail = NULL; }

    void addSong(string name) {
        Node* n = new Node(name);
        if (head == NULL) {
            head = tail = n;
        }
        else {
            tail->next = n;
            tail = n;
        }
        tail->next = head;
    }

    void display() {
        Node* temp = head;
        do {
            cout << temp->song << endl;
            temp = temp->next;
        } while (temp != head);
    }

    void play(int rounds) {
        Node* temp = head;
        for (int i = 1; i <= rounds; i++) {
            cout << "Round " << i << endl;
            do {
                cout << "Playing " << temp->song << endl;
                temp = temp->next;   // goes back to first after the last song
            } while (temp != head);
        }
    }
};

int main() {
    Playlist p;
    p.addSong("Tum Hi Ho");
    p.addSong("Kesariya");
    p.addSong("Believer");
    p.addSong("Shape of You");
    p.addSong("Perfect");

    cout << "All songs:" << endl;
    p.display();

    cout << endl;
    p.play(2);

    return 0;
}
