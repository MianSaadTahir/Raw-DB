#include "../include/backup_recovery/recovery.hpp"
#include <iostream>
#include <fstream>

using namespace rdbms;

void createDummyDatabase(const std::string &filename)
{
    std::ofstream db(filename.c_str(), std::ios::binary);
    db << "DUMMY DATABASE CONTENT\n";
    db.close();
}

int main()
{
    const std::string dbFile = "main.db";
    RecoveryManager recovery(dbFile);

    std::cout << "[TEST] Creating Dummy Database...\n";
    createDummyDatabase(dbFile);

    std::cout << "[TEST] Creating Backup...\n";
    if (recovery.createBackup("backup1.bak"))
    {
        std::cout << "Backup created successfully.\n";
    }
    else
    {
        std::cout << "Failed to create backup.\n";
    }

    std::cout << "[TEST] Listing Backups...\n";
    std::vector<std::string> backups = recovery.listBackups();
    for (const auto &b : backups)
    {
        std::cout << "- " << b << "\n";
    }

    std::cout << "[TEST] Restoring Backup...\n";
    if (recovery.restoreBackup("backup1.bak"))
    {
        std::cout << "Backup restored successfully.\n";
    }
    else
    {
        std::cout << "Failed to restore backup.\n";
    }

    return 0;
}
