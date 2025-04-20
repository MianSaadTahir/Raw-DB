#include "../include/buffer_pool/buffer_pool.hpp"
#include <iostream>

using namespace std;

namespace rdbms
{

    BufferPool::BufferPool(int maxPages) : capacity(maxPages) {}

    void BufferPool::touchPage(const string &pageId)
    {
        lruList.remove(pageId);
        lruList.push_front(pageId);
    }

    bool BufferPool::hasPage(const string &pageId) const
    {
        return pageMap.count(pageId) > 0;
    }

    void BufferPool::addPage(const string &pageId, const Page &page)
    {
        if (pageMap.count(pageId))
        {
            pageMap[pageId] = page;
            touchPage(pageId);
            return;
        }

        if (pageMap.size() >= capacity)
        {
            string evictId = lruList.back();
            lruList.pop_back();
            pageMap.erase(evictId);
            cout << "Evicted page: " << evictId << endl;
        }

        pageMap[pageId] = page;
        lruList.push_front(pageId);
    }

    Page BufferPool::getPage(const string &pageId)
    {
        if (!hasPage(pageId))
        {
            throw runtime_error("Page not in buffer pool");
        }
        touchPage(pageId);
        return pageMap[pageId];
    }

    void BufferPool::removePage(const string &pageId)
    {
        if (pageMap.count(pageId))
        {
            pageMap.erase(pageId);
            lruList.remove(pageId);
        }
    }

    void BufferPool::printLRU()
    {
        cout << "Current LRU order:\n";
        for (const auto &id : lruList)
        {
            cout << "- " << id << "\n";
        }
    }

    const unordered_map<string, Page> &rdbms::BufferPool::getCache() const
    {
        return pageMap;
    }

} // namespace rdbms
