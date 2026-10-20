#include <iostream>
#include <string>
using namespace std;

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

int main()
{
    int ch, p;
    string id;
    do {
        cout << "\n--- Hospital Emergency Department ---\n";
        cout << "(priority 1 = most urgent)\n";
        cout << "1. Add patient\n2. Treat next patient\n3. Display waiting patients\n0. Exit\n";
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
        else if (ch == 0) cout << "Bye!\n";
        else cout << "wrong choice\n";
    } while (ch != 0);
    return 0;
}
