#include <iostream>
using namespace std;

#define SIZE 5

int bankQ[SIZE];
int bfront = -1, brear = -1;

void enqueueCustomer(int token)
{
    if (brear == SIZE - 1) {
        cout << "Overflow! Counter line is full, token " << token << " cant be added.\n";
        return;
    }
    if (bfront == -1) bfront = 0;
    brear++;
    bankQ[brear] = token;
    cout << "Token " << token << " added to the line.\n";
}

void dequeueCustomer()
{
    if (bfront == -1 || bfront > brear) {
        cout << "Underflow! No customer is waiting.\n";
        return;
    }
    cout << "Serving customer with token " << bankQ[bfront] << endl;
    bfront++;
    if (bfront > brear) { bfront = -1; brear = -1; }
}

void showCustomers()
{
    if (bfront == -1) {
        cout << "No customers waiting.\n";
        return;
    }
    cout << "Waiting customers: ";
    for (int i = bfront; i <= brear; i++)
        cout << bankQ[i] << " ";
    cout << endl;
}

int countCustomers()
{
    if (bfront == -1) return 0;
    return brear - bfront + 1;
}

int main()
{
    int ch, t;
    do {
        cout << "\n--- Bank Customer Service ---\n";
        cout << "1. Add customer (enqueue)\n2. Serve customer (dequeue)\n";
        cout << "3. Display waiting customers\n4. Number of waiting customers\n0. Exit\n";
        cout << "Choice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "Enter token number: ";
            cin >> t;
            enqueueCustomer(t);
            break;
        case 2: dequeueCustomer(); break;
        case 3: showCustomers(); break;
        case 4: cout << "Customers waiting = " << countCustomers() << endl; break;
        case 0: cout << "Bye!\n"; break;
        default: cout << "wrong choice\n";
        }
    } while (ch != 0);
    return 0;
}
