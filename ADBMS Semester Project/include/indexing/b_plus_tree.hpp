#ifndef B_PLUS_TREE_HPP
#define B_PLUS_TREE_HPP

#include <map>
#include <vector>
#include <string>

namespace rdbms
{

    class BPlusTree
    {
    private:
        std::map<int, int> tree; // key -> numeric value

    public:
        BPlusTree();
        void insert(int key, int value);
        bool remove(int key);
        int search(int key);
        std::vector<int> searchByCondition(int value, const std::string &condition);
        void printTree();
    };

} // namespace rdbms

#endif // B_PLUS_TREE_HPP
