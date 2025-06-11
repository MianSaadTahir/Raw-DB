#ifndef STORAGE_ENGINE_HPP
#define STORAGE_ENGINE_HPP

#include "../file_manager/file_manager.hpp"
#include "../buffer_pool/buffer_pool.hpp"
#include "../indexing/b_plus_tree.hpp"
#include "../page/page.hpp"
#include <vector>
#include <string>

namespace rdbms
{
    class StorageEngine
    {
    private:
        FileManager fileManager;
        BufferPool bufferPool;
        BPlusTree index;
        std::string tableName;

    public:
        StorageEngine(const std::string &tableName, int bufferSize = 5);

        bool insert(int key, const std::string &value);
        std::string search(int key);
        void printStorage();
        void flushAll();

        void update(const std::string &column, const std::string &newValue,
                    const std::string &conditionColumn, const std::string &conditionValue, const std::string &operatorStr);

        void deleteFrom(const std::string &table, const std::string &column,
                        const std::string &conditionValue, const std::string &operatorStr);

        void select(const std::string &table, const std::string &column,
                    const std::string &conditionValue, const std::string &operatorStr);
    };
} // namespace rdbms

#endif // STORAGE_ENGINE_HPP
