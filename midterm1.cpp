// comsc 210 | midterm1 | Christian Molina

#include <iostream>
using namespace std;

// constants for random list size and value ranges
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Doubly linked list class
class DoublyLinkedList {
private:
  struct Node {// Node structure for doubly linked list each one stores an int and has prev and next pointers
    int data;// the value or data stored in the node(s)
    Node *prev;
    Node *next;
    // constructor of nodes to start data and pointers
    Node(int val, Node *p = nullptr, Node *n = nullptr) {
      data = val;
      prev = p;
      next = n;
    }
  };

  Node *head;
  Node *tail;// pointers to the start and end of the list

public:
//a default constructor to start an empty list with head and tail as nullptr
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
  }
  // insert new node after a given position 
  void insert_after(int value, int position) {
    if (position < 0) {
      cout << "Position must be >= 0." << endl;
      return;
    }

    Node *newNode = new Node(value);// create the new node
    if (!head) {// if the list is empty then we set head and tail to the new node
      head = tail = newNode;
      return;
    }

    Node *temp = head;
    for (int i = 0; i < position && temp; ++i)//loop to find the position
      temp = temp->next;
    
    if (!temp) {// if position is out of bounds
      cout << "Position exceeds list size. Node not inserted.\n";
      delete newNode;// in case of memory leak
      return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;// adjust the pointers to link the new node
    if (temp->next)
      temp->next->prev = newNode;
    else
      tail = newNode;
    temp->next = newNode;//if inserting at the end update tail
  }

    // a method to erase a node by their value
  void delete_val(int value) {
    if (!head)// if the list is empty
      return;
    Node *temp = head;// go through the list to find the node with the given value
    while (temp && temp->data != value)
      temp = temp->next;
    if (!temp)
      return;
    if (temp->prev)
      temp->prev->next = temp->next;
    else
      head = temp->next;
    // if the node to delete is the head, update head
    if (temp->next)
      temp->next->prev = temp->prev;
    else
      tail = temp->prev;
    delete temp;// delete the node
  }

    // erase node by position (1based? I am not sure)
  void delete_pos(int pos) {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }// empty list case
    
    if (pos == 1) {
      pop_front();
      return;
    }//if deleting head node

    Node *temp = head;// start from head node

    for (int i = 1; i < pos; i++) {// loop to find the position
      if (!temp) {
        cout << "Position doesn't exist." << endl;
        return;
      } else
        temp = temp->next;// move to next node
    }

    if (!temp) {
      cout << "Position doesn't exist." << endl;
      return;
    }// if position is out of bounds

    if (!temp->next) {
      pop_back();
      return;
    }// if deleting tail node

    Node *tempPrev = temp->prev;// pointer to the previous node
    // adjust pointers to remove the node from the list
    tempPrev->next = temp->next;
    temp->next->prev = tempPrev;// link the next node back to the previous node
    delete temp;// delete the node 
  }

  void push_back(int v) {
    Node *newNode = new Node(v);
    if (!tail)
      head = tail = newNode;
    else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  void push_front(int v) {
    Node *newNode = new Node(v);
    if (!head)
      head = tail = newNode;
    else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  void pop_front() {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }
    Node *temp = head;
    if (head->next) {
      head = head->next;
      head->prev = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }

  void pop_back() {
    if (!tail) {
      cout << "List is empty." << endl;
      return;
    }
    Node *temp = tail;
    if (tail->prev) {
      tail = tail->prev;
      tail->next = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }

  ~DoublyLinkedList() {
    while (head) {
      Node *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void print() {
    Node *current = head;
    if (!current) {
      cout << "List is empty." << endl;
      return;
    }
    while (current) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << endl;
  }

  void print_reverse() {
    Node *current = tail;
    if (!current) {
      cout << "List is empty." << endl;
      return;
    }
    while (current) {
      cout << current->data << " ";
      current = current->prev;
    }
    cout << endl;
  }
};

int main() {
  cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid
  DoublyLinkedList list;

  cout << "list forward:  ";
  list.print();
  //to print the list forward
  cout << "list backward: ";
  list.print_reverse();
  //to print the list backward
    return 0;
}