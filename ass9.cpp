#include <iostream>
using namespace std;

#define MAX 100

struct Request {
    string name;
    int priority;
};

class PriorityQueue {
    Request heap[MAX];
    int size = 0;

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[i].priority > heap[parent].priority) {
                swap(heap[i], heap[parent]);
                i = parent;
            } else break;
        }
    }

    void heapifyDown(int i) {
        while (true) {
            int left = 2*i + 1;
            int right = 2*i + 2;
            int largest = i;

            if (left < size && heap[left].priority > heap[largest].priority)
                largest = left;

            if (right < size && heap[right].priority > heap[largest].priority)
                largest = right;

            if (largest != i) {
                swap(heap[i], heap[largest]);
                i = largest;
            } else break;
        }
    }

public:
    void insert(string name, int priority) {
        if (size == MAX) {
            cout << "Queue Overflow\n";
            return;
        }

        heap[size] = {name, priority};
        heapifyUp(size);
        size++;
        cout << "Request added!\n";
    }

    void processRequest() {
        if (size == 0) {
            cout << "No requests\n";
            return;
        }

        cout << "Processing: " << heap[0].name 
             << " (Priority " << heap[0].priority << ")\n";

        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
    }

    void display() {
        if (size == 0) {
            cout << "Queue is empty\n";
            return;
        }

        cout << "Current Requests:\n";
        for (int i = 0; i < size; i++) {
            cout << heap[i].name << " (" << heap[i].priority << ")\n";
        }
    }

    void swap(Request &a, Request &b){
        Request temp = a;
        a = b;
        b = temp;
    }
};

int main() {
    PriorityQueue pq;
    int choice;
    string name;
    int priority;

    while (true) {
        cout << "\n===== Customer Support Menu =====\n";
        cout << "1. Add Request\n";
        cout << "2. Process Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cin.ignore();
                cout << "Enter issue: ";
                getline(cin, name);

                cout << "Enter priority (3-Urgent, 2-Moderate, 1-Routine): ";
                cin >> priority;

                pq.insert(name, priority);
                break;

            case 2:
                pq.processRequest();
                break;

            case 3:
                pq.display();
                break;

            case 4:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}