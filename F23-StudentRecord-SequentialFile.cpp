#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string rollNo;
    string name;
    string division;
    string address;
};

void addStudent() {
    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Division: ";
    getline(cin, s.division);
    cout << "Enter Address: ";
    getline(cin, s.address);

    ofstream file("students.txt", ios::app);
    file << s.rollNo << "," << s.name << "," << s.division << "," << s.address << "\n";
    file.close();
    cout << "Student added successfully.\n";
}

void displayStudent(string rollNo) {
    ifstream file("students.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find(',');
        string rno = line.substr(0, pos);

        if (rno == rollNo) {
            found = true;
            cout << "Student Details:\n" << line << "\n";
            break;
        }
    }

    if (!found)
        cout << "Student with Roll No " << rollNo << " not found.\n";

    file.close();
}

void deleteStudent(string rollNo) {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.find(rollNo + ",") != 0) {
            outFile << line << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student with Roll No " << rollNo << " deleted.\n";
    else
        cout << "Student not found.\n";
}

void displayAll() {
    ifstream file("students.txt");
    string line;

    cout << "\nAll Student Records:\n";
    while (getline(file, line)) {
        cout << line << "\n";
    }

    file.close();
}

int main() {
    int choice;
    string roll;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student by Roll No\n";
        cout << "3. Delete Student\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll Number to search: ";
                cin >> roll;
                displayStudent(roll);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 4:
                displayAll();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
