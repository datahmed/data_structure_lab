#include <iostream>
using namespace std;

#define SIZE 5

int dq[SIZE];
int df = -1, dr = -1;

bool dqFull()  { return (df == 0 && dr == SIZE - 1) || (df == dr + 1); }
bool dqEmpty() { return df == -1; }

void insertFront(int x)
{
    if (dqFull()) { cout << "Deque is FULL, cant insert " << x << " at front.\n"; return; }
    if (dqEmpty()) { df = 0; dr = 0; }
    else if (df == 0) df = SIZE - 1;
    else df--;
    dq[df] = x;
    cout << x << " inserted at front.\n";
}

void insertRear(int x)
{
    if (dqFull()) { cout << "Deque is FULL, cant insert " << x << " at rear.\n"; return; }
    if (dqEmpty()) { df = 0; dr = 0; }
    else if (dr == SIZE - 1) dr = 0;
    else dr++;
    dq[dr] = x;
    cout << x << " inserted at rear.\n";
}

void removeFront()
{
    if (dqEmpty()) { cout << "Deque is EMPTY, nothing to remove from front.\n"; return; }
    cout << "Removed " << dq[df] << " from front.\n";
    if (df == dr) { df = -1; dr = -1; }
    else if (df == SIZE - 1) df = 0;
    else df++;
}

void removeRear()
{
    if (dqEmpty()) { cout << "Deque is EMPTY, nothing to remove from rear.\n"; return; }
    cout << "Removed " << dq[dr] << " from rear.\n";
    if (df == dr) { df = -1; dr = -1; }
    else if (dr == 0) dr = SIZE - 1;
    else dr--;
}

void showDeque()
{
    if (dqEmpty()) { cout << "Deque is empty.\n"; return; }
    cout << "Front -> ";
    int i = df;
    while (true) {
        cout << dq[i] << " ";
        if (i == dr) break;
        i = (i + 1) % SIZE;
    }
    cout << "<- Rear\n";
}

int main()
{
    int ch, x;
    do {
        cout << "\n--- Train Station Requests (Deque) ---\n";
        cout << "1. Insert at front\n2. Insert at rear\n3. Remove from front\n";
        cout << "4. Remove from rear\n5. Display (front to rear)\n0. Exit\n";
        cout << "Choice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "Request ID: "; cin >> x; insertFront(x); break;
        case 2: cout << "Request ID: "; cin >> x; insertRear(x); break;
        case 3: removeFront(); break;
        case 4: removeRear(); break;
        case 5: showDeque(); break;
        case 0: cout << "Bye!\n"; break;
        default: cout << "wrong choice\n";
        }
    } while (ch != 0);
    return 0;
}
