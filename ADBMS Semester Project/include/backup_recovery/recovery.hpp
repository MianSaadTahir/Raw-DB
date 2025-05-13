#ifndef RECOVERY_HPP
#define RECOVERY_HPP

#include <string>
#include <vector>

namespace rdbms
{

    class RecoveryManager
    {
    private:
        std::string dbFileName;
        std::string backupLogFile;

    public:
        RecoveryManager(const std::string &dbFile);

        bool createBackup(const std::string &backupName);
        std::vector<std::string> listBackups();
        bool restoreBackup(const std::string &backupName);
    };

} // namespace rdbms

#endif // RECOVERY_HPP
