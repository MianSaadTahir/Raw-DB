#include "../include/backup_recovery/recovery.hpp"
#include <fstream>
#include <iostream>

namespace rdbms
{
    // Default file name the database is assumed to use
    const std::string DEFAULT_DB_FILE = "database.txt";

    RecoveryManager::RecoveryManager(const std::string &dbFile)
        : dbFileName(dbFile), backupLogFile("backup_list.txt") {}

    bool RecoveryManager::createBackup(const std::string &backupName)
    {
        std::ifstream src(dbFileName, std::ios::binary);
        if (!src)
        {
            std::cerr << "Error: Cannot open source database file: " << dbFileName << "\n";
            return false;
        }

        std::ofstream dst(backupName, std::ios::binary);
        if (!dst)
        {
            std::cerr << "Error: Cannot create backup file: " << backupName << "\n";
            return false;
        }

        dst << src.rdbuf(); // Copy contents
        src.close();
        dst.close();

        std::ofstream log(backupLogFile, std::ios::app);
        if (!log)
        {
            std::cerr << "Error: Cannot write to backup log file.\n";
            return false;
        }

        log << backupName << "\n";
        log.close();

        return true;
    }

    std::vector<std::string> RecoveryManager::listBackups()
    {
        std::vector<std::string> backups;
        std::ifstream log(backupLogFile);
        if (!log)
        {
            std::cerr << "Warning: Backup log file not found.\n";
            return backups;
        }

        std::string name;
        while (std::getline(log, name))
        {
            if (!name.empty())
                backups.push_back(name);
        }

        return backups;
    }

    bool RecoveryManager::restoreBackup(const std::string &backupName)
    {
        std::ifstream src(backupName, std::ios::binary);
        if (!src)
        {
            std::cerr << "Error: Cannot open backup file: " << backupName << "\n";
            return false;
        }

        std::ofstream dst(dbFileName, std::ios::binary | std::ios::trunc);
        if (!dst)
        {
            std::cerr << "Error: Cannot open database file for restore: " << dbFileName << "\n";
            return false;
        }

        dst << src.rdbuf(); // Restore contents
        src.close();
        dst.close();

        return true;
    }

} // namespace rdbms
