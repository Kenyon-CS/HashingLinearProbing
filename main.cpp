#include <iostream>
#include <string>
using namespace std;

// Template for a generic type
template <typename K, typename V>

// HashNode class
class HashNode {
public:
    K key;
    V value;

    // Constructor of HashNode
    HashNode(K key, V value) : key(key), value(value) {}
};


// Template for generic type
template <typename K, typename V>

// Our own HashMap class
class HashMap {
    HashNode<K, V> **arr;
    int capacity;
    int size;
    HashNode<K, V> *dummy;

public:
    HashMap(int capacity = 20) : capacity(capacity), size(0) {
        arr = new HashNode<K, V> *[capacity];
        for (int i = 0; i < capacity; i++)
            arr[i] = nullptr;
        dummy = new HashNode<K, V>(K(), V());
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            if (arr[i] && arr[i] != dummy)
                delete arr[i];
        }
        delete[] arr;
        delete dummy;
    }

    // Hash function to compute index
    int hashCode(K key) { return static_cast<int>(hash<K>{}(key) % capacity); }

    // Function to add key-value pair
    void insertNode(K key, V value) {
        int hashIndex = hashCode(key);
        int startIndex = hashIndex;

        while (arr[hashIndex] != nullptr && arr[hashIndex]->key != key &&
               arr[hashIndex] != dummy) {
            hashIndex = (hashIndex + 1) % capacity;
            if (hashIndex == startIndex) {
                cout << "Hash table is full, cannot insert!" << endl;
                return;
            }
        }

        if (arr[hashIndex] == nullptr || arr[hashIndex] == dummy)
            size++;

        arr[hashIndex] = new HashNode<K, V>(key, value);
    }

    // Function to delete a key-value pair
    V deleteNode(K key) {
        int hashIndex = hashCode(key);
        int startIndex = hashIndex;

        while (arr[hashIndex] != nullptr) {
            if (arr[hashIndex]->key == key) {
                HashNode<K, V> *temp = arr[hashIndex];
                arr[hashIndex] = dummy;
                size--;
                V deletedValue = temp->value;
                delete temp;
                return deletedValue;
            }
            hashIndex = (hashIndex + 1) % capacity;
            if (hashIndex == startIndex) break;
        }

        cout << "Key not found!" << endl;
        return V();
    }

    // Function to get the value for a given key
    V get(K key) {
        int hashIndex = hashCode(key);
        int startIndex = hashIndex;
        int counter = 0;

        while (arr[hashIndex] != nullptr) {
            if (counter++ > capacity) // to avoid infinite loop
                return V();

            if (arr[hashIndex]->key == key)
                return arr[hashIndex]->value;

            hashIndex = (hashIndex + 1) % capacity;
            if (hashIndex == startIndex) break;
        }

        return V();
    }

    // Return current size
    int sizeofMap() const { return size; }

    // Check if the table is empty
    bool isEmpty() const { return size == 0; }

    // Function to display the stored key-value pairs
    void display() const {
        for (int i = 0; i < capacity; i++) {
            if (arr[i] != nullptr && arr[i] != dummy)
                cout << "key = " << arr[i]->key << ", value = " << arr[i]->value << endl;
        }
    }
};

// Driver method to test HashMap class
int main() {
    HashMap<int, string> hTable;
    int key;
    string value;

    while (true) {
        cout << "\n1. Add, 2. Lookup, 3. Delete, 4. Display, 5. Exit: ";
        int opt;
        cin >> opt;

        if (opt == 1) {
            cout << "Enter key and value: ";
            cin >> key >> value;
            hTable.insertNode(key, value);
        } else if (opt == 2) {
            cout << "Enter key to lookup: ";
            cin >> key;
            value = hTable.get(key);
            if (!value.empty())
                cout << "Found: " << value << endl;
            else
                cout << "Not found!" << endl;
        } else if (opt == 3) {
            cout << "Enter key to delete: ";
            cin >> key;
            hTable.deleteNode(key);
        } else if (opt == 4) {
            hTable.display();
        } else if (opt == 5) {
            break;
        } else {
            cout << "Invalid option!" << endl;
        }
    }

    return 0;
}
