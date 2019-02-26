//splayTreeMain.cpp

#include <iostream>
#include <string>
#include "splayTree.h"

using namespace std;

int main() {
    int num;

    cin >> num;
    splayTree tree;

    for (int i = 0; i < num; i++) {
        string command;
        cin >> command;

        if (command == "insert") {
            int i;
            cin >> i;
            tree.insert(i);
        }
        else if (command == "find") {
            int i;
            cin >> i;
            tree.find(i);
        }
        else if (command == "delete") {
            int i;
            cin >> i;
            tree.remove(i);
        }
        else {  //print
            tree.print();
        }
    }
    

    return 0;
}
