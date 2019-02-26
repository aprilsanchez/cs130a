//splayTree.h
  
#ifndef SPLAYTREE_H
#define SPLAYTREE_H
  
#include <utility>
#include <cstddef> 
struct Node {
     int data;
     Node* left;
     Node* right;
     Node* parent;
     Node(int d): data(d), left(NULL), right(NULL), parent(NULL) {}
};

 
class splayTree {
  
    public:
        splayTree(): root(NULL) {}
        splayTree(Node* n): root(n) {}
        ~splayTree();
        void find(int i);
        void insert(int i);
        void remove(int i);
        void print();
        //Node* root; 
    private:
        Node* root;
        void splay(Node* n);
        Node* access(int i);
        Node* join(Node* t1, Node* t2);
        std::pair<Node*, Node*> split(int i, Node* t);
        void clear(Node* n);    //helper function for destructor
        Node* access(int i, Node* n);    //helper function for access
        void print(Node* r);    //helper function for print
        void singleRotation(Node* n);   //helper function for splay
};

#endif          
