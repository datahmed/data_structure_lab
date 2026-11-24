#include <iostream>
#include <string>
using namespace std;

struct Order {
    int id;
    string customer;
    int amount;
    Order* left;
    Order* right;
};

Order* heap[50];
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
        if (heap[p]->amount >= heap[i]->amount) break;
        swap(heap[p], heap[i]);
        i = p;
    }
}

void down(int i) {
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, big = i;
        if (l < n && heap[l]->amount > heap[big]->amount) big = l;
        if (r < n && heap[r]->amount > heap[big]->amount) big = r;
        if (big == i) break;
        swap(heap[i], heap[big]);
        i = big;
    }
}

void addOrder(int id, string cust, int amt) {
    Order* o = new Order;
    o->id = id;
    o->customer = cust;
    o->amount = amt;
    o->left = o->right = NULL;
    heap[n] = o;
    n++;
    up(n - 1);
    link();
}

int main() {
    addOrder(5001, "Asad", 4500);
    addOrder(5002, "Maryam", 1200);
    addOrder(5003, "Junaid", 8700);
    addOrder(5004, "Sana", 2300);
    addOrder(5005, "Fahad", 6400);
    addOrder(5006, "Iqra", 950);
    addOrder(5007, "Danish", 3100);

    int total = n;
    int sorted[50];
    int k = total - 1;

    while (n > 0) {
        Order* top = heap[0];
        sorted[k] = top->amount;
        k--;
        heap[0] = heap[n - 1];
        n--;
        delete top;
        down(0);
        link();
    }

    cout << "Order amounts (smallest to largest):" << endl;
    for (int i = 0; i < total; i++) {
        cout << sorted[i] << " ";
    }
    cout << endl;
    return 0;
}
