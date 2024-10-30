#include <bits/stdc++.h>
using namespace std;

// template for generic type
template <typename K, typename V>

// Hashnode class
class HashNode {
public:
  V value;
  K key;

  // Constructor of hashnode
  HashNode(K key, V value) {
    this->value = value;
    this->key = key;
  }
};

// template for generic type
template <typename K, typename V>

// Our own Hashmap class
class HashMap {
  // hash element array
  HashNode<K, V> **arr;
  int capacity;
  // current size
  int size;
  // dummy node
  HashNode<K, V> *dummy;

public:
  HashMap() {
    // Initial capacity of hash array
    capacity = 20;
    size = 0;
    arr = new HashNode<K, V> *[capacity];

    // Initialise all elements of array as NULL
    for (int i = 0; i < capacity; i++)
      arr[i] = NULL;

    // dummy node with value and key -1
    dummy = new HashNode<K, V>(-1, "");
  }
  // This implements hash function to find index
  // for a key
  int hashCode(K key) { return key % capacity; }

  // Function to add key value pair
  void insertNode(K key, V value) {
    HashNode<K, V> *temp = new HashNode<K, V>(key, value);

    // Apply hash function to find index for given key
    int hashIndex = hashCode(key);

    // find next free space
    while (arr[hashIndex] != NULL && arr[hashIndex]->key != key &&
           arr[hashIndex]->key != -1) {
      hashIndex++;
      hashIndex %= capacity;
    }

    // if new node to be inserted
    // increase the current size
    if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1)
      size++;
    arr[hashIndex] = temp;
  }

  // Function to delete a key value pair
  V deleteNode(int key) {
    // Apply hash function
    // to find index for given key
    int hashIndex = hashCode(key);

    // finding the node with given key
    while (arr[hashIndex] != NULL) {
      // if node found
      if (arr[hashIndex]->key == key) {
        HashNode<K, V> *temp = arr[hashIndex];

        // Insert dummy node here for further use
        arr[hashIndex] = dummy;

        // Reduce size
        size--;
        return temp->value;
      }
      hashIndex++;
      hashIndex %= capacity;
    }

    // If not found return ""
    return "";
  }

  // Function to search the value for a given key
  V get(int key) {
    // Apply hash function to find index for given key
    int hashIndex = hashCode(key);
    int counter = 0;

    // finding the node with given key
    while (arr[hashIndex] != NULL) { // int counter =0; // BUG!

      if (counter++ > capacity) // to avoid infinite loop
        return NULL;

      // if node found return its value
      if (arr[hashIndex]->key == key)
        return arr[hashIndex]->value;
      hashIndex++;
      hashIndex %= capacity;
    }
    // If not found return ""
    return "";
  }

  // Return current size
  int sizeofMap() { return size; }

  // Return true if size is 0
  bool isEmpty() { return size == 0; }

  // Function to display the stored key value pairs
  void display() {
    for (int i = 0; i < capacity; i++) {
      if (arr[i] != NULL && arr[i]->key != -1)
        cout << "key = " << arr[i]->key << " value = " << arr[i]->value << endl;
    }
  }
};

// Driver method to test map class
int main() {
  HashMap<int, string> *h = new HashMap<int, string>;
  int key;
  string value;

  while (1) {
    if (h->isEmpty()) {
      cout << "Table is empty." << endl;
    } else {
      cout << "Table size: " << h->sizeofMap() << endl;
    }
    cout << "Add: 1, Lookup 2, Delete 3, Display 4, Exit 5: ";
    int opt;
    cin >> opt;
    if (opt == 1) {
      cout << "Enter key and value:";
      cin >> key >> value;
      h->insertNode(key, value);
    } else if (opt == 2) {
      cout << "Enter key to lookup:";
      cin >> key;
      value = h->get(key);
      if (value != "") {
        cout << "Found: " << h->get(key) << endl;
      } else {
        cout << "Not found!" << endl;
      }
    } else if (opt == 3) {
      cout << "Enter key to delete:";
      cin >> key;
      h->deleteNode(key);
    } else if (opt == 4) {
      h->display();
    } else if (opt == 5) {
      h->display();
    } else {
      cout << "Bad option:" << endl;
    }
  }

  return 0;
}
