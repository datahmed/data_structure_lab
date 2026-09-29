#include <iostream>
using namespace std;

class Node {
public:
    int rollNo;
    Node* next;

    Node(int r) {
        rollNo = r;
        next = NULL;
    }
};

void addStudent(Node*& head, int rollNo) {
    Node* newNode = new Node(rollNo);

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void display(Node* head) {
    Node* temp = head;

    cout << "Registered Students:" << endl;

    while (temp != NULL) {
        cout << temp->rollNo;

        if (temp->next != NULL)
            cout << " -> ";

        temp = temp->next;
    }

    cout << endl;
}

void searchStudent(Node* head, int rollNo) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->rollNo == rollNo) {
            cout << "Student Found" << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "Student Not Found" << endl;
}

int main() {
    Node* head = NULL;
    int n, rollNo, searchRoll;

    cout << "Enter number of students: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        addStudent(head, rollNo);
    }

    display(head);

    cout << "Enter Roll Number to Search: ";
    cin >> searchRoll;

    searchStudent(head, searchRoll);

    return 0;
}
