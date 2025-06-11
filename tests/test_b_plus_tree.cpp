#include "../include/indexing/b_plus_tree.hpp"
#include <iostream>
#include <cassert>

using namespace rdbms;
using namespace std;

void testInsert()
{
    BPlusTree tree;
    tree.insert(10, 100);
    tree.insert(20, 200);
    tree.insert(30, 300);

    assert(tree.search(10) == 100);
    assert(tree.search(20) == 200);
    assert(tree.search(30) == 300);

    cout << "Insert Test Passed!" << endl;
}

void testRemove()
{
    BPlusTree tree;
    tree.insert(10, 100);
    tree.insert(20, 200);
    tree.insert(30, 300);

    assert(tree.remove(20) == true);
    assert(tree.search(20) == -1); // not found
    assert(tree.remove(40) == false);

    cout << "Remove Test Passed!" << endl;
}

void testSearchByCondition()
{
    BPlusTree tree;
    tree.insert(10, 100);
    tree.insert(20, 200);
    tree.insert(30, 300);
    tree.insert(40, 400);

    vector<int> result = tree.searchByCondition(200, "=");
    assert(result.size() == 1 && result[0] == 20);

    result = tree.searchByCondition(250, ">");
    cout << "Result for values greater than 250: ";
    for (size_t i = 0; i < result.size(); ++i)
        cout << result[i] << " ";
    cout << endl;
    assert(result.size() == 2 && result[0] == 30 && result[1] == 40);

    result = tree.searchByCondition(150, "<");
    assert(result.size() == 1 && result[0] == 10);

    cout << "Search by Condition Test Passed!" << endl;
}

void testPrintTree()
{
    BPlusTree tree;
    tree.insert(5, 50);
    tree.insert(15, 150);
    tree.insert(25, 250);

    cout << "Tree Structure:" << endl;
    tree.printTree();
}

int main()
{
    testInsert();
    testRemove();
    testSearchByCondition();
    testPrintTree();

    return 0;
}
