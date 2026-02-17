
#include <iostream> 
#include <list> 
using namespace std; 
  
#define SIZE 10 
  
// ----------------- SEPARATE CHAINING ----------------- 
  
class ChainingHash { 
    list<pair<int, int>> table[SIZE]; 
  
public: 
    int hashFunc(int key) { 
        return key % SIZE; 
    } 
  
    void insert(int key, int stock) { 
        int index = hashFunc(key); 
        table[index].push_back({key, stock}); 
        cout << "Inserted successfully\n"; 
    } 
  
    void search(int key) { 
        int index = hashFunc(key); 
        for (auto it : table[index]) { 
            if (it.first == key) { 
                cout << "Product found. Stock = " << it.second << endl; 
                return; 
            } 
        } 
        cout << "Product not found\n"; 
    } 
  
    void display() { 
        for (int i = 0; i < SIZE; i++) { 
            cout << i << " -> "; 
            for (auto it : table[i]) { 
                cout << "(" << it.first << "," << it.second << ") "; 
            } 
            cout << endl; 
        } 
    } 
}; 
  
// ----------------- LINEAR PROBING ----------------- 
  
class LinearHash { 
    int key[SIZE]; 
    int value[SIZE]; 
  
public: 
    LinearHash() { 
        for (int i = 0; i < SIZE; i++) { 
            key[i] = -1; 
            value[i] = -1; 
        } 
    } 
  
    int hashFunc(int k) { 
        return k % SIZE; 
    } 
  
    void insert(int k, int v) { 
        int index = hashFunc(k); 
  
        while (key[index] != -1) { 
            index = (index + 1) % SIZE; 
        } 
  
        key[index] = k; 
        value[index] = v; 
        cout << "Inserted successfully\n"; 
    } 
  
    void search(int k) { 
        int index = hashFunc(k); 
        int start = index; 
  
        while (key[index] != -1) { 
            if (key[index] == k) { 
                cout << "Product found. Stock = " << value[index] << endl; 
                return; 
            } 
            index = (index + 1) % SIZE; 
  
            if (index == start) 
                break; 
        } 
        cout << "Product not found\n"; 
    } 
  
    void display() { 
        for (int i = 0; i < SIZE; i++) { 
            cout << i << " : "; 
            if (key[i] != -1) 
                cout << "(" << key[i] << "," << value[i] << ")"; 
            else 
                cout << "-"; 
            cout << endl; 
        } 
    } 
}; 
  
// ----------------- MAIN MENU ----------------- 
  
int main() { 
    ChainingHash chain; 
    LinearHash linear; 
  
    int choice, key, stock; 
  
    do { 
        cout << "\n===== PRODUCT INVENTORY HASH TABLE =====\n"; 
        cout << "1. Insert (Separate Chaining)\n"; 
        cout << "2. Search (Separate Chaining)\n"; 
        cout << "3. Display (Separate Chaining)\n"; 
        cout << "4. Insert (Linear Probing)\n"; 
        cout << "5. Search (Linear Probing)\n"; 
        cout << "6. Display (Linear Probing)\n"; 
        cout << "0. Exit\n"; 
        cout << "Enter choice: "; 
        cin >> choice; 
  
        switch (choice) { 
        case 1: 
            cout << "Enter Product ID and Stock: "; 
            cin >> key >> stock; 
            chain.insert(key, stock); 
            break; 
  
        case 2: 
            cout << "Enter Product ID: "; 
            cin >> key; 
            chain.search(key); 
            break; 
  
        case 3: 
            chain.display(); 
            break; 
  
        case 4: 
            cout << "Enter Product ID and Stock: "; 
            cin >> key >> stock; 
            linear.insert(key, stock); 
            break; 
  
        case 5: 
            cout << "Enter Product ID: "; 
            cin >> key; 
            linear.search(key); 
            break; 
  
        case 6: 
            linear.display(); 
            break; 
  
        case 0: 
            cout << "Exiting...\n"; 
            break; 
  
        default: 
            cout << "Invalid choice\n"; 
        } 
  
    } while (choice != 0); 
  
    return 0; 
} 