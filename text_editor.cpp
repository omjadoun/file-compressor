#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(string data) {     // constructor
        this->data = data;
        this->next = NULL;
    }
};

class Editor {
public:
    void add_line(Node* &root) {    // add a user-given line to the end of text
        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        if (root == NULL) {      // insert line in an empty list
            root = new Node(line);
            return;
        }

        Node* root_ref = root;
        while (root_ref->next != NULL) {   // traverse the whole list
            root_ref = root_ref->next;
        }

        Node* temp = new Node(line);
        root_ref->next = temp;    // insert the line at end
    }

    void add_line_at(Node* &root, int line_no) {   // add a line at a particular index
        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        Node* temp = new Node(line);

        if (line_no == 1) {      // add node to the head of list
            temp->next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;
        for (int i = 1; i < line_no - 1; i++) {       // traverse till the specified index
            if (root_ref == NULL || root_ref->next == NULL) {
                cout << "Index out of bounds." << endl;
                return;
            }
            root_ref = root_ref->next;
        }

        temp->next = root_ref->next;    // insert the node
        root_ref->next = temp;
    }

    void replace_line(Node* &root) {    // replace a line
        int line_no;
        cout << "Enter the line number to replace: ";
        cin >> line_no;
        cin.ignore(); // clear input buffer

        delete_line(root, line_no);     // delete the line at index
        add_line_at(root, line_no);     // replace it with a new line
    }

    void delete_line(Node* &root, int line_no) {     // delete the line at given index
        if (line_no == 1) {      // delete node at the head of list
            Node* temp = root;
            root = root->next;
            delete temp;        // free up space 
            return;
        }

        Node* root_ref = root;
        for (int i = 1; i < line_no - 1; i++) {       // traverse till the specified index
            if (root_ref == NULL || root_ref->next == NULL) {
                cout << "Index out of bounds." << endl;
                return;
            }
            root_ref = root_ref->next;
        }

        Node* temp = root_ref->next;
        if (temp != NULL) {
            root_ref->next = temp->next;
            delete temp;        // free up space
        }
    }

    void open_file(Node* &root) {   // read a file and return the head of linked list
        ifstream file("sample.txt"); // open file in read mode
        string line;

        if (!file) {
            cout << "File couldn't open successfully." << endl;
            return;
        } else {
            cout << "File opened successfully." << endl;
        }

        while (getline(file, line)) {    // execute until file is read completely
            if (root == NULL) {
                root = new Node(line);      // head node
            } else {
                Node* root_ref = root;
                while (root_ref->next != NULL) {   
                    root_ref = root_ref->next;    // traverse till the end of linked list
                }
                Node* temp = new Node(line);    
                root_ref->next = temp;
            }
        }
    
        file.close();   
    }   

    void save_file(Node* &root) {   // save the modified file
        ofstream file("sample.txt"); // open in output mode

        Node* root_ref = root;
        while (root_ref != NULL) {
            file << root_ref->data << endl; // write data in the file
            root_ref = root_ref->next;
        }
        cout << "File saved successfully." << endl;
        file.close();
    }

    void search_word(Node* root) {   // Search for a specific word in each line
        string word;
        cout << "Enter the word to search: ";
        cin >> word;
        cin.ignore();  // Clear any leftover newline characters after reading the word

        Node* root_ref = root;
        int line_no = 1;
        bool found = false;

        while (root_ref != NULL) {
            if (root_ref->data.find(word) != string::npos) {  // Check if word is in the line
                cout << "Line " << line_no << ": " << root_ref->data << endl;
                found = true;
            }
            root_ref = root_ref->next;
            line_no++;
        }

        if (!found) {
            cout << "Word \"" << word << "\" not found in any line." << endl;
        }
    }

    void display(Node* root) {      // display the content of file
        cout << "Current text:" << endl;
        int i = 0;
        while (root != NULL) {
            cout << ++i << "> " << root->data << endl;
            root = root->next;
        }
        cout << endl;
    }

    void begin(Node* &root) {     // controller function
        open_file(root);

        int select;

        while (1) {
            cout << "Enter your Selection:" << endl;
            cout << "1. Insert line" << endl;
            cout << "2. Insert line at index" << endl; 
            cout << "3. Replace a line" << endl;
            cout << "4. Delete line" << endl;
            cout << "5. Display text file" << endl;
            cout << "6. Save File" << endl;
            cout << "7. Search for a word" << endl;
            cout << "-1. Exit" << endl;
            cout << ">> ";

            cin >> select;
            cin.ignore();
            switch (select) {
                case 1:
                    add_line(root);           
                    break;
                case 2:
                    int line_no;
                    cout << "Enter the index to insert at: ";
                    cin >> line_no;
                    cin.ignore();
                    add_line_at(root, line_no);               
                    break;
                case 3:
                    replace_line(root);  
                    break;
                case 4:
                    cout << "Enter line number to delete: ";
                    cin >> line_no;
                    cin.ignore();
                    delete_line(root, line_no);
                    break;
                case 5:
                    display(root);
                    break;
                case 6:
                    save_file(root);
                    break;
                case 7:
                    search_word(root);
                    break;
                case -1:
                    cout << "Editor exited...";
                    return;   
                default:
                    cout << "Invalid selection. Try again." << endl;
            }
        }
    }
};

int main() {
    Node* root = NULL;
    Editor a;

    a.begin(root);

    return 0;
}
