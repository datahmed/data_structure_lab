#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    string name;
    int id;
    int priority;
    Patient* left;
    Patient* right;
};

Patient* heap[50];
int n = 0;

void link() {
    for (int i = 0; i < n; i++) {
        int l = 2 * i + 1, r = 2 * i + 2;
        heap[i]->left = l < n ? heap[l] : NULL;
        heap[i]->right = r < n ? heap[r] : NULL;
    }
}

void up(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p]->priority >= heap[i]->priority) break;
        swap(heap[p], heap[i]);
        i = p;
    }
}

void down(int i) {
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, big = i;
        if (l < n && heap[l]->priority > heap[big]->priority) big = l;
        if (r < n && heap[r]->priority > heap[big]->priority) big = r;
        if (big == i) break;
        swap(heap[i], heap[big]);
        i = big;
    }
}

void addPatient(string name, int id, int pr) {
    Patient* p = new Patient;
    p->name = name;
    p->id = id;
    p->priority = pr;
    p->left = p->right = NULL;
    heap[n] = p;
    n++;
    up(n - 1);
    link();
}

void show() {
    if (n == 0) {
        cout << "No patients waiting" << endl;
        return;
    }
    queue<Patient*> q;
    q.push(heap[0]);
    int level = 0;
    while (!q.empty()) {
        int sz = q.size();
        cout << "Level " << level << ": ";
        for (int i = 0; i < sz; i++) {
            Patient* cur = q.front();
            q.pop();
            cout << cur->name << "(ID " << cur->id << ", P" << cur->priority << ")  ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << endl;
        level++;
    }
}

void treat() {
    if (n == 0) return;
    Patient* done = heap[0];
    cout << "Treated and removed: " << done->name << " (ID " << done->id << ")" << endl;
    heap[0] = heap[n - 1];
    n--;
    delete done;
    down(0);
    link();
}

int main() {
    addPatient("Kamran", 11, 4);
    addPatient("Nimra", 12, 9);
    addPatient("Farhan", 13, 6);
    addPatient("Hira", 14, 10);
    addPatient("Taimoor", 15, 3);
    addPatient("Mehwish", 16, 7);
    addPatient("Rehan", 17, 8);

    cout << "All patients (level order):" << endl;
    show();

    cout << endl << "Highest priority patient: " << heap[0]->name << " (ID " << heap[0]->id << ", priority " << heap[0]->priority << ")" << endl;

    cout << endl;
    treat();

    cout << endl << "Heap after heapify down:" << endl;
    show();

    cout << endl << "Next patient to treat: " << heap[0]->name << " (ID " << heap[0]->id << ", priority " << heap[0]->priority << ")" << endl;
    return 0;
}
