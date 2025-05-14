#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../include/query_processor/executor.hpp"
#include "../include/security/access_control.hpp"
#include "../include/database/database.hpp"
#include "../include/backup_recovery/recovery.hpp" // Include recovery manager

using namespace std;
using namespace rdbms;

// Show available commands
void showCommands()
{
    cout << "\nAvailable Commands:\n"
         << "  CREATE_DATABASE <name>\n"
         << "  CREATE_TABLE <table_name> <col1:type1> <col2:type2> ...\n"
         << "  INSERT <table_name> <val1> <val2> ...\n"
         << "  SELECT <columns> FROM <table_name>\n"
         << "  DELETE <table_name> WHERE <column> = <value>\n"
         << "  UPDATE <table_name> SET <column> = <value> WHERE <column> = <value>\n"
         << "  JOIN <table1> <table2> ON <column1> = <column2>\n"
         << "  GROUP_BY <table_name> <column>\n"
         << "  ORDER <table_name> <column> ASC|DESC\n"
         << "  MATCH <table_name> <column> <value>\n"
         << "  LIMIT <table_name> <n>\n"
         << "  DISTINCT <table_name> <column>\n"
         << "  CREATE_INDEX <table_name> <column>\n"
         << "  SHOWDATABASE\n"
         << "  SHOWTABLES\n"
         << "  FLUSH\n"
         << "  PUT <key> <value>\n"
         << "  GET <key>\n"
         << "  REMOVE <key>\n"
         << "  HELP\n"
         << "  EXIT\n";
}

int main()
{
    cout << "===================================\n";
    cout << "  Welcome to Custom RDBMS Console  \n";
    cout << "===================================\n";

    // Setup users
    AccessControl accessControl;
    accessControl.addUser("admin", "admin123", Role::ADMIN);
    accessControl.addUser("guest", "guest123", Role::GUEST);

    string username, password;
    cout << "\nLogin\n------\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (!accessControl.authenticate(username, password))
    {
        cout << "Authentication failed. Exiting...\n";
        return 1;
    }

    Role userRole = accessControl.getUserRole(username);
    cout << "Login successful. Role: " << (userRole == Role::ADMIN ? "Admin" : "Guest") << "\n";

    Database database;
    Executor executor(database);

    // This must match the actual DB file used in your system
    const std::string databaseFileName = "database.txt";
    RecoveryManager recoveryManager(databaseFileName);

    cin.ignore(); // Clear input buffer
    string input;

    showCommands();

    while (true)
    {
        cout << "\n>>> ";
        getline(cin, input);
        if (input.empty())
            continue;

        // Parse command and arguments
        istringstream iss(input);
        vector<string> tokens;
        string token;
        while (iss >> token)
            tokens.push_back(token);

        if (tokens.empty())
            continue;

        string command = tokens[0];

        // Convert command to uppercase for robustness
        for (auto &c : command)
            c = toupper(c);

        if (command == "EXIT")
        {
            cout << "Exiting database. Goodbye!\n";
            break;
        }

        if (command == "HELP")
        {
            showCommands();
            continue;
        }

        // Handle BACKUP
        if (command == "BACKUP" && tokens.size() == 2)
        {
            string backupName = tokens[1];
            if (recoveryManager.createBackup(backupName))
                cout << "Backup created successfully as '" << backupName << "'\n";
            else
                cout << "Backup failed.\n";
            continue;
        }

        // Handle RESTORE
        if (command == "RESTORE" && tokens.size() == 2)
        {
            string backupName = tokens[1];
            if (recoveryManager.restoreBackup(backupName))
                cout << "Database restored successfully from '" << backupName << "'\n";
            else
                cout << "Restore failed.\n";
            continue;
        }

        // Everything else handled by executor
        try
        {
            executor.executeCommand(input);
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
