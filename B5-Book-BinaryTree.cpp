#include <iostream>
#include <string>
using namespace std;

class Tree {
    struct Node {
        string name;
        Node* left;
        Node* right;
        Node(string n) : name(n), left(NULL), right(NULL) {}
    };

    // stack class for Node pointers (used in inorder/preorder/postorder)
    class Stack {
        Node* arr[50];
        int top;
    public:
        Stack() : top(-1) {}
        void push(Node* n) {
            if (top < 49)
                arr[++top] = n;
        }
        Node* pop() {
            if (top >= 0)
                return arr[top--];
            return NULL;
        }
        bool isEmpty() {
            return top == -1;
        }
    };

    // queue class for Node pointers (used in level order)
    class Queue {
        Node* arr[50];
        int front, rear;
    public:
        Queue() : front(0), rear(0) {}
        void enqueue(Node* n) {
            if (rear < 50)
                arr[rear++] = n;
        }
        Node* dequeue() {
            if (front < rear)
                return arr[front++];
            return NULL;
        }
        bool isEmpty() {
            return front == rear;
        }
    };

    Node* root;

public:
    Tree() : root(NULL) {}

    void buildTree() {
        string bookName;
        cout << "\nEnter the BOOK name: ";
        getline(cin, bookName);
        root = new Node(bookName);

        string chapters[2];
        cout << "\nEnter TWO chapters:\n";
        for (int i = 0; i < 2; ++i) {
            cout << "  Chapter " << (i + 1) << " name: ";
            getline(cin, chapters[i]);
        }

        Node* chapter1 = new Node(chapters[0]);
        Node* chapter2 = new Node(chapters[1]);
        root->left = chapter1;
        root->right = chapter2;

        string sections[4];
        cout << "\nEnter TWO sections for EACH chapter:\n";
        for (int i = 0; i < 2; ++i) {
            cout << "\nChapter " << (i + 1) << ": " << chapters[i] << endl;
            for (int j = 0; j < 2; ++j) {
                int idx = i * 2 + j;
                cout << "  Section " << (j + 1) << " name: ";
                getline(cin, sections[idx]);
            }
        }

        Node* section1 = new Node(sections[0]);
        Node* section2 = new Node(sections[1]);
        Node* section3 = new Node(sections[2]);
        Node* section4 = new Node(sections[3]);

        chapter1->left = section1;
        chapter1->right = section2;
        chapter2->left = section3;
        chapter2->right = section4;

        string subsections[8];
        cout << "\nEnter TWO subsections for EACH section:\n";
        for (int i = 0; i < 4; ++i) {
            cout << "\nSection " << (i + 1) << ": " << sections[i] << endl;
            for (int j = 0; j < 2; ++j) {
                int idx = i * 2 + j;
                cout << "  Subsection " << (j + 1) << " name: ";
                getline(cin, subsections[idx]);
            }
        }

        section1->left = new Node(subsections[0]);
        section1->right = new Node(subsections[1]);
        section2->left = new Node(subsections[2]);
        section2->right = new Node(subsections[3]);
        section3->left = new Node(subsections[4]);
        section3->right = new Node(subsections[5]);
        section4->left = new Node(subsections[6]);
        section4->right = new Node(subsections[7]);
    }

    void preorder() {
        cout << "\nPreorder: ";
        if (!root) return;
        Stack st;
        st.push(root);
        while (!st.isEmpty()) {
            Node* curr = st.pop();
            cout << curr->name << " ";
            if (curr->right) st.push(curr->right);
            if (curr->left)  st.push(curr->left);
        }
    }

    void inorder() {
        cout << "\nInorder: ";
        Stack st;
        Node* curr = root;
        while (curr || !st.isEmpty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.pop();
            cout << curr->name << " ";
            curr = curr->right;
        }
    }

    void postorder() {
        cout << "\nPostorder: ";
        if (!root) return;
        Stack s1, s2;
        s1.push(root);
        while (!s1.isEmpty()) {
            Node* curr = s1.pop();
            s2.push(curr);
            if (curr->left)  s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }
        while (!s2.isEmpty()) {
            cout << s2.pop()->name << " ";
        }
    }

    // New: Level Order Traversal
    void levelOrder() {
        cout << "\nLevel Order: ";
        if (!root) return;
        Queue q;
        q.enqueue(root);
        while (!q.isEmpty()) {
            Node* curr = q.dequeue();
            cout << curr->name << " ";
            if (curr->left)  q.enqueue(curr->left);
            if (curr->right) q.enqueue(curr->right);
        }
    }

    void displayAllTraversals() {
        preorder();
        inorder();
        postorder();
        levelOrder();  // call the new level order method
        cout << endl;
    }
};

int main() {
    Tree t;
    int choice;

    do {
        cout << "\n===== MENU =====";
        cout << "\n1. Build Book Tree";
        cout << "\n2. Display Preorder, Inorder, Postorder & Level Order";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // consume the newline after choice

        switch (choice) {
            case 1:
                t.buildTree();
                break;
            case 2:
                t.displayAllTraversals();
                break;
            case 3:
                cout << "Exiting...";
                break;
            default:
                cout << "Invalid choice. Please try again.";
        }
    } while (choice != 3);

    return 0;
}
