#include <iostream>
using namespace std;

class Node {
public:
    string patientID;
    Node* next;

    Node(string id) {
        patientID = id;
        next = NULL;
    }
};

void addPatient(Node*& head, string id) {
    Node* newNode = new Node(id);

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

void displayQueue(Node* head) {
    Node* temp = head;

    cout << "Waiting Patients:" << endl;

    while (temp != NULL) {
        cout << temp->patientID;

        if (temp->next != NULL)
            cout << " -> ";

        temp = temp->next;
    }

    cout << endl;
}

void servePatient(Node*& head) {
    if (head == NULL) {
        cout << "No patients waiting." << endl;
        return;
    }

    Node* temp = head;
    cout << "Patient " << temp->patientID << " is being served." << endl;

    head = head->next;
    delete temp;
}

int main() {
    Node* head = NULL;
    int n;
    string patientID;

    cout << "Enter number of patients: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter Patient ID: ";
        cin >> patientID;
        addPatient(head, patientID);
    }

    displayQueue(head);

    servePatient(head);

    cout << "Updated Queue:" << endl;
    displayQueue(head);

    return 0;
}
