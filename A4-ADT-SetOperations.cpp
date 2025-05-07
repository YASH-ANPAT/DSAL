#include <iostream>
#include <vector>
using namespace std;

class Set {
    vector<int> elements;

    bool exists(int val) {
        for (int i : elements)
            if (i == val)
                return true;
        return false;
    }

public:
    void create() {
        int n, x;
        cout << "Enter number of elements: ";
        cin >> n;
        cout << "Enter " << n << " elements:\n";
        for (int i = 0; i < n; i++) {
            cin >> x;
            if (!exists(x))
                elements.push_back(x);
            else
                cout << x << " is a duplicate and won't be added.\n";
        }
    }

    void insert(int val) {
        if (!exists(val))
            elements.push_back(val);
        else
            cout << "Element already exists in the set.\n";
    }

    void remove(int val) {
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            if (*it == val) {
                elements.erase(it);
                cout << "Element removed.\n";
                return;
            }
        }
        cout << "Element not found.\n";
    }

    bool contains(int val) {
        return exists(val);
    }

    int size() {
        return elements.size();
    }

    void display() {
        if (elements.empty()) {
            cout << "{ NULL }";
        } else {
            cout << "{ ";
            for (int val : elements)
                cout << val << " ";
            cout << "}";
        }
        cout << endl;
    }

    Set setUnion(Set& other) {
        Set result;
        for (int val : elements)
            result.insert(val);
        for (int val : other.elements)
            result.insert(val);
        return result;
    }

    Set intersection(Set& other) {
        Set result;
        for (int val : elements)
            if (other.contains(val))
                result.insert(val);
        return result;
    }

    Set difference(Set& other) {
        Set result;
        for (int val : elements)
            if (!other.contains(val))
                result.insert(val);
        return result;
    }

    bool isSubsetOf(Set& other) {
        for (int val : elements)
            if (!other.contains(val))
                return false;
        return true;
    }
};

int main() {
    Set A, B, C;
    int choice, val;

    cout << "--- Create Set A ---\n";
    A.create();
    cout << "--- Create Set B ---\n";
    B.create();

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Add element\n";
        cout << "2. Remove element\n";
        cout << "3. Check element\n";
        cout << "4. Display sets\n";
        cout << "5. Size of sets\n";
        cout << "6. Union\n";
        cout << "7. Intersection \n";
        cout << "8. Difference \n";
        cout << "9. Subset check \n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Add to which set? (1 for A, 2 for B): ";
            cin >> val;
            cout << "Enter element: ";
            int ele;
            cin >> ele;
            (val == 1 ? A : B).insert(ele);
            break;
        case 2:
            cout << "Remove from which set? (1 for A, 2 for B): ";
            cin >> val;
            cout << "Enter element: ";
            cin >> ele;
            (val == 1 ? A : B).remove(ele);
            break;
        case 3:
            cout << "Check in which set? (1 for A, 2 for B): ";
            cin >> val;
            cout << "Enter element: ";
            cin >> ele;
            if ((val == 1 ? A : B).contains(ele))
                cout << "Element found.\n";
            else
                cout << "Element not found.\n";
            break;
        case 4:
            cout << "Set A: ";
            A.display();
            cout << "Set B: ";
            B.display();
            break;
        case 5:
            cout << "Size of Set A: " << A.size() << endl;
            cout << "Size of Set B: " << B.size() << endl;
            break;
        case 6:
            C = A.setUnion(B);
            cout << "A <UNION> B = ";
            C.display();
            break;
        case 7:
            C = A.intersection(B);
            cout << "A <INTERSECTION> B = ";
            C.display();
            break;
        case 8:
            C = A.difference(B);
            cout << "A - B = ";
            C.display();
            break;
        case 9:
            if (A.isSubsetOf(B))
                cout << "A is a subset of B.\n";
            else
                cout << "A is not a subset of B.\n";
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
