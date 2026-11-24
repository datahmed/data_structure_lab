#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Medicine {
    string name;
    int id;
    int expiry;
    Medicine* left;
    Medicine* right;
};

Medicine* heap[50];
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
        if (heap[p]->expiry <= heap[i]->expiry) break;
        swap(heap[p], heap[i]);
        i = p;
    }
}

void down(int i) {
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, small = i;
        if (l < n && heap[l]->expiry < heap[small]->expiry) small = l;
        if (r < n && heap[r]->expiry < heap[small]->expiry) small = r;
        if (small == i) break;
        swap(heap[i], heap[small]);
        i = small;
    }
}

void addMedicine(string name, int id, int exp) {
    Medicine* m = new Medicine;
    m->name = name;
    m->id = id;
    m->expiry = exp;
    m->left = m->right = NULL;
    heap[n] = m;
    n++;
    up(n - 1);
    link();
}

void show() {
    if (n == 0) {
        cout << "No medicines in store" << endl;
        return;
    }
    queue<Medicine*> q;
    q.push(heap[0]);
    int level = 0;
    while (!q.empty()) {
        int sz = q.size();
        cout << "Level " << level << ": ";
        for (int i = 0; i < sz; i++) {
            Medicine* cur = q.front();
            q.pop();
            cout << cur->name << "(ID " << cur->id << ", " << cur->expiry << ")  ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << endl;
        level++;
    }
}

int main() {
    addMedicine("Panadol", 301, 20270315);
    addMedicine("Brufen", 302, 20261120);
    addMedicine("Augmentin", 303, 20280510);
    addMedicine("Disprin", 304, 20260830);
    addMedicine("Calpol", 305, 20271201);
    addMedicine("Amoxil", 306, 20261005);
    addMedicine("Ponstan", 307, 20270722);

    cout << "Medicine heap (level order):" << endl;
    show();

    cout << endl << "Nearest expiry: " << heap[0]->name << " (ID " << heap[0]->id << ", " << heap[0]->expiry << ")" << endl;

    Medicine* old = heap[0];
    cout << "Deleting " << old->name << endl;
    heap[0] = heap[n - 1];
    n--;
    delete old;
    down(0);
    link();

    cout << endl << "Heap after heapify down:" << endl;
    show();
    return 0;
}
