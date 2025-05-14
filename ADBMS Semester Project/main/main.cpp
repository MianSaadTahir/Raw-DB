#include <iostream>
#include <string>
#include "../include/query_processor/executor.hpp"
#include "../include/security/access_control.hpp"
#include "../include/database/database.hpp"

using namespace std;
using namespace rdbms;

// Function to display available commands
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

    // Access Control setup for users
    AccessControl accessControl;
    accessControl.addUser("admin", "admin123", Role::ADMIN);
    accessControl.addUser("guest", "guest123", Role::GUEST);

    string username, password;
    cout << "\nLogin\n------\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Authenticate user
    if (!accessControl.authenticate(username, password))
    {
        cout << "Authentication failed. Exiting...\n";
        return 1;
    }

    // Show user role after login
    Role userRole = accessControl.getUserRole(username);
    cout << "Login successful. Role: " << (userRole == Role::ADMIN ? "Admin" : "Guest") << "\n";

    // Database and executor setup
    Database database;
    Executor executor(database);

    cin.ignore(); // clear input buffer after login
    string input;

    // Display available commands
    showCommands();

    while (true)
    {
        cout << "\n>>> ";
        getline(cin, input); // User input

        if (input.empty()) // Ignore empty commands
            continue;

        // Handle exit command
        if (input == "EXIT" || input == "exit" || input == "quit")
        {
            cout << "Exiting database. Goodbye!\n";
            break;
        }

        // Show available commands
        if (input == "HELP" || input == "help")
        {
            showCommands();
            continue;
        }

        // Execute the command through the executor
        try
        {
            executor.executeCommand(input);
        }
        catch (const std::exception &e)
        {
            cout << "Error: " << e.what() << "\n"; // Catch and display errors
        }
    }

    return 0;
}
