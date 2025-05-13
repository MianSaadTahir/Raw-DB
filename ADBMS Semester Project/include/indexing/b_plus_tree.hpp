#ifndef B_PLUS_TREE_HPP
#define B_PLUS_TREE_HPP

#include <vector>
#include <string>

namespace rdbms
{
    const int MAX_KEYS = 3; // adjust this for testing (smaller = more splits)

    struct BPlusTreeNode
    {
        bool isLeaf;
        std::vector<int> keys;
        std::vector<std::string> values;       // only used in leaf
        std::vector<BPlusTreeNode *> children; // used in internal nodes

        BPlusTreeNode(bool leaf);
    };

    class BPlusTree
    {
    private:
        BPlusTreeNode *root;

        void insertInternal(int key, const std::string &value, BPlusTreeNode *node,
                            BPlusTreeNode *&newChild, int &newKey);
        bool removeInternal(int key, BPlusTreeNode *node, BPlusTreeNode *&newChild, int &newKey);
        void fixAfterRemoval(BPlusTreeNode *node, int pos);

        bool checkCondition(const std::string &value, const std::string &conditionValue, const std::string &operatorStr);

    public:
        BPlusTree();
        ~BPlusTree();

        void insert(int key, const std::string &value);
        bool remove(int key);
        std::string search(int key);
        std::vector<int> searchByCondition(const std::string &column, const std::string &conditionValue, const std::string &operatorStr);
        bool checkConditionOnPage(const std::string &pageId, const std::string &column, const std::string &value);
        void printTree(); // for debug
        void printRecursive(BPlusTreeNode *node, int level);
    };
}

#endif
