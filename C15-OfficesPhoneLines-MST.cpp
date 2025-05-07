#include <iostream>
#include <string>
using namespace std;

#define MAX 50

class Node {
public:
    string city;
    int weight;
    Node* next;

    Node(string c, int w) : city(c), weight(w), next(NULL) {}
};

class OfficeGraph {
    string offices[MAX];
    int matrix[MAX][MAX];
    Node* adjList[MAX];
    int numO;
    bool costEntered;

public:
    OfficeGraph() : numO(0), costEntered(false) {
        for(int i=0; i<MAX; i++) {
            adjList[i] = NULL;
            for(int j=0; j<MAX; j++)
                matrix[i][j] = 0;
        }
    }

    void createO();
    void setupCostMatrix();
    void displayMatrix();
    void displayList();
    bool isConnected(bool useMatrix);
    void findMST(bool useMatrix);
    int getIndex(string city);

private:
    void buildAdjList();
    void bfsMatrix(int start, bool visited[]);
    void bfsList(int start, bool visited[]);
    int findMinKey(int key[], bool mstSet[]);
};

void OfficeGraph::createO() {
    cout << "\nEnter number of offices: ";
    cin >> numO;
    cout << "Enter office names:\n";
    for(int i=0; i<numO; i++) {
        cout << "Office " << i+1 << ": ";
        cin >> offices[i];
    }
}

void OfficeGraph::setupCostMatrix() {
    cout << "\nEnter installation cost between offices:\n";
    for (int i = 0; i < numO; i++) {
        for (int j = i + 1; j < numO; j++) {
            cout << offices[i] << " and " << offices[j] << ": ";
            cin >> matrix[i][j];
            matrix[j][i] = matrix[i][j];
        }
    }
    costEntered = true;
    buildAdjList();  // Build adjacency list from matrix
    cout << "Costs entered successfully!\n";
}

void OfficeGraph::buildAdjList() {
    for (int i = 0; i < numO; i++)
        adjList[i] = NULL;

    for (int i = 0; i < numO; i++) {
        for (int j = 0; j < numO; j++) {
            if (matrix[i][j] != 0) {
                Node* newNode = new Node(offices[j], matrix[i][j]);
                newNode->next = adjList[i];
                adjList[i] = newNode;
            }
        }
    }
}

void OfficeGraph::displayMatrix() {
    if (!costEntered) {
        cout << "Enter installation costs first!\n";
        return;
    }
    cout << "\nAdjacency Matrix:\n\t";
    for(int i=0; i<numO; i++)
        cout << offices[i] << "\t";
    cout << "\n";
    for (int i = 0; i < numO; i++) {
        cout << offices[i] << "\t";
        for (int j = 0; j < numO; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void OfficeGraph::displayList() {
    if (!costEntered) {
        cout << "Enter installation costs first!\n";
        return;
    }
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < numO; i++) {
        cout << offices[i] << " -> ";
        Node* temp = adjList[i];
        while (temp) {
            cout << temp->city << "(" << temp->weight << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

int OfficeGraph::getIndex(string city) {
    for(int i=0; i<numO; i++)
        if(offices[i] == city) return i;
    return -1;
}

bool OfficeGraph::isConnected(bool useMatrix) {
    if (!costEntered) return false;

    bool visited[MAX];
    for(int i = 0; i < numO; ++i)
        visited[i] = false;

    if(useMatrix) bfsMatrix(0, visited);
    else bfsList(0, visited);

    for(int i=0; i<numO; i++)
        if(!visited[i])
            return false;

    return true;
}

void OfficeGraph::bfsMatrix(int start, bool visited[]) {
    int queue[MAX], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = true;

    while(front != rear) {
        int u = queue[front++];
        for(int v=0; v<numO; v++) {
            if(matrix[u][v] && !visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
        }
    }
}

void OfficeGraph::bfsList(int start, bool visited[]) {
    int queue[MAX], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = true;

    while(front != rear) {
        int u = queue[front++];
        Node* current = adjList[u];
        while(current) {
            int v = getIndex(current->city);
            if(v != -1 && !visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
            }
            current = current->next;
        }
    }
}

int OfficeGraph::findMinKey(int key[], bool mstSet[]) {
    int min = 99999, min_index = -1;
    for(int v=0; v<numO; v++)
        if(!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void OfficeGraph::findMST(bool useMatrix) {
    if (!costEntered) {
        cout << "Enter installation costs first!\n";
        return;
    }
    if (!isConnected(useMatrix)) {
        cout << "Graph is not connected. MST not possible!\n";
        return;
    }

    int parent[MAX], key[MAX];
    bool mstSet[MAX];

    for(int i=0; i<numO; i++) {
        key[i] = 99999;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for(int count=0; count<numO-1; count++) {
        int u = findMinKey(key, mstSet);
        mstSet[u] = true;

        if(useMatrix) {
            for(int v=0; v<numO; v++) {
                if(matrix[u][v] && !mstSet[v] && matrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = matrix[u][v];
                }
            }
        } else {
            Node* current = adjList[u];
            while(current) {
                int v = getIndex(current->city);
                if(v != -1 && !mstSet[v] && current->weight < key[v]) {
                    parent[v] = u;
                    key[v] = current->weight;
                }
                current = current->next;
            }
        }
    }

    cout << "\nMinimum Spanning Tree (";
    cout << (useMatrix ? "Matrix" : "List") << "):\n";
    int total = 0;
    for(int i=1; i<numO; i++) {
        cout << offices[parent[i]] << " - " << offices[i] 
             << " (Cost: " << key[i] << ")\n";
        total += key[i];
    }
    cout << "Total Minimum Cost: " << total << endl;
}

// ------------------ MAIN ------------------
int main() {
    OfficeGraph og;
    int choice;
    char cont;

    do {
        cout << "\nOffice Connections Management\n";
        cout << "1. Create Offices\n";
        cout << "2. Enter Installation Costs\n";
        cout << "3. Display Adjacency Matrix\n";
        cout << "4. Display Adjacency List\n";
        cout << "5. Find MST using Matrix\n";
        cout << "6. Find MST using List\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                og.createO();
                break;
            case 2:
                og.setupCostMatrix();
                break;
            case 3:
                og.displayMatrix();
                break;
            case 4:
                og.displayList();
                break;
            case 5:
                og.findMST(true);
                break;
            case 6:
                og.findMST(false);
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }

        cout << "\nContinue? (y/n): ";
        cin >> cont;
    } while(tolower(cont) == 'y');

    return 0;
}
