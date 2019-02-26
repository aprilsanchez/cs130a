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

//Helper function for splay
void splayTree::rotateRight(Node* P) {
    Node* n = P->left;
    Node* r = n->right;
    Node* p = P->parent;

    //assign new parent of n, if it's not NULL
    if (p) {
        if ( P == p->right) {
            p->right = n;
        }
        else {
            p->left = n;
        }
    }

    //if right child of n exists
    if (r) {
        r->parent = P;
    }

    n->parent = p;
    n->right = P;

    P->parent = n;
    P->left = r;

    if (P == root) {
        root = n;
    }

    return;
}

//Helper function for splay
void splayTree::rotateLeft(Node* P) {
    Node* n = P->right;
    Node* l = n->left;
    Node* p = P->parent;

    //assign new parent of n, it's not NULL
    if (p) {
        if (P == p->left) {
            p->left = n;
        }
        else {
            p->right = n;
        }
    }

    //if left child of n exists
    if (l) {
        l->parent = P;
    }
    n->parent = p;
    n->left = P;
    P->parent = n;
    P->right = l;

    if ( P == root) {
        root = n;
    }

    return;
}


//SPLAY function
void splayTree::splay(Node* n) {
    //Case 0: n is the root
    if (n == root) {
        return;
    }

    //Case 1: parent(n) is the root; single rotation
    else if (n->parent == root) {
        //if n is a left child
        if (n == n->parent->left) {
            rotateRight(n->parent);
        }
        else {
            rotateLeft(n->parent);
        }
        return;
    } 

 //Case 2: parent(n) is not the root
    else if ( (n == n->parent->left && n->parent == n->parent->parent->left    ) ) {
        rotateRight(n->parent->parent);
        rotateRight(n->parent);
        return splay(n);
    }
    else if ((n == n->parent->right && n->parent == n->parent->parent->right) ) {
        rotateLeft(n->parent->parent);
        rotateLeft(n->parent);
        return splay(n);
    }

    else if ( n == n->parent->left && n->parent == n->parent->parent->right) {
        rotateRight(n->parent);
        rotateLeft(n->parent->parent);
    }

    else {
        rotateLeft(n->parent);
        rotateRight(n->parent->parent);
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
       // std::cout << "found " << i << ", calling splay(" << i << ")" << std::endl;
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

    //now that we have have, make it the root of t1
    //assign left child of max as left child of max's parent
    
    //edge case
    if (max == t1) {
        max->right = t2;
        max->right->parent = max;
        t2 = NULL;
        return max;
    
    }
    //else
    max->parent->right = max->left;
    if (max->left) {
        max->left->parent = max->parent; 
    }

    max->parent = NULL;

    max->left = t1;
    t1->parent = max;
    t1 = NULL;

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
    access(i);

    if (root->data != i) {
        std::cout << "item " << i << " not deleted; not present" << std::endl;
        return;
    }
    //else the item exists in the tree
    //
    Node* left = root->left;
    Node* right = root->right;
    if (left) {
        left->parent = NULL;
    }
    if (right) {
        right->parent = NULL;
    }
    root->left = NULL;
    root->right = NULL;
    delete root;

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

