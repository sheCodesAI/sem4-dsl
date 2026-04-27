#include <iostream>
using namespace std;

#define MAX 100

struct Customer {
    string name;
    int priority;
    int arrivalTime;
};

class MinHeap {
    Customer heap[MAX];
    int size;
    int timer;

public:
    MinHeap() {
        size = 0;
        timer = 0;
    }

    bool higherPriority(Customer a, Customer b) {
        if (a.priority == b.priority)
            return a.arrivalTime < b.arrivalTime;
        return a.priority < b.priority;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (higherPriority(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }

    void heapifyDown(int index) {
        while (index < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && higherPriority(heap[left], heap[smallest]))
                smallest = left;

            if (right < size && higherPriority(heap[right], heap[smallest]))
                smallest = right;

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else break;
        }
    }

    void addCustomer(string name, int priority) {
        if (size == MAX) {
            cout << "Queue Full\n";
            return;
        }

        heap[size].name = name;
        heap[size].priority = priority;
        heap[size].arrivalTime = timer++;

        heapifyUp(size);
        size++;
    }

    void serveCustomer() {
        if (size == 0) {
            cout << "No customers\n";
            return;
        }

        cout << "Serving: " << heap[0].name
             << " (Priority: " << heap[0].priority << ")\n";

        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }

    void display() {
        if (size == 0) {
            cout << "Queue is empty\n";
            return;
        }

        cout << "Customers in Queue:\n";
        for (int i = 0; i < size; i++) {
            cout << heap[i].name << "("
                 << heap[i].priority << ") ";
        }
        cout << endl;
    }
};

int main() {
    MinHeap service;
    int choice, priority;
    string name;

    do {
        cout << "\n--- Customer Service Menu ---\n";
        cout << "1. Add Customer\n";
        cout << "2. Serve Customer\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter customer name: ";
                cin >> name;
                cout << "Enter priority (1=Urgent, 2=Moderate, 3=Normal): ";
                cin >> priority;
                service.addCustomer(name, priority);
                break;

            case 2:
                service.serveCustomer();
                break;

            case 3:
                service.display();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 4);

    return 0;
}