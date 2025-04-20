#include "../include/indexing/b_plus_tree.hpp"
#include <iostream>
#include <algorithm> // for lower_bound
using namespace std;

namespace rdbms
{

    BPlusTreeNode::BPlusTreeNode(bool leaf) : isLeaf(leaf) {}

    BPlusTree::BPlusTree()
    {
        root = new BPlusTreeNode(true);
    }

    BPlusTree::~BPlusTree()
    {
        // Recursively delete tree (left as an exercise for now)
    }

    void BPlusTree::insert(int key, const string &value)
    {
        BPlusTreeNode *newChild = nullptr;
        int newKey = -1;
        insertInternal(key, value, root, newChild, newKey);

        if (newChild)
        {
            auto *newRoot = new BPlusTreeNode(false);
            newRoot->keys.push_back(newKey);
            newRoot->children.push_back(root);
            newRoot->children.push_back(newChild);
            root = newRoot;
        }
    }

    void BPlusTree::insertInternal(int key, const string &value, BPlusTreeNode *node,
                                   BPlusTreeNode *&newChild, int &newKey)
    {
        if (node->isLeaf)
        {
            auto it = lower_bound(node->keys.begin(), node->keys.end(), key);
            int pos = it - node->keys.begin();

            node->keys.insert(node->keys.begin() + pos, key);
            node->values.insert(node->values.begin() + pos, value);

            if (node->keys.size() > MAX_KEYS)
            {
                auto *sibling = new BPlusTreeNode(true);
                int mid = node->keys.size() / 2;

                sibling->keys.assign(node->keys.begin() + mid, node->keys.end());
                sibling->values.assign(node->values.begin() + mid, node->values.end());

                node->keys.resize(mid);
                node->values.resize(mid);

                newKey = sibling->keys[0];
                newChild = sibling;
            }
            else
            {
                newChild = nullptr;
            }
        }
        else
        {
            auto it = lower_bound(node->keys.begin(), node->keys.end(), key);
            int pos = it - node->keys.begin();

            BPlusTreeNode *child = node->children[pos];
            BPlusTreeNode *childNew = nullptr;
            int childKey = -1;

            insertInternal(key, value, child, childNew, childKey);

            if (childNew)
            {
                node->keys.insert(node->keys.begin() + pos, childKey);
                node->children.insert(node->children.begin() + pos + 1, childNew);

                if (node->keys.size() > MAX_KEYS)
                {
                    auto *sibling = new BPlusTreeNode(false);
                    int mid = node->keys.size() / 2;

                    sibling->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
                    sibling->children.assign(node->children.begin() + mid + 1, node->children.end());

                    newKey = node->keys[mid];
                    node->keys.resize(mid);
                    node->children.resize(mid + 1);
                    newChild = sibling;
                }
                else
                {
                    newChild = nullptr;
                }
            }
            else
            {
                newChild = nullptr;
            }
        }
    }

    string BPlusTree::search(int key)
    {
        BPlusTreeNode *current = root;

        while (!current->isLeaf)
        {
            auto it = lower_bound(current->keys.begin(), current->keys.end(), key);
            int pos = it - current->keys.begin();
            current = current->children[pos];
        }

        for (int i = 0; i < current->keys.size(); ++i)
        {
            if (current->keys[i] == key)
            {
                return current->values[i];
            }
        }

        return "Key not found";
    }

    void BPlusTree::printRecursive(BPlusTreeNode *node, int level)
    {
        if (!node)
            return;

        cout << "Level " << level << ": ";
        for (int key : node->keys)
            cout << key << " ";
        cout << "\n";

        if (!node->isLeaf)
        {
            for (auto *child : node->children)
            {
                printRecursive(child, level + 1);
            }
        }
    }

    void BPlusTree::printTree()
    {
        printRecursive(root, 0);
    }

}
