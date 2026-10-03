#include <iostream>
#include <string>
using namespace std;

// Node for doubly linked list
class Node {
public:
    string site;
    Node* prev;
    Node* next;

    Node(string s) {
        site = s;
        prev = NULL;
        next = NULL;
    }
};

class BrowserHistory {
private:
    Node* head;
    Node* tail;

public:
    BrowserHistory() {
        head = NULL;
        tail = NULL;
    }

    // add a new visited website at the end
    void visit(string site) {
        Node* newNode = new Node(site);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // first visited -> last visited (using next)
    void showForward() {
        cout << "History (first -> last):" << endl;
        Node* temp = head;
        int i = 1;
        while (temp != NULL) {
            cout << i++ << ". " << temp->site << endl;
            temp = temp->next;
        }
    }

    // last visited -> first visited (using prev)
    void showBackward() {
        cout << "History (last -> first):" << endl;
        Node* temp = tail;
        int i = 1;
        while (temp != NULL) {
            cout << i++ << ". " << temp->site << endl;
            temp = temp->prev;
        }
    }

    ~BrowserHistory() {
        Node* temp = head;
        while (temp != NULL) {
            Node* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
    }
};

int main() {
    BrowserHistory h;
    h.visit("google.com");
    h.visit("youtube.com");
    h.visit("github.com");
    h.visit("stackoverflow.com");
    h.visit("wikipedia.org");

    h.showForward();
    cout << endl;
    h.showBackward();
    return 0;
}
