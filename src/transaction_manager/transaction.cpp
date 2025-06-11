#include "../include/transaction_manager/transaction.hpp"
#include <iostream>

namespace rdbms
{

    LockManager::LockManager() {}

    LockManager::~LockManager()
    {
        table_locks.clear();
    }

    bool LockManager::acquireLock(const std::string &tableName, LockType)
    {
        if (table_locks.find(tableName) == table_locks.end())
        {
            std::cout << "Acquiring new lock on table: " << tableName << "\n";
            table_locks[tableName] = true;
            return true;
        }
        else
        {
            std::cout << "Table '" << tableName << "' is already locked!\n";
            return false;
        }
    }

    void LockManager::releaseLock(const std::string &tableName)
    {
        std::cout << "Releasing lock on table: " << tableName << "\n";
        table_locks.erase(tableName);
    }

    bool LockManager::isLocked(const std::string &tableName) const
    {
        return table_locks.find(tableName) != table_locks.end();
    }

}
