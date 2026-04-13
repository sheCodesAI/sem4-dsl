#include <iostream>
#include <iomanip>

using namespace std;

#define SIZE 10

class OBST {
    double p[SIZE];        // Success probabilities
    double q[SIZE];        // Failure probabilities
    int a[SIZE];           // Keys/Data
    double w[SIZE][SIZE];  // Weight table
    double c[SIZE][SIZE];  // Cost table
    int r[SIZE][SIZE];     // Root table
    int n;                 // Number of nodes

public:
    void get_data() {
        cout << "\n--- Input Data ---" << endl;
        cout << "Enter the number of nodes (max 9): ";
        cin >> n;

        cout << "Enter the keys (in sorted order):" << endl;
        for (int i = 1; i <= n; i++) {
            cout << "a[" << i << "]: ";
            cin >> a[i];
        }

        cout << "Enter probabilities 'p' (Success):" << endl;
        for (int i = 1; i <= n; i++) {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }

        cout << "Enter probabilities 'q' (Failure/Dummy):" << endl;
        for (int i = 0; i <= n; i++) {
            cout << "q[" << i << "]: ";
            cin >> q[i];
        }
    }

    // Finds the root k that minimizes c[i][k-1] + c[k][j]
    int Min_Value(int i, int j) {
        double min_cost = 999.0;
        int k_index = 0;

        for (int k = i + 1; k <= j; k++) {
            double val = c[i][k - 1] + c[k][j];
            if (val < min_cost) {
                min_cost = val;
                k_index = k;
            }
        }
        return k_index;
    }

    void build_OBST() {
        // Step 1: Initialize subtrees of size 0 (dummy nodes)
        for (int i = 0; i <= n; i++) {
            w[i][i] = q[i];
            c[i][i] = 0.0;
            r[i][i] = 0;
        }

        // Step 2: Build tables for subtree sizes m = 1 to n
        for (int m = 1; m <= n; m++) {
            for (int i = 0; i <= n - m; i++) {
                int j = i + m;
                w[i][j] = w[i][j - 1] + p[j] + q[j];
                int k = Min_Value(i, j);
                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
                r[i][j] = k;
            }
        }
        cout << "\nOptimal tables built successfully!" << endl;
    }

    void display_results() {
        cout << fixed << setprecision(2);
        cout << "\nFinal Cost of OBST: " << c[0][n] << endl;
        cout << "Root of the Tree: " << a[r[0][n]] << endl;

        cout << "\n--- Root Table (R) ---" << endl;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (j < i) cout << "-\t";
                else cout << r[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void build_tree() {
        if (n == 0) return;
        
        int queue[40], front = -1, rear = -1;
        cout << "\n--- Tree Structure (Level Order) ---" << endl;
        cout << "PARENT\tLEFT\tRIGHT" << endl;

        // Push the main range [0, n] to the queue
        queue[++rear] = 0;
        queue[++rear] = n;

        while (front != rear) {
            int i = queue[++front];
            int j = queue[++front];
            int k = r[i][j];

            if (k != 0) {
                cout << a[k] << "\t";

                // Left Child check
                if (r[i][k - 1] != 0) {
                    cout << a[r[i][k - 1]] << "\t";
                    queue[++rear] = i;
                    queue[++rear] = k - 1;
                } else {
                    cout << "None\t";
                }

                // Right Child check
                if (r[k][j] != 0) {
                    cout << a[r[k][j]] << endl;
                    queue[++rear] = k;
                    queue[++rear] = j;
                } else {
                    cout << "None" << endl;
                }
            }
        }
    }
};

int main() {
    OBST tree;
    int choice;

    do {
        cout << "\n==========================";
        cout << "\n   OBST MENU (Asst 8)";
        cout << "\n==========================";
        cout << "\n1. Enter Data";
        cout << "\n2. Calculate OBST";
        cout << "\n3. Display Tables/Cost";
        cout << "\n4. Show Tree structure";
        cout << "\n5. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: tree.get_data(); break;
            case 2: tree.build_OBST(); break;
            case 3: tree.display_results(); break;
            case 4: tree.build_tree(); break;
            case 5: cout << "Exiting program..." << endl; break;
            default: cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}