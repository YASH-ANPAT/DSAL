#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int value) {
        data = value;
        left = right = NULL;
    }
};

// Custom stack for Node pointers
class Stack {
    Node* arr[100];
    int top;
public:
    Stack() { top = -1; }
    void push(Node* node) {
        if (top < 99)
            arr[++top] = node;
    }
    Node* pop() {
        if (top >= 0)
            return arr[top--];
        return NULL;
    }
    Node* peek() {
        if (top >= 0)
            return arr[top];
        return NULL;
    }
    bool isEmpty() {
        return top == -1;
    }
};

// Custom queue for Node pointers (for Level Order)
class Queue {
    Node* arr[100];
    int front, rear;
public:
    Queue() {
        front = rear = -1;
    }
    void enqueue(Node* node) {
        if (rear < 99) {
            if (front == -1) front = 0;
            arr[++rear] = node;
        }
    }
    Node* dequeue() {
        if (front == -1 || front > rear) return NULL;
        return arr[front++];
    }
    bool isEmpty() {
        return front == -1 || front > rear;
    }
};

class BST {
    Node *root;

public:
    BST() { root = NULL; }

    Node* insert(Node* node, int value) {
        if (node == NULL)
            return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);
        return node;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    int height(Node* node) {
        if (node == NULL)
            return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

    int getHeight() {
        return height(root);
    }

    int Min() {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return -1;
        }
        Node* temp = root;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp->data;
    }

    void mirror(Node* node) {
        if (node == NULL)
            return;

        if (node->left != NULL && node->right != NULL) {
            cout << "Swapping " << node->left->data << " <-> " << node->right->data << endl;
        } else if (node->left != NULL) {
            cout << "Swapping " << node->left->data << " <-> NULL" << endl;
        } else if (node->right != NULL) {
            cout << "Swapping NULL <-> " << node->right->data << endl;
        }

        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        mirror(node->left);
        mirror(node->right);
    }

    void mirrorTree() {
        mirror(root);
    }

    bool search(Node* node, int key) {
        while (node != NULL) {
            if (key == node->data)
                return true;
            else if (key < node->data)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }

    bool searchTree(int key) {
        return search(root, key);
    }

    void inorderTraversal() {
        cout << "Inorder BST: ";
        Stack s;
        Node* curr = root;

        while (curr != NULL || !s.isEmpty()) {
            while (curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
        cout << endl;
    }

    void levelOrderTraversal() {
        cout << "Level Order BST: ";
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }

        Queue q;
        q.enqueue(root);

        while (!q.isEmpty()) {
            Node* current = q.dequeue();
            cout << current->data << " ";

            if (current->left != NULL)
                q.enqueue(current->left);
            if (current->right != NULL)
                q.enqueue(current->right);
        }
        cout << endl;
    }
};

int main() {
    BST tree;
    int choice, value;
    char ans;
    do {
        cout << "\nMENU:\n";
        cout << "1. Insert new node\n";
        cout << "2. Find nodes in longest path\n";
        cout << "3. Find min data value\n";
        cout << "4. Mirror the tree\n";
        cout << "5. Search a value\n";
        cout << "6. Display (Inorder)\n";
        cout << "7. Display (Level Order)\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter new node value: ";
            cin >> value;
            tree.insert(value);
            tree.inorderTraversal();
            break;
        case 2:
            cout << "Nodes in longest path: " << tree.getHeight() << endl;
            break;
        case 3:
            cout << "Minimum value in BST: " << tree.Min() << endl;
            break;
        case 4:
            cout << "Tree before mirroring (Inorder Traversal): ";
            tree.inorderTraversal();
            tree.mirrorTree();
            cout << "Tree after mirroring (Inorder Traversal): ";
            tree.inorderTraversal();
            break;
        case 5:
            cout << "Enter value to search: ";
            cin >> value;
            if (tree.searchTree(value))
                cout << "Key found!\n";
            else
                cout << "Key not found!\n";
            break;
        case 6:
            tree.inorderTraversal();
            break;
        case 7:
            tree.levelOrderTraversal();
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
        cout << "Do you want to continue? (y/n): ";
        cin >> ans;
        cout << "-----------------------------------\n";
    } while (ans == 'y' || ans == 'Y');
    return 0;
}
