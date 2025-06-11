#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <unordered_map>

namespace rdbms
{

    enum class LockType
    {
        READ,
        WRITE
    };

    class LockManager
    {
    public:
        LockManager();
        ~LockManager();

        bool acquireLock(const std::string &tableName, LockType lockType);
        void releaseLock(const std::string &tableName);

        bool isLocked(const std::string &tableName) const;

    private:
        std::unordered_map<std::string, bool> table_locks;
    };

} // namespace rdbms

#endif // TRANSACTION_HPP
