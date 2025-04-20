#ifndef STORAGE_ENGINE_HPP
#define STORAGE_ENGINE_HPP

#include "../file_manager/file_manager.hpp"
#include "../buffer_pool/buffer_pool.hpp"
#include "../indexing/b_plus_tree.hpp"
#include "../page/page.hpp"

namespace rdbms
{

    class StorageEngine
    {
    private:
        FileManager fileManager;
        BufferPool bufferPool;
        BPlusTree index;
        string tableName;

    public:
        StorageEngine(const string &tableName, int bufferSize = 5);

        bool insert(int key, const string &value);
        string search(int key);
        void printStorage();

        void flushAll(); // Write all dirty pages back to disk
    };

} // namespace rdbms

#endif // STORAGE_ENGINE_HPP
