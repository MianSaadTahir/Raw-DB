#ifndef BUFFER_POOL_HPP
#define BUFFER_POOL_HPP

#include "../page/page.hpp"
#include <unordered_map>
#include <list>
#include <string>
using namespace std;

namespace rdbms
{

    class BufferPool
    {
    private:
        int capacity;
        unordered_map<string, Page> pageMap;
        list<string> lruList;

        void touchPage(const string &pageId);

    public:
        BufferPool(int maxPages = 5); // default size 5

        bool hasPage(const string &pageId) const;
        void addPage(const string &pageId, const Page &page);
        Page getPage(const string &pageId);
        void removePage(const string &pageId);
        void printLRU();

        const unordered_map<string, Page> &getCache() const;
    };

} // namespace rdbms

#endif // BUFFER_POOL_HPP
