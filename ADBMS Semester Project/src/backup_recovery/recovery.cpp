#include "../include/backup_recovery/recovery.hpp"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iostream>

namespace rdbms
{

    RecoveryManager::RecoveryManager(const std::string &dbFile)
        : dbFileName(dbFile), backupLogFile("backup_list.txt") {}

    bool RecoveryManager::createBackup(const std::string &backupName)
    {
        std::ifstream src(dbFileName.c_str(), std::ios::binary);
        if (!src.is_open())
        {
            std::cerr << "Error: Cannot open source database file.\n";
            return false;
        }

        std::ofstream dst(backupName.c_str(), std::ios::binary);
        if (!dst.is_open())
        {
            std::cerr << "Error: Cannot create backup file.\n";
            return false;
        }

        dst << src.rdbuf();
        src.close();
        dst.close();

        std::ofstream log(backupLogFile.c_str(), std::ios::app);
        if (!log.is_open())
        {
            std::cerr << "Error: Cannot write to backup log.\n";
            return false;
        }
        log << backupName << "\n";
        log.close();

        return true;
    }

    std::vector<std::string> RecoveryManager::listBackups()
    {
        std::vector<std::string> backups;
        std::ifstream log(backupLogFile.c_str());
        if (!log.is_open())
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

        log.close();
        return backups;
    }

    bool RecoveryManager::restoreBackup(const std::string &backupName)
    {
        std::ifstream src(backupName.c_str(), std::ios::binary);
        if (!src.is_open())
        {
            std::cerr << "Error: Cannot open backup file.\n";
            return false;
        }

        std::ofstream dst(dbFileName.c_str(), std::ios::binary | std::ios::trunc);
        if (!dst.is_open())
        {
            std::cerr << "Error: Cannot open database file for restore.\n";
            return false;
        }

        dst << src.rdbuf();
        src.close();
        dst.close();

        return true;
    }

} // namespace rdbms
