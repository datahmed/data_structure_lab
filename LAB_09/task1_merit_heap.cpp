#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Student {
    string name;
    int roll;
    int marks;
    Student* left;
    Student* right;
};

Student* heap[50];
int n = 0;

void link() {
    for (int i = 0; i < n; i++) {
        int l = 2 * i + 1, r = 2 * i + 2;
        heap[i]->left = l < n ? heap[l] : NULL;
        heap[i]->right = r < n ? heap[r] : NULL;
    }
}

void heapifyUp(int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p]->marks >= heap[i]->marks) break;
        swap(heap[p], heap[i]);
        i = p;
    }
}

void heapifyDown(int i) {
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, big = i;
        if (l < n && heap[l]->marks > heap[big]->marks) big = l;
        if (r < n && heap[r]->marks > heap[big]->marks) big = r;
        if (big == i) break;
        swap(heap[i], heap[big]);
        i = big;
    }
}

void insertStudent(string name, int roll, int marks) {
    Student* s = new Student;
    s->name = name;
    s->roll = roll;
    s->marks = marks;
    s->left = s->right = NULL;
    heap[n] = s;
    n++;
    heapifyUp(n - 1);
    link();
    cout << "Inserted " << name << " (" << marks << ")" << endl;
}

void show() {
    if (n == 0) {
        cout << "Heap is empty" << endl;
        return;
    }
    queue<Student*> q;
    q.push(heap[0]);
    int level = 0;
    while (!q.empty()) {
        int sz = q.size();
        cout << "Level " << level << ": ";
        for (int i = 0; i < sz; i++) {
            Student* cur = q.front();
            q.pop();
            cout << cur->name << "(" << cur->roll << ", " << cur->marks << ")  ";
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << endl;
        level++;
    }
}

void deleteTop() {
    if (n == 0) return;
    Student* gone = heap[0];
    cout << "Deleted: " << gone->name << " with marks " << gone->marks << endl;
    heap[0] = heap[n - 1];
    n--;
    delete gone;
    heapifyDown(0);
    link();
}

int main() {
    insertStudent("Ali", 101, 72);
    insertStudent("Sara", 102, 88);
    insertStudent("Hamza", 103, 65);
    insertStudent("Ayesha", 104, 91);
    insertStudent("Bilal", 105, 79);
    insertStudent("Zainab", 106, 84);
    insertStudent("Usman", 107, 95);

    cout << endl << "Merit list (level order):" << endl;
    show();

    cout << endl;
    deleteTop();

    cout << endl << "After heapify down:" << endl;
    show();
    return 0;
}
