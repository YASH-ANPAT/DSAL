#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;

class EmployeeSystem {
    struct Employee {
        int emp_id;
        char name[50];
        char designation[50];
        double salary;
    };

    struct Index {
        int emp_id;
        int position;
    };

    Employee emp;
    Index idx;

public:
    void Create();
    void Display();
    void Update();
    void Delete();
    void Search();
    void Append();
};

void EmployeeSystem::Create() {
    char ch = 'y';
    ofstream empFile("EMPLOYEE.DAT", ios::binary);
    ofstream indexFile("INDEX.DAT", ios::binary);

    if(!empFile || !indexFile) {
        cout << "Error in file creation!";
        return;
    }

    do {
        cout << "\nEnter Employee ID: ";
        cin >> emp.emp_id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(emp.name, 50);
        cout << "Enter Designation: ";
        cin.getline(emp.designation, 50);
        cout << "Enter Salary: ";
        cin >> emp.salary;

        // Write to employee file
        int pos = empFile.tellp();
        empFile.write((char*)&emp, sizeof(emp));

        // Update index
        idx.emp_id = emp.emp_id;
        idx.position = pos / sizeof(emp);
        indexFile.write((char*)&idx, sizeof(idx));

        cout << "Add more records? (y/n): ";
        cin >> ch;
    } while(ch == 'y' || ch == 'Y');

    empFile.close();
    indexFile.close();
}

void EmployeeSystem::Display() {
    ifstream empFile("EMPLOYEE.DAT", ios::binary);
    ifstream indexFile("INDEX.DAT", ios::binary);

    if(!empFile || !indexFile) {
        cout << "Error opening files!";
        return;
    }

    cout << "\nEmployee Records:\n";
    cout << setw(10) << "ID" << setw(20) << "Name" 
         << setw(20) << "Designation" << setw(15) << "Salary" << endl;

    while(indexFile.read((char*)&idx, sizeof(idx))) {
        if(idx.emp_id == -1) continue; // Skip deleted records

        empFile.seekg(idx.position * sizeof(emp));
        empFile.read((char*)&emp, sizeof(emp));

        if(emp.emp_id != -1) {
            cout << setw(10) << emp.emp_id 
                 << setw(20) << emp.name 
                 << setw(20) << emp.designation 
                 << setw(15) << fixed << setprecision(2) << emp.salary << endl;
        }
    }

    empFile.close();
    indexFile.close();
}

void EmployeeSystem::Search() {
    int searchId;
    cout << "Enter Employee ID to search: ";
    cin >> searchId;

    ifstream empFile("EMPLOYEE.DAT", ios::binary);
    ifstream indexFile("INDEX.DAT", ios::binary);

    bool found = false;
    while(indexFile.read((char*)&idx, sizeof(idx))) {
        if(idx.emp_id == searchId) {
            empFile.seekg(idx.position * sizeof(emp));
            empFile.read((char*)&emp, sizeof(emp));
            
            if(emp.emp_id != -1) {
                cout << "\nEmployee Found:\n";
                cout << "ID: " << emp.emp_id << endl;
                cout << "Name: " << emp.name << endl;
                cout << "Designation: " << emp.designation << endl;
                cout << "Salary: " << fixed << setprecision(2) << emp.salary << endl;
                found = true;
            }
            break;
        }
    }

    if(!found) {
        cout << "Employee not found!\n";
    }

    empFile.close();
    indexFile.close();
}

void EmployeeSystem::Update() {
    int updateId;
    cout << "Enter Employee ID to update: ";
    cin >> updateId;

    fstream empFile("EMPLOYEE.DAT", ios::in | ios::out | ios::binary);
    fstream indexFile("INDEX.DAT", ios::in | ios::binary);

    bool found = false;
    while(indexFile.read((char*)&idx, sizeof(idx))) {
        if(idx.emp_id == updateId) {
            empFile.seekg(idx.position * sizeof(emp));
            empFile.read((char*)&emp, sizeof(emp));
            
            if(emp.emp_id != -1) {
                cout << "Current Details:\n";
                cout << "Name: " << emp.name << endl;
                cout << "Designation: " << emp.designation << endl;
                cout << "Salary: " << fixed << setprecision(2) << emp.salary << endl;

                cout << "\nEnter new details:\n";
                cout << "Name: ";
                cin.ignore();
                cin.getline(emp.name, 50);
                cout << "Designation: ";
                cin.getline(emp.designation, 50);
                cout << "Salary: ";
                cin >> emp.salary;

                empFile.seekp(idx.position * sizeof(emp));
                empFile.write((char*)&emp, sizeof(emp));
                cout << "Record updated successfully!\n";
                found = true;
            }
            break;
        }
    }

    if(!found) {
        cout << "Employee not found!\n";
    }

    empFile.close();
    indexFile.close();
}

void EmployeeSystem::Delete() {
    int deleteId;
    cout << "Enter Employee ID to delete: ";
    cin >> deleteId;

    fstream empFile("EMPLOYEE.DAT", ios::in | ios::out | ios::binary);
    fstream indexFile("INDEX.DAT", ios::in | ios::out | ios::binary);

    bool found = false;
    while(indexFile.read((char*)&idx, sizeof(idx))) {
        if(idx.emp_id == deleteId) {
            // Mark as deleted in employee file
            empFile.seekg(idx.position * sizeof(emp));
            empFile.read((char*)&emp, sizeof(emp));
            
            if(emp.emp_id != -1) {
                emp.emp_id = -1; // Mark as deleted
                empFile.seekp(idx.position * sizeof(emp));
                empFile.write((char*)&emp, sizeof(emp));

                // Mark as deleted in index file
                idx.emp_id = -1;
                indexFile.seekp(indexFile.tellg() - streamoff(sizeof(idx)));
                indexFile.write((char*)&idx, sizeof(idx));
                
                cout << "Record deleted successfully!\n";
                found = true;
            }
            break;
        }
    }

    if(!found) {
        cout << "Employee not found!\n";
    }

    empFile.close();
    indexFile.close();
}

void EmployeeSystem::Append() {
    ofstream empFile("EMPLOYEE.DAT", ios::app | ios::binary);
    ofstream indexFile("INDEX.DAT", ios::app | ios::binary);

    if(!empFile || !indexFile) {
        cout << "Error opening files!";
        return;
    }

    cout << "\nEnter Employee ID: ";
    cin >> emp.emp_id;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(emp.name, 50);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 50);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    // Write to employee file
    int pos = empFile.tellp();
    empFile.write((char*)&emp, sizeof(emp));

    // Update index
    idx.emp_id = emp.emp_id;
    idx.position = pos / sizeof(emp);
    indexFile.write((char*)&idx, sizeof(idx));

    cout << "Record added successfully!\n";

    empFile.close();
    indexFile.close();
}

int main() {
    EmployeeSystem es;
    int choice;
    char cont;

    do {
        cout << "\nEmployee Record System\n";
        cout << "1. Create Database\n";
        cout << "2. Display All Records\n";
        cout << "3. Search Record\n";
        cout << "4. Update Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Append Record\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: es.Create(); break;
            case 2: es.Display(); break;
            case 3: es.Search(); break;
            case 4: es.Update(); break;
            case 5: es.Delete(); break;
            case 6: es.Append(); break;
            case 7: return 0;
            default: cout << "Invalid choice!\n";
        }

        if(choice != 7) {
            cout << "\nContinue? (y/n): ";
            cin >> cont;
        }
    } while(cont == 'y' || cont == 'Y');

    return 0;
}