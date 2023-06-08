/* ---------------------------------------------
Program 4: Priority Queue
Course: CS 251, Fall 2022. 
System: MacOS using replit
Author: Yousef Habeeb
UIN: 652622525
---------------------------------------------
*/
#pragma once

#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

template <typename T> class priorityqueue {
private:
  struct NODE {
    int priority; // used to build BST
    T value;      // stored data for the p-queue
    bool dup;     // marked true when there are duplicate priorities
    NODE *parent; // links back to parent
    NODE *link;   // links to linked list of NODES with duplicate priorities
    NODE *left;   // links to left child
    NODE *right;  // links to right child
  };
  NODE *root; // pointer to root node of the BST
  int size;   // # of elements in the pqueue
  NODE *curr; // pointer to next item in pqueue (see begin and next)



  void copy(NODE *other) {
    if (other != nullptr) {

      this->enqueue(other->value, other->priority);

      copy(other->left);
      if (other->dup == true) {
        copy(other->link);
      }
      copy(other->right);
    }
  }



// deletes every node recursively 
  void del(NODE *curr) {
    if (curr == nullptr) {
      return;
    } 
    else {
      del(curr->left);

      if (root->dup == true) {
        del(curr->link);
      }

      del(curr->right);

      size--;
      delete curr;
    }
  }



// prints out duplicate nodes
  void duplicate(NODE *dups, ostream &out) {
    if (dups == nullptr) {
      return;
    }
    out << dups->priority << " Value: " << dups->value << endl;
    duplicate(dups->link, out);
  }

  //  prints out current priority queue
  void pair(NODE *curr, ostream &out) {

    if (curr == nullptr) {
      return;
    } else {
      pair(curr->left, out);
      out << curr->priority << " Value: " << curr->value << endl;
      if (curr->dup == true) {
        duplicate(curr->link, out);
      }
      pair(curr->right, out);
    }
  }


  // checks if another priorirty queue is equal to the original 
  bool equal(NODE *curr, NODE *other) {

    if (curr == nullptr && other == nullptr) {
      return true;
    } else if (curr == nullptr) {
      return false;
    } else if (other == nullptr) {
      return false;
    } else {
      if ((equal(curr->left, other->left)) &&
          (curr->priority == other->priority) &&
          (curr->value == other->value) && (equal(curr->link, other->link)) &&
          (equal(curr->right, other->right))) {
        return true;
      } else {
        return false;
      }
    }
  }


// finds the smallest node value
  NODE *minValueNode(NODE *node) {
    NODE *curr = node;
    while (curr && curr->left != NULL)
      curr = curr->left;

    return curr;
  }

  // deletes the smallest node and re assigns the tree nodes
  NODE *deleteNode(NODE *curr) {
    // base case
    if (curr == NULL)
      return curr;

    // node has no child
    if (curr->left == nullptr) {
      if (curr == root) {
        if (curr->right == nullptr) {
          delete curr;
          root = nullptr;
          return nullptr;
        } 
        else {
          NODE *temp = curr;
          curr = curr->right;
          root = curr;
          delete temp;
          return root;
        }
      } 
      else if (curr->right == nullptr) {
        NODE *temp = curr;

        curr = curr->parent;
        curr->left = nullptr;
        delete temp;
        return curr;
      } 
      else {
        NODE *temp = curr;
        NODE *par = curr->parent;
        curr = curr->right;
        par->left = curr;
        curr->parent = par;
        delete temp;
        return curr;
      }
    }
    return curr;
  }


  

    bool BST(NODE* curr, T &value,int &priority){
      if(curr == nullptr){
          return false; 
      }
      value = curr->value;
      priority = curr-> priority;
      
      // if(curr-> dup == true){
      //     BSTdup(curr);
      // }

      if(curr ->right  != nullptr){
          curr = curr -> right;
          curr = minValueNode(curr);
          return true;
      }
      else{
        NODE* par = curr-> parent;
        while (par != nullptr && curr == curr->right){
          curr = par;
          par = par -> parent;
        }
        curr = par;
        return true;
      } 
    }

public:
  //
  // default constructor:
  //
  // Creates an empty priority queue.
  // O(1)
  //
  priorityqueue() {

    root = nullptr;
    size = 0;
    curr = nullptr;
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  // Sets all member variables appropriately.
  // O(n), where n is total number of nodes in custom BST

  priorityqueue &operator=(const priorityqueue &other) {

    this->clear();
    // copies the tree
    copy(other->root);
    this->size = other->size;
    return *this;
  }

  //
  // clear:
  //
  // Frees the memory associated with the priority queue but is public.
  // O(n), where n is total number of nodes in custom BST

  //
  void clear() {

    curr = root;
    // deletes every node and assigns the last null
    del(curr);
    root = nullptr;
  }

  //
  // destructor:
  //
  // Frees the memory associated with the priority queue.
  // O(n), where n is total number of nodes in custom BST
  //
  ~priorityqueue() {
    clear(); 
    }

  //
  // enqueue:
  //
  // Inserts the value into the custom BST in the correct location based on
  // priority.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  // duplicate priorities
  void enqueue(T value, int priority) {
    NODE *prev = nullptr;
    NODE *cur = root;
  // checks to see where the priority is
    while (cur != nullptr) {
      if (priority == cur->priority) {
        prev = cur;
        cur = nullptr;
      } else if (priority < cur->priority) {
        prev = cur;
        cur = cur->left;
      } else {
        prev = cur;
        cur = cur->right;
      }
    }

    // insterts the new node 
    NODE *n = new NODE();
    n->priority = priority;
    n->value = value;
    n->dup = false;
    n->left = nullptr;
    n->right = nullptr;
    n->link = nullptr;

    if (prev == nullptr) {
      root = n;
    }

    else if (priority == prev->priority) {
      prev->dup = true;
      // to make duplicates
      while (prev->link != nullptr) {
        prev = prev->link;
      }
      prev->link = n;
      n->parent = prev;
    } else if (priority < prev->priority) {
      prev->left = n;
      n->parent = prev;
    } else {
      prev->right = n;
      n->parent = prev;
    }
    size++;
  }
  //
  // dequeue:
  //
  // returns the value of the next element in the priority queue and removes
  // the element from the priority queue.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  //
  
  T dequeue() {
    T valueOut;

    if (root == nullptr) {
      return valueOut;
    }
    NODE *curroot = root;
    curr = root;
    NODE *prev;

    // brings curr to the lowest value 
    while (curr->left != nullptr) {
      prev = curr;
      curr = curr->left;
    }

    valueOut = curr->value;

    // in case of duplicate values
    if (curr->dup == true) {
      NODE *temp = curr;
      curr = curr->link;

      // if there is duplicate values for the root
      if (temp == root) {
        if (temp->right != nullptr) {
          NODE *t2 = temp->right;
          curr->right = t2;
          t2->parent = curr;
          size--;
          delete temp;
          root = curr;
          return valueOut;
        } 
        else {
          root = curr;
          size--;
          delete temp;
          return valueOut;
        }
      }

      prev->left = curr;
      curr->parent = prev;
      size--;
      delete temp;
      return valueOut;
    }
      // if there is no duplicate but different numbers
    else {
      curroot = deleteNode(curr);
      size--;
    }
    return valueOut;
  }

  //
  // Size:
  //
  // Returns the # of elements in the priority queue, 0 if empty.
  // O(1)
  //
  int Size() { 
    return size; 
  }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the
  // call to begin(), the internal state denotes the first inorder
  // node; this ensure that first call to next() function returns
  // the first inorder node value.
  //
  // O(logn), where n is number of unique nodes in tree
  //
  // Example usage:
  //    pq.begin();
  //    while (tree.next(value, priority)) {
  //      cout << priority << " value: " << value << endl;
  //    }
  //    cout << priority << " value: " << value << endl;

// brings curr tot eh smalles value node
  void begin() {

    curr = root;
    while (curr->left != nullptr) {
      curr = curr->left;
    }
    // cout<<curr->priority<< " "<< curr->value;
  }

  //
  // next
  //
  // Uses the internal state to return the next inorder priority, and
  // then advances the internal state in anticipation of future
  // calls.  If a value/priority are in fact returned (via the reference
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more values/priorities are available.  This is the end of the
  // inorder traversal.
  //
  // O(logn), where n is the number of unique nodes in tree
  //
  // Example usage:
  //    pq.begin();
  //    while (pq.next(value, priority)) {
  //      cout << priority << " value: " << value << endl;
  //    }
  //    cout << priority << " value: " << value << endl;

   
   
    bool next(T& value, int &priority) {

       BST(curr, value, priority);
    
       return true;
    }
  //
  // toString:
  //
  // Returns a string of the entire priority queue, in order.  Format:
  // "1 value: Ben
  //  2 value: Jen
  //  2 value: Sven
  //  3 value: Gwen"
  string toString() {

    string str = "";
    curr = root;
    stringstream s;
    pair(curr, s);
    str = s.str();

    return str;
  }

  //
  // peek:
  //
  // returns the value of the next element in the priority queue but does not
  // remove the item from the priority queue.
  // O(logn + m), where n is number of unique nodes in tree and m is number of
  // duplicate priorities
  //
  T peek() {

    T valueOut;

    NODE *currroot = root;

    if (currroot == nullptr) {
      return valueOut;
    }

    // brings curroot to the loqest value node
    while (currroot->left != nullptr) {
      currroot = currroot->left;
    }
    // peek at the next value
    valueOut = currroot->value;

    // cout << "Peek Value: " << valueOut << endl;
    return valueOut;
  }

  //
  // ==operator
  //
  // Returns true if this priority queue as the priority queue passed in as
  // other.  Otherwise returns false.
  // O(n), where n is total number of nodes in custom BST

  // returns true or false for the equal operator
  //

  bool operator==(const priorityqueue &other) const {
    // recursive function checker 
    return equal(this->root, other->root);
  }

  //
  // getRoot - Do not edit/change!
  //
  // Used for testing the BST.
  // return the root node for testing.
  //
  void *getRoot() { return root; }
};
