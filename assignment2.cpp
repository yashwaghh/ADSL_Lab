#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/*------------- Node Structure -------------*/
struct Node {
    char label[50];      // name of book/chapter/section
    int childCount;      // number of children
    Node* child[10];     // fixed size children array
};

/*------------- Tree Class -------------*/
class BookTree {
private:
    Node* root;

public:
    BookTree() {
        root = NULL;
    }

    /* Create Tree */
    void createTree() {
        root = new Node;

        cout << "Enter Book name: ";
        cin.ignore();
        cin.getline(root->label, 50);

        cout << "Enter number of chapters: ";
        cin >> root->childCount;
        cin.ignore();

        for (int i = 0; i < root->childCount; i++) {
            root->child[i] = new Node;

            cout << "\nEnter Chapter " << i + 1 << " name: ";
            cin.getline(root->child[i]->label, 50);

            cout << "Enter number of sections in this chapter: ";
            cin >> root->child[i]->childCount;
            cin.ignore();

            for (int j = 0; j < root->child[i]->childCount; j++) {
                root->child[i]->child[j] = new Node;

                cout << "Enter Section " << j + 1 << " name: ";
                cin.getline(root->child[i]->child[j]->label, 50);

                root->child[i]->child[j]->childCount = 0; // no subsections
            }
        }
    }

    /* Display Tree */
    void display() {
        if (root == NULL) {
            cout << "\nTree is empty. Create it first.\n";
            return;
        }

        cout << "\n\n===== Book Hierarchy =====";
        cout << "\nBook: " << root->label;

        for (int i = 0; i < root->childCount; i++) {
            cout << "\n  Chapter " << i + 1 << ": "
                 << root->child[i]->label;

            for (int j = 0; j < root->child[i]->childCount; j++) {
                cout << "\n     Section " << j + 1 << ": "
                     << root->child[i]->child[j]->label;
            }
        }
        cout << "\n";
    }
};

/*------------- Main Function -------------*/
int main() {
    BookTree tree;
    int choice;

    while (true) {
        cout << "\n---------------------------";
        cout << "\n        Book Tree";
        cout << "\n---------------------------";
        cout << "\n1. Create";
        cout << "\n2. Display";
        cout << "\n3. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tree.createTree();
                break;

            case 2:
                tree.display();
                break;

            case 3:
                exit(0);

            default:
                cout << "Invalid choice!";
        }
    }
}
