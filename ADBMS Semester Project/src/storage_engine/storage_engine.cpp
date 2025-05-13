#include "../include/storage_engine/storage_engine.hpp"
#include "../../include/config/constants.hpp"
#include <iostream>
#include <vector>
#include <string>

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

    void StorageEngine::update(const std::string &column, const std::string &newValue,
                               const std::string &conditionColumn, const std::string &conditionValue, const std::string &operatorStr)
    {
        // Search for rows that match the condition
        std::vector<int> matchingKeys = index.searchByCondition(conditionColumn, conditionValue, operatorStr);

        if (matchingKeys.empty())
        {
            std::cout << "No records found matching the condition." << std::endl;
            return;
        }

        // For each matching row, update the value
        for (int key : matchingKeys)
        {
            std::string pageId = index.search(key);

            if (pageId == "Key not found")
            {
                std::cout << "Key not found: " << key << std::endl;
                continue;
            }

            // Retrieve the page from buffer pool or file
            Page page;
            if (bufferPool.hasPage(pageId))
            {
                page = bufferPool.getPage(pageId);
            }
            else
            {
                int pageNumber = std::stoi(pageId.substr(pageId.find('_') + 1));
                char buffer[PAGE_SIZE];
                if (!fileManager.readPage(tableName, pageNumber, buffer))
                {
                    std::cout << "Failed to load page for key: " << key << std::endl;
                    continue;
                }
                page.loadFromRawData(buffer);
                bufferPool.addPage(pageId, page);
            }

            // Check if the column exists in the page
            if (!page.hasColumn(column))
            {
                std::cout << "Column " << column << " not found in the page." << std::endl;
                continue;
            }

            // Update the column with the new value
            page.updateColumn(column, newValue);

            // Write the updated page back to the buffer pool and disk
            bufferPool.addPage(pageId, page);

            // Flush the page to disk
            int pageNumber = std::stoi(pageId.substr(pageId.find('_') + 1));
            if (!fileManager.writePage(tableName, pageNumber, page.getRawData()))
            {
                std::cout << "Failed to write updated page for key: " << key << std::endl;
            }
            else
            {
                std::cout << "Successfully updated record for key: " << key << std::endl;
            }
        }
    }

    void StorageEngine::deleteFrom(const std::string &table, const std::string &column, const std::string &conditionValue, const std::string &operatorStr)
    {
        // Search for rows that match the condition
        std::vector<int> matchingKeys = index.searchByCondition(column, conditionValue, operatorStr);

        if (matchingKeys.empty())
        {
            std::cout << "No records found matching the condition." << std::endl;
            return;
        }

        // For each matching row, delete it from the storage
        for (int key : matchingKeys)
        {
            std::string pageId = index.search(key);
            if (pageId == "Key not found")
            {
                std::cout << "Key not found: " << key << std::endl;
                continue;
            }

            // Delete the record (remove from index and file)
            index.remove(key);
            bufferPool.removePage(pageId);
            std::cout << "Deleted record for key: " << key << std::endl;
        }
    }

    void StorageEngine::select(const std::string &table, const std::string &column, const std::string &conditionValue, const std::string &operatorStr)
    {
        // Search for rows that match the condition
        std::vector<int> matchingKeys = index.searchByCondition(column, conditionValue, operatorStr);

        if (matchingKeys.empty())
        {
            std::cout << "No records found matching the condition." << std::endl;
            return;
        }

        // Display selected records
        for (int key : matchingKeys)
        {
            std::string pageId = index.search(key);
            if (pageId == "Key not found")
            {
                std::cout << "Key not found: " << key << std::endl;
                continue;
            }

            // Retrieve the page and display its data
            Page page;
            if (bufferPool.hasPage(pageId))
            {
                page = bufferPool.getPage(pageId);
                std::cout << "Selected record: " << page.readData() << std::endl;
            }
            else
            {
                int pageNumber = std::stoi(pageId.substr(pageId.find('_') + 1));
                char buffer[PAGE_SIZE];
                if (!fileManager.readPage(tableName, pageNumber, buffer))
                {
                    std::cout << "Failed to load page for key: " << key << std::endl;
                    continue;
                }
                page.loadFromRawData(buffer);
                std::cout << "Selected record: " << page.readData() << std::endl;
            }
        }
    }

} // namespace rdbms
