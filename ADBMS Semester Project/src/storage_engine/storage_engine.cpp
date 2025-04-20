#include "../include/storage_engine/storage_engine.hpp"
#include "../../include/config/constants.hpp"
#include <iostream>

using namespace std;

namespace rdbms
{

    StorageEngine::StorageEngine(const string &table, int bufferSize)
        : bufferPool(bufferSize), tableName(table)
    {
        fileManager.createFile(tableName);
        fileManager.openFile(tableName);
    }

    bool StorageEngine::insert(int key, const string &value)
    {
        Page page;
        page.writeData(value);

        // Pick a page number based on key (or just use key as page number for now)
        int pageNumber = key;

        // Write to file
        if (!fileManager.writePage(tableName, pageNumber, page.getRawData()))
        {
            cerr << "Failed to write page for key: " << key << endl;
            return false;
        }

        // Add to buffer pool
        string pageId = tableName + "_" + to_string(pageNumber);
        bufferPool.addPage(pageId, page);

        // Add to index
        index.insert(key, pageId);
        return true;
    }

    string StorageEngine::search(int key)
    {
        string pageId = index.search(key);

        if (pageId == "Key not found")
        {
            return "Key not found";
        }

        // Try to get from buffer pool
        if (bufferPool.hasPage(pageId))
        {
            Page page = bufferPool.getPage(pageId);
            return page.readData();
        }

        // Otherwise load from file
        int pageNumber = stoi(pageId.substr(pageId.find('_') + 1));
        char buffer[PAGE_SIZE];
        if (!fileManager.readPage(tableName, pageNumber, buffer))
        {
            return "Failed to load page";
        }

        Page page;
        page.loadFromRawData(buffer);
        bufferPool.addPage(pageId, page);
        return page.readData();
    }

    void StorageEngine::printStorage()
    {
        index.printTree();
        bufferPool.printLRU();
    }
    void StorageEngine::flushAll()
    {
        cout << "Flushing all pages from BufferPool to disk...\n";

        const auto &cache = bufferPool.getCache();

        for (const auto &entry : cache)
        {
            const string &pageId = entry.first;
            const Page &page = entry.second;

            size_t underscorePos = pageId.find_last_of('_');
            if (underscorePos == string::npos)
                continue;

            string filename = pageId.substr(0, underscorePos);
            int pageNumber = stoi(pageId.substr(underscorePos + 1));

            fileManager.writePage(filename, pageNumber, page.getRawData());
            cout << "Flushed page: " << pageId << " to disk.\n";
        }
    }
} // namespace rdbms
