#include <iostream>
using namespace std;

const int n = 10; 

// Landmark names 
string landmarks[n] = {
    "Main Gate", "Admin", "Library", "Canteen", 
    "Auditorium", "Sports", "Hostel", "Parking", 
    "Academic", "Garden"
};

class Queue {
    int arr[n];
    int front, rear;

public:
    Queue() {
        front = rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return rear == n - 1;
    }

    void enqueue(int x) {
        if (isFull()) {
            cout << "Queue is full!\n";
            return;
        }
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear++;
        }
        arr[rear] = x;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        int val = arr[front];
        if (front == rear) {
            front = rear = -1;
        } else {
            front++;
        }
        return val;
    }
};

class Graph {
    int adjMatrix[n][n]; // For DFS
    int adjList[n][n];   // For BFS (2D array)
    int visited[n];
    int size[n];         // Tracks #neighbors per node

public:
    Graph() {
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
            size[i] = 0;
            for (int j = 0; j < n; j++) {
                adjMatrix[i][j] = 0;
                adjList[i][j] = -1; 
            }
        }
    }

    void readGraph() {
        int v, e;
        cout << "Enter number of landmarks: ";
        cin >> v;
        cout << "Enter number of connections (edges): ";
    	cin >> e;

        // Show landmark indices
        cout << "Landmark Indices:\n";
        for (int i = 0; i < v; i++) {
            cout << i << ": " << landmarks[i] << endl;
        }

        int x, y;
        for (int i = 0; i < e; i++) {
            cout << "Enter connected landmarks (x y): ";
            cin >> x >> y;
            adjMatrix[x][y] = adjMatrix[y][x] = 1;
            adjList[x][size[x]++] = y;
            adjList[y][size[y]++] = x;
        }
    }

    void dfs(int x) {
        visited[x] = 1;
        cout << landmarks[x] << " ";
        for (int i = 0; i < n; i++) {
            if (adjMatrix[x][i] == 1 && !visited[i]) {
                dfs(i);
            }
        }
    }

    void bfs(int start) {
        for (int i = 0; i < n; i++) visited[i] = 0;

        Queue q;
        q.enqueue(start);
        visited[start] = 1;

        while (!q.isEmpty()) {
            int current = q.dequeue();
            cout << landmarks[current] << " ";

            for (int i = 0; i < size[current]; i++) {
                int neighbor = adjList[current][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    q.enqueue(neighbor);
                }
            }
        }
    }
};

int main() {
    Graph g;
    g.readGraph();

    cout << "\nDFS Traversal:\n";
    g.dfs(0); 

    cout << "\n\nBFS Traversal:\n";
    g.bfs(0);

    return 0;
}
