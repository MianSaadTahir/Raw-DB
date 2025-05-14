#include <iostream>
#include <string>
#include "../include/query_processor/executor.hpp"
#include "../include/security/access_control.hpp"
#include "../include/database/database.hpp"

using namespace std;
using namespace rdbms;

void showCommands()
{
    cout << "\nAvailable Commands:\n"
         << "  CREATE_DATABASE <name>\n"
         << "  CREATE_TABLE <table> <col1> <col2> ...\n"
         << "  INSERT <table> <val1> <val2> ...\n"
         << "  SELECT <columns> FROM <table>\n"
         << "  DELETE <table> WHERE <col> = <val>\n"
         << "  UPDATE <table> SET <col> = <val> WHERE <col> = <val>\n"
         << "  JOIN <table1> <table2> ON <col1> = <col2>\n"
         << "  GROUP_BY <table> <column>\n"
         << "  ORDER <table> <column> ASC|DESC\n"
         << "  MATCH <table> <column> <value>\n"
         << "  LIMIT <table> <n>\n"
         << "  DISTINCT <table> <column>\n"
         << "  CREATE_INDEX <table> <column>\n"
         << "  BACKUP <backup_path>\n"
         << "  RESTORE <backup_path>\n"
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
        cout << "❌ Authentication failed. Exiting...\n";
        return 1;
    }

    Role userRole = accessControl.getUserRole(username);
    cout << "✅ Login successful. Role: " << (userRole == Role::ADMIN ? "Admin" : "Guest") << "\n";

    Database database;
    Executor executor(database);

    cin.ignore(); // clear input buffer
    string input;
    showCommands();

    while (true)
    {
        cout << "\n>>> ";
        getline(cin, input);

        if (input.empty())
            continue;

        if (input == "EXIT" || input == "exit" || input == "quit")
        {
            cout << "👋 Exiting database. Goodbye!\n";
            break;
        }

        if (input == "HELP" || input == "help")
        {
            showCommands();
            continue;
        }

        try
        {
            executor.executeCommand(input);
        }
        catch (const std::exception &e)
        {
            cout << "❌ Error: " << e.what() << "\n";
        }
    }

    return 0;
}
