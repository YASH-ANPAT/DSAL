#include <iostream>
using namespace std;

class Hash
{
    struct node
    {
        int Tel_no;
        string Name;
        node *next;
    };

    node *Hashtable[10];
    bool isOccupied[10];

public:
    Hash()
    {
        for (int i = 0; i < 10; i++)
        {
            Hashtable[i] = NULL;
            isOccupied[i] = false;
        }
    }

    node *create_chaining()
    {
        int Tel_no;
        string Name;

        cout << "Enter Name: ";
        cin >> Name;

        cout << "Enter Telephone Number: ";
        cin >> Tel_no;

        node *temp = new node;
        temp->Name = Name;
        temp->Tel_no = Tel_no;
        temp->next = NULL;

        int I = Tel_no % 10;

        if (Hashtable[I] == NULL)
        {
            Hashtable[I] = temp;
        }
        else
        {
            node *p = Hashtable[I];
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = temp;
        }
        return Hashtable[I];
    }

    void create_linear_probing()
    {
        int Tel_no;
        string Name;

        cout << "Enter Name: ";
        cin >> Name;

        cout << "Enter Telephone Number: ";
        cin >> Tel_no;

        int I = Tel_no % 10;
        int originalIndex = I;

        while (isOccupied[I])
        {
            I = (I + 1) % 10;
            if (I == originalIndex)
            {
                cout << "Hash table is full!" << endl;
                return;
            }
        }

        node *temp = new node;
        temp->Name = Name;
        temp->Tel_no = Tel_no;
        temp->next = NULL;

        Hashtable[I] = temp;
        isOccupied[I] = true;
    }

    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            node *temp = Hashtable[i];
            cout << "Index-" << i << " ----> ";

            if (temp == NULL)
            {
                cout << "NULL" << endl;
                continue;
            }
            else
            {
                while (temp != NULL)
                {
                    cout << temp->Name << ":" << temp->Tel_no;
                    temp = temp->next;
                    if (temp != NULL)
                    {
                        cout << " --> ";
                    }
                }
                cout << endl;
            }
        }
    }

    void search(int Tel_no, int method)
    {
        int I = Tel_no % 10;

        if (method == 1) // Separate Chaining
        {
            node *temp = Hashtable[I];
            while (temp != NULL)
            {
                if (temp->Tel_no == Tel_no)
                {
                    cout << "Record Found at index " << I << ": " << temp->Name << " - " << temp->Tel_no << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "Record Not Found!" << endl;
        }
        else if (method == 2) // Linear Probing
        {
            int start = I;
            while (isOccupied[I])
            {
                if (Hashtable[I] != NULL && Hashtable[I]->Tel_no == Tel_no)
                {
                    cout << "Record Found at index " << I << ": " << Hashtable[I]->Name << " - " << Hashtable[I]->Tel_no << endl;
                    return;
                }
                I = (I + 1) % 10;
                if (I == start)
                    break;
            }
            cout << "Record Not Found!" << endl;
        }
    }

    void menu()
    {
        int ch, method = 1;

        cout << "Choose collision resolution method:\n1. Separate Chaining\n2. Linear Probing\n";
        cout << "Your choice: ";
        cin >> method;

        do
        {
            cout << "\nEnter option:\n1. Create Node\n2. Display Nodes\n3. Search Record\n4. Exit Menu" << endl;
            cout << "Your Choice : ";
            cin >> ch;

            switch (ch)
            {
            case 1:
                if (method == 1)
                    create_chaining();
                else
                    create_linear_probing();
                break;
            case 2:
                display();
                break;
            case 3:
                int tel;
                cout << "Enter Telephone Number to search: ";
                cin >> tel;
                search(tel, method);
                break;
            case 4:
                break;
            default:
                cout << "Invalid Option. Please try again...!" << endl;
            }
        } while (ch != 4);
    }
};

int main()
{
    Hash T;
    T.menu();
    return 0;
}
