//splayTree.cpp

#include "splayTree.h"
#include <iostream>
#include <queue>

//Destructor for splayTree
splayTree::~splayTree() {
    clear(root);
}

//Helper function for destructor
void splayTree::clear(Node* n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
    return;
}

//Helper function for splay; does a single notation from n to parent of n
void splayTree::singleRotation(Node* n) {
    Node* temp = n->parent;
    
    if (root == n->parent) {
        root = n;
    }
        
    //if n is a left child
    if (n == temp->left) {
        temp->left = n->right;
        if (n->right) {
            n->right->parent = temp;
        }
        n->right = temp;
    }
    else {  // n is a right child
        temp->right = n->left;
        if (n->left) {
            n->left->parent = temp;
        }
        n->left = temp;
    }
    
    //assign n its new parent
    n->parent = temp->parent;
    //if new parent is not NULL, fix its child pointer
    if (n->parent) {
        if (temp == temp->parent->left) {
            temp->parent->left = n;
        }
        else {
            temp->parent->right = n;
        }
    }
    temp->parent = n;

    return;
}

//SPLAY function
void splayTree::splay(Node* n) {
    //Case0: n is the root
    if (n == root) {
        return;
    }

    //Case 1: parent(n) is the root; single rotation
    else if (n->parent == root) {
        singleRotation(n);
        return;
    } 

    //Case 2: parent(n) is not the root
    else if ( (n == n->parent->left && n->parent == n->parent->parent->left) || (n == n->parent->right && n->parent == n->parent->parent->right) ) {
        singleRotation(n->parent);
        singleRotation(n);
        splay(n);
    }

    //Case 3:
    else {
        singleRotation(n);
        singleRotation(n);
        splay(n);
    }
    
    return;
}

//ACCESS function, Node* is the most recent non-NULL node we searched
Node* splayTree::access(int i) {
    return access(i, root);
}

//Helper function for ACCESS
Node* splayTree::access(int i, Node* n) {
    //if i is at current node
    
    if(n->data == i) {
        splay(n);
        return n;
    }
    //if i < n->data
    else if (i < n->data) {
        //if there's no left child, splay n and return NULL
        if (n->left == NULL) 
        {
            splay(n);
            return NULL;
        }
        else {  //traverse further down tree
            return access(i, n->left);
        }
    }
    //if i > n->data
    else {
        //if there's no right child, splay n and return NULL
        if (n->right == NULL) {
            splay(n);
            return NULL;
        } 
        else {   //traverse further down tree
            return access(i, n->right);
        }
    }
}

//JOIN function
Node* splayTree::join(Node* t1, Node* t2) {
    if (!t1) {  //t2 is null
        return t2; 
    }
    if (!t2) {
        return t1;
    }
    
    if (!t1 && !t2) {
        return NULL;
    }
    
    //find largest item in t1
    Node* max = t1;

    while (max->right) {
        max = max->right;
    }

    splay(max);
    //max does not have right child; make t2 its right child to join the trees
    max->right = t2;
    t2->parent = max;
    t2 = NULL;

    return max; 

}

//SPLIT function
std::pair<Node*, Node*> splayTree::split(int i, Node* t) {
    access(i, t);

    Node* left;
    Node* right;

    if (root->data > i) {
        left = root->left;
        root->left = NULL;
        right = root;
    }
    else {
        right = root->right;
        root->right = NULL;
        left = root;
    }
    if (left) {
        left->parent = NULL;
    }
    if (right) {
        right->parent = NULL;
    }
    t = NULL;

    std::pair<Node*, Node*> result;
    result.first = left;
    result.second = right;
    return result;
}

//FIND function
void splayTree::find(int i) {
    if (!root) {
        std::cout << "item " << i << " not found" << std::endl;
        return;
    }
    if (access(i)) {
        std::cout << "item " << i << " found" << std::endl;
    }
    else {
        std::cout << "item " << i << " not found" << std::endl;
    }
    return;
}

//INSERT function
void splayTree::insert(int i) {
    //if splayTree is empty
    if (!root) {
        root = new Node(i);
        std::cout << "item " << i << " inserted" << std::endl;
        return;
    }
    
    //else i does not already exist, so insert it into the tree
    std::pair<Node*, Node*> p = split(i, root);

    if (p.first) {
        if (p.first->data == i) {
            root = join(p.first, p.second);
            std::cout << "item " << i << " not inserted; already present" << std::endl;
            return;
        }
    }
    //else
    root = new Node(i);
    root->left = p.first;
    root->right = p.second;
    if (p.first) { //if the left child is not NULL
        root->left->parent = root;
    }
    if (p.second) { //if the right child is not NULL 
        root->right->parent = root;
        
    }
    std::cout << "item " << i << " inserted" << std::endl;
    return;
    
}

void splayTree::remove(int i) {
    if (!root) {
        std::cout << "item " << i << " not deleted; not present" << std::endl;
        return;
    }
    access(i);

    if (root->data != i) {
        std::cout << "item " << i << " not deleted; not present" << std::endl;
        return;
    }
    //else the item exists in the tree
    //
    Node* left = root->left;
    Node* right = root->right;

    if (!left && !right) {
        delete root;
        root = NULL;
        std::cout << "item " << i << " deleted" << std::endl;
        return;
    }

    if (left) {
        left->parent = NULL;
    }
    if (right) {
        right->parent = NULL;
    }
    root->left = NULL;
    root->right = NULL;
    delete root;

    root = left;
    root = join(left, right);

    std::cout << "item " << i << " deleted" << std::endl;
    return;
}

void splayTree::print() {
    print(root);
}

void splayTree::print(Node* r) {
    //Base Case
    if (r == NULL) {
        return;
    }

    Node* n;
    std::queue<Node*> q;
    int currNum = 0;
    int nextNum = 0;

    //store root in queue
    q.push(r);
    currNum++;

    while (!q.empty()) {
        n = q.front();
        std::cout << n->data;
        q.pop();
        currNum--;

        if (n->left) {
            q.push(n->left);
            nextNum++;
        }

        if (n->right) {
            q.push(n->right);
            nextNum++;
        }

        if (currNum == 0) {
            currNum = nextNum;
            nextNum = 0;
            std::cout << std::endl;
        }
        else {
            std::cout << ", ";
        }
    }
    return;

}

