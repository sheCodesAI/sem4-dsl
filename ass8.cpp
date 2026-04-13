#include <iostream>
#include <climits>
using namespace std;

#define max 20

class OBST {
    int keys[max];
    int p[max], q[max];
    int weight[max][max], cost[max][max], root[max][max];
    int n;

public:
    void input() {
        cout << "Enter number of keys: " << endl;
        cin >> n;

        cout << "Enter keys (sorted):" << endl;
        for (int i = 1; i <= n; i++) cin >> keys[i];

        cout << "Enter p:" << endl;
        for (int i = 1; i <= n; i++) cin >> p[i];

        cout << "Enter q:" << endl;
        for (int i = 0; i <= n; i++) cin >> q[i];
    }

    int findMin(int i, int j) {
        int minCost = INT_MAX, best = 0;

        for (int k = root[i][j - 1]; k <= root[i + 1][j]; k++) {
            int val = cost[i][k - 1] + cost[k][j];

            if (val < minCost) {
                minCost = val;
                best = k;
            }
        }
        return best;
    }

    void buildOBST() {
        for (int i = 0; i < n; i++) {
            weight[i][i] = q[i];
            cost[i][i] = 0;
            root[i][i] = 0;

            weight[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
            cost[i][i + 1] = weight[i][i + 1];
            root[i][i + 1] = i + 1;
        }

        weight[n][n] = q[n];
        cost[n][n] = 0;
        root[n][n] = 0;

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len;

                weight[i][j] = weight[i][j - 1] + p[j] + q[j];

                int k = findMin(i, j);

                cost[i][j] = weight[i][j] + cost[i][k - 1] + cost[k][j];
                root[i][j] = k;
            }
        }
    }

    void display(int i = 0, int j = -1, int level = 0, string label = "Root") {
        if (j == -1) {
            j = n;
            cout << endl << "Optimal Cost: " << cost[0][n] << endl << endl;
        }

        if (i == j) return;

        int k = root[i][j];

        for (int x = 0; x < level; x++) {
            cout << " ";
        }

        cout << label << ": " << keys[k] << endl;

        display(i, k - 1, level + 1, "L");
        display(k, j, level + 1, "R");
    }
};

int main() {
    OBST obj;
    obj.input();
    obj.buildOBST();
    obj.display();
    return 0;
}