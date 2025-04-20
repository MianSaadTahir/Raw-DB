#include "../include/indexing/b_plus_tree.hpp"
#include <iostream>
using namespace std;
using namespace rdbms;

int main() {
    BPlusTree tree;

    tree.insert(10, "Ten");
    tree.insert(20, "Twenty");
    tree.insert(5, "Five");
    tree.insert(6, "Six");
    tree.insert(7, "Seven");
    tree.insert(12, "Twelve");
    tree.insert(17, "Seventeen");
    tree.insert(30, "Thirty");

    tree.printTree();

    cout << "Search 12: " << tree.search(12) << "\n";
    cout << "Search 21: " << tree.search(21) << "\n";

    return 0;
}
