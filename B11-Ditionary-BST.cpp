#include <iostream>
using namespace std;

class node {
public:
    string keyword;
    string meaning;
    node* left;
    node* right;
};

class tree {
public:
    node* root;

    tree() {
        root = NULL;
    }

    void create() {
        char ans = 'y';
        do {
            node* New = new node;
            cout << "Enter word: ";
            cin >> New->keyword;
            cout << "Enter meaning: ";
            cin >> New->meaning;
            New->left = NULL;
            New->right = NULL;

            if (root == NULL)
                root = New;
            else
                insert(root, New);
            cout << "Do you want to enter more elements? (y/n): ";
            cin >> ans;
        } while (ans == 'y' || ans == 'Y');
    }

    void insert(node* root, node* New) {
        if (New->keyword > root->keyword) {
            if (root->right == NULL)
                root->right = New;
            else
                insert(root->right, New);
        }
        if (New->keyword < root->keyword) {
            if (root->left == NULL)
                root->left = New;
            else
                insert(root->left, New);
        }
    }

    void search(string key) {
        node* temp = root;  
        while (temp != NULL) {
            if (temp->keyword == key) {
                cout << "Word searched: " << temp->keyword << "-->" << temp->meaning << endl;
                return;  
            }
            if (temp->keyword < key)
                temp = temp->right;
            else
                temp = temp->left;
        }
        cout << "Word not found." << endl;
    }

    void update(string key) {
        node* temp = root;  
        while (temp != NULL) {
            if (temp->keyword == key) {
                cout << "Update meaning for word '" << temp->keyword << "': " << endl;
                cin >> temp->meaning;
                cout << "Updated word: " << temp->keyword << "-->" << temp->meaning << endl;
                return;  
            }
            if (temp->keyword < key)
                temp = temp->right;
            else
                temp = temp->left;
        }
        cout << "Word not found." << endl;
    }

    node* findMin(node* root) {
        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }

    node* del(node* root, string x) {
        if (root == NULL) {
            cout << "Keyword not found" << endl;
            return root;
        }
        if (x < root->keyword) {
            root->left = del(root->left, x);
        } else if (x > root->keyword) {
            root->right = del(root->right, x);
        } else {
            // Node with only one child or no child
            if (root->left == NULL) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                node* temp = root->left;
                delete root;
                return temp;
            }
            // Node with two children
            node* temp = findMin(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = del(root->right, temp->keyword);
        }
        return root;
    }

    void display_data_ascend(node* temp) {
        if (temp != NULL) {
            display_data_ascend(temp->left);
            cout << temp->keyword << " --> " << temp->meaning << endl;
            display_data_ascend(temp->right);
        }
    }

    void display_data_descend(node* temp) {
        if (temp != NULL) {
            display_data_descend(temp->right);
            cout << temp->keyword << " --> " << temp->meaning << endl;
            display_data_descend(temp->left);
        }
    }
    
    int max_comparisons(node* root){
    	//height
    	if (root == NULL)
            return 0;
        if (root->left == NULL && root->right == NULL)
            return 0;
        int hl = 1 + max_comparisons(root->left);
        int hr = 1 + max_comparisons(root->right);
        if (hl >= hr)
            return hl;
        else
            return hr;
	}
	
    void menu(){
    	int ch;
    	do{
cout<<"\n1.Enter your words and meanings \n2.Search word \n3.Update word \n4.Delete word \n5.Display in ascending order \n6.Display in descending order \n7.Maximum comparisons \n8.Exit"<<endl;
    		cin>>ch;
    		
    		switch(ch){
    			case 1:
    				create();
    				break;
    			case 2: {
    				string key;
				 cout << "Enter word to search: ";
				 cin >> key;
				 search(key);
				 break;
				}
			case 3: {
				string a;
				 cout << "Enter word to update its meaning: ";
				 cin >> a;
				 update(a);
				 break;
				}
			case 4: {
				string key1;
				cout << "Enter word to delete: ";
				cin >> key1;
				root = del(root, key1);
				break;
				}
			case 5:
				cout << "Displaying in ascending order..." << endl;
    				display_data_ascend(root);
    				break;
			case 6:
				cout << "Displaying in descending order..." << endl;
    				display_data_descend(root);	
    				break;
    			case 7:
    				cout<<"Maximum comparisons: "<<max_comparisons(root)<<endl;
    				break;
			case 8:
				cout<<"Exiting..."	;
				break;
			default:
				cout<<"Invalid choice";		
			}
		} while(ch != 7);
	}
};

int main() {
    tree t;
    t.menu();
    return 0;
}