#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 100
#define INF 999999

int keys[MAX], freq[MAX];
int cost[MAX][MAX], root[MAX][MAX], weight[MAX][MAX];

// Inorder Traversal
void printInorder(int i, int j) {
    if (i >= j) return;

    int r = root[i][j];
    printInorder(i, r - 1);         // Left subtree
    cout << keys[r] << " ";         // Root
    printInorder(r, j);             // Right subtree
}

// Print Tree Structure (Node - Left - Right)
void printStructure(int i, int j) {
    if (i >= j) return;

    int r = root[i][j];
    int left = root[i][r - 1];
    int right = root[r][j];

    cout << keys[r] << "\t";
    if (left) {
        cout << keys[left] << "\t";
    } else {
        cout << "-\t";
    }

    if (right) {
        cout << keys[right] << "\n";
    } else {
        cout << "-\n";
    }

    printStructure(i, r - 1);  // Left subtree
    printStructure(r, j);      // Right subtree
}

// Display matrix
void displayMatrix(int mat[MAX][MAX], int n, string label) {
    cout << "\n" << label << ":\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i > j) cout << setw(5) << "-";
            else cout << setw(5) << mat[i][j];
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cout << "Enter key " << i << ": ";
        cin >> keys[i];
        cout << "Enter the corresponding frequency of key: ";
        cin >> freq[i];
    }

    // Initialize diagonals
    for (int i = 0; i <= n; i++) {
        cost[i][i] = 0;
        weight[i][i] = 0;
    }

    // OBST Construction
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len;
            cost[i][j] = INF;
            weight[i][j] = weight[i][j - 1] + freq[j];

            for (int k = i + 1; k <= j; k++) {
                int temp = cost[i][k - 1] + cost[k][j] + weight[i][j];
                if (temp < cost[i][j]) {
                    cost[i][j] = temp;
                    root[i][j] = k;
                }
            }
        }
    }

    // Output
    cout << "\nMinimum Cost of OBST: " << cost[0][n];
    cout << "\nRoot of OBST: " << keys[root[0][n]];

    // Inorder
    cout << "\n\nInorder Traversal of OBST: ";
    printInorder(0, n);

    // Structure
    cout << "\n\nStructure of OBST:\n";
    cout << "NODE\tLEFT\tRIGHT\n";
    printStructure(0, n);

    // Matrices
    displayMatrix(cost, n, "Cost Matrix");
    displayMatrix(root, n, "Root Matrix");

    return 0;
}
