// DSA LAB 07 - Queues (simple, circular, priority, deque)
// Muhammad Ahmad Nadeem - 2502450

#include <iostream>
#include <string>
using namespace std;

#define SIZE 5   // keeping it small so overflow is easy to show

// ---------------------------------------------------------
// TASK 1 : Bank customer service - simple linear queue
// ---------------------------------------------------------
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
    // once everyone is served, reset
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

void task1()
{
    int ch, t;
    do {
        cout << "\n--- Bank Customer Service ---\n";
        cout << "1. Add customer (enqueue)\n2. Serve customer (dequeue)\n";
        cout << "3. Display waiting customers\n4. Number of waiting customers\n0. Back\n";
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
        case 0: break;
        default: cout << "wrong choice\n";
        }
    } while (ch != 0);
}

// ---------------------------------------------------------
// TASK 2 : Network packets - circular queue
// ---------------------------------------------------------
int pkt[SIZE];
int pf = -1, pr = -1;

bool pktFull()  { return (pf == 0 && pr == SIZE - 1) || (pr + 1) % SIZE == pf; }
bool pktEmpty() { return pf == -1; }

void addPacket(int id)
{
    if (pktFull()) {
        cout << "Buffer is FULL, packet " << id << " dropped.\n";
        return;
    }
    if (pktEmpty()) {
        pf = 0;
        pr = 0;
    } else {
        pr = (pr + 1) % SIZE;      // wraps around
    }
    pkt[pr] = id;
    cout << "Packet " << id << " stored at index " << pr << endl;
}

void sendPacket()
{
    if (pktEmpty()) {
        cout << "Buffer is EMPTY, nothing to transmit.\n";
        return;
    }
    cout << "Transmitting packet " << pkt[pf] << " (index " << pf << ")\n";
    if (pf == pr) {          // that was the last one
        pf = -1;
        pr = -1;
    } else {
        pf = (pf + 1) % SIZE;
    }
}

void showPackets()
{
    if (pktEmpty()) {
        cout << "No packets waiting.\n";
        return;
    }
    cout << "Packets waiting: ";
    int i = pf;
    while (true) {
        cout << pkt[i] << "(idx" << i << ") ";
        if (i == pr) break;
        i = (i + 1) % SIZE;
    }
    cout << endl;
}

void task2()
{
    int ch, id;
    do {
        cout << "\n--- Network Packet Buffer ---\n";
        cout << "1. Insert packet\n2. Transmit packet\n3. Display packets\n0. Back\n";
        cout << "Choice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Packet ID: ";
            cin >> id;
            addPacket(id);
        }
        else if (ch == 2) sendPacket();
        else if (ch == 3) showPackets();
        else if (ch != 0) cout << "wrong choice\n";
    } while (ch != 0);
}

// ---------------------------------------------------------
// TASK 3 : Hospital emergency - priority queue using array
// smaller number = more urgent (1 is the highest priority)
// ---------------------------------------------------------
struct Patient {
    string id;
    int priority;
};

Patient er[10];
int erCount = 0;

void addPatient(string id, int p)
{
    if (erCount == 10) {
        cout << "Emergency ward is full!\n";
        return;
    }
    // shift patients with a bigger priority number (less urgent) to the right
    // equal priority -> stays behind the earlier one, so arrival order is kept
    int i = erCount - 1;
    while (i >= 0 && er[i].priority > p) {
        er[i + 1] = er[i];
        i--;
    }
    er[i + 1].id = id;
    er[i + 1].priority = p;
    erCount++;
    cout << "Patient " << id << " added with priority " << p << endl;
}

void treatPatient()
{
    if (erCount == 0) {
        cout << "No patients waiting, queue is empty.\n";
        return;
    }
    cout << "Treating patient " << er[0].id << " (priority " << er[0].priority << ")\n";
    for (int i = 0; i < erCount - 1; i++)
        er[i] = er[i + 1];
    erCount--;
}

void showPatients()
{
    if (erCount == 0) {
        cout << "No patients waiting.\n";
        return;
    }
    cout << "ID\tPriority\n";
    for (int i = 0; i < erCount; i++)
        cout << er[i].id << "\t" << er[i].priority << endl;
}

void task3()
{
    int ch, p;
    string id;
    do {
        cout << "\n--- Hospital Emergency Department ---\n";
        cout << "(priority 1 = most urgent)\n";
        cout << "1. Add patient\n2. Treat next patient\n3. Display waiting patients\n0. Back\n";
        cout << "Choice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Patient ID: ";
            cin >> id;
            cout << "Priority (1-5): ";
            cin >> p;
            addPatient(id, p);
        }
        else if (ch == 2) treatPatient();
        else if (ch == 3) showPatients();
        else if (ch != 0) cout << "wrong choice\n";
    } while (ch != 0);
}

// ---------------------------------------------------------
// TASK 4 : Train station - deque using array (circular)
// ---------------------------------------------------------
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

void task4()
{
    int ch, x;
    do {
        cout << "\n--- Train Station Requests (Deque) ---\n";
        cout << "1. Insert at front\n2. Insert at rear\n3. Remove from front\n";
        cout << "4. Remove from rear\n5. Display (front to rear)\n0. Back\n";
        cout << "Choice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "Request ID: "; cin >> x; insertFront(x); break;
        case 2: cout << "Request ID: "; cin >> x; insertRear(x); break;
        case 3: removeFront(); break;
        case 4: removeRear(); break;
        case 5: showDeque(); break;
        case 0: break;
        default: cout << "wrong choice\n";
        }
    } while (ch != 0);
}

// ---------------------------------------------------------
int main()
{
    int c;
    do {
        cout << "\n========== DSA LAB 07 ==========\n";
        cout << "1. Task 1 - Bank (Linear Queue)\n";
        cout << "2. Task 2 - Network Packets (Circular Queue)\n";
        cout << "3. Task 3 - Hospital (Priority Queue)\n";
        cout << "4. Task 4 - Train Station (Deque)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> c;
        switch (c) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 0: cout << "Bye!\n"; break;
        default: cout << "Invalid choice\n";
        }
    } while (c != 0);
    return 0;
}
