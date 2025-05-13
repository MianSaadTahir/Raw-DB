#include "../../include/indexing/b_plus_tree.hpp"
#include <iostream>

namespace rdbms
{

    BPlusTree::BPlusTree() {}

    void BPlusTree::insert(int key, int value)
    {
        tree[key] = value;
    }

    bool BPlusTree::remove(int key)
    {
        return tree.erase(key) > 0;
    }

    int BPlusTree::search(int key)
    {
        if (tree.find(key) != tree.end())
        {
            return tree[key];
        }
        return -1; // indicates "not found"
    }

    std::vector<int> BPlusTree::searchByCondition(int value, const std::string &condition)
    {
        std::vector<int> result;
        for (std::map<int, int>::iterator it = tree.begin(); it != tree.end(); ++it)
        {
            if (condition == "=" && it->second == value)
            {
                result.push_back(it->first);
            }
            else if (condition == ">" && it->second > value)
            {
                result.push_back(it->first);
            }
            else if (condition == "<" && it->second < value)
            {
                result.push_back(it->first);
            }
        }
        return result;
    }

    void BPlusTree::printTree()
    {
        for (std::map<int, int>::iterator it = tree.begin(); it != tree.end(); ++it)
        {
            std::cout << it->first << " : " << it->second << std::endl;
        }
    }

} // namespace rdbms
