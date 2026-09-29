#include <iostream>
using namespace std;

class Node {
public:
    string productID;
    Node* next;

    Node(string id) {
        productID = id;
        next = NULL;
    }
};

void addProduct(Node*& head, string id) {
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

void displayCart(Node* head) {
    Node* temp = head;

    cout << "Shopping Cart:" << endl;

    while (temp != NULL) {
        cout << temp->productID;

        if (temp->next != NULL)
            cout << " -> ";

        temp = temp->next;
    }

    cout << endl;
}

void removeProduct(Node*& head, string id) {
    if (head == NULL)
        return;

    if (head->productID == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* temp = head;

    while (temp->next != NULL) {
        if (temp->next->productID == id) {
            Node* remove = temp->next;
            temp->next = remove->next;
            delete remove;
            return;
        }

        temp = temp->next;
    }
}

int main() {
    Node* head = NULL;
    int n;
    string productID;

    cout << "Enter number of products: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter Product ID: ";
        cin >> productID;
        addProduct(head, productID);
    }

    displayCart(head);

    cout << "Remove Product: ";
    cin >> productID;

    removeProduct(head, productID);

    cout << "Updated Cart:" << endl;
    displayCart(head);

    return 0;
}
