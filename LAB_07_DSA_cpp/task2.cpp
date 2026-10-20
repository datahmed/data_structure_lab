#include <iostream>
using namespace std;

#define SIZE 5

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
        pr = (pr + 1) % SIZE;
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
    if (pf == pr) {
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

int main()
{
    int ch, id;
    do {
        cout << "\n--- Network Packet Buffer ---\n";
        cout << "1. Insert packet\n2. Transmit packet\n3. Display packets\n0. Exit\n";
        cout << "Choice: ";
        cin >> ch;
        if (ch == 1) {
            cout << "Packet ID: ";
            cin >> id;
            addPacket(id);
        }
        else if (ch == 2) sendPacket();
        else if (ch == 3) showPackets();
        else if (ch == 0) cout << "Bye!\n";
        else cout << "wrong choice\n";
    } while (ch != 0);
    return 0;
}
