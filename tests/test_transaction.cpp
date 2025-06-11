#include "../include/transaction_manager/transaction.hpp"
#include <iostream>

void simulateTransaction(int id, rdbms::LockManager &lockManager, const std::string &tableName)
{
    std::cout << "[Transaction " << id << "] Trying to acquire lock...\n";

    bool acquired = lockManager.acquireLock(tableName, rdbms::LockType::WRITE);
    if (acquired)
    {
        std::cout << "[Transaction " << id << "] Lock acquired, doing work... (simulated)\n";
        std::cout << "[Transaction " << id << "] Releasing lock...\n";
        lockManager.releaseLock(tableName);
    }
    else
    {
        std::cout << "[Transaction " << id << "] Could not acquire lock. Aborting transaction.\n";
    }
}

int main()
{
    rdbms::LockManager lockManager;

    simulateTransaction(1, lockManager, "users");

    // Simulate a conflict: T2 runs before T1 has released
    lockManager.acquireLock("users", rdbms::LockType::WRITE); // lock manually
    simulateTransaction(2, lockManager, "users");             // should fail
    lockManager.releaseLock("users");                         // manual release

    simulateTransaction(3, lockManager, "users"); // now succeeds

    return 0;
}
