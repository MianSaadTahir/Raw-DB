#include "../include/query_processor/executor.hpp"
#include <sstream>
#include <iostream>

Executor::Executor(Database &db) : db(db) {}

void Executor::executeCommand(const std::string &commandLine)
{
    std::istringstream stream(commandLine);
    std::string command;
    stream >> command;

    std::vector<std::string> args;
    std::string word;
    while (stream >> word)
    {
        args.push_back(word);
    }

    if (command == "PUT")
        executePut(args);
    else if (command == "GET")
        executeGet(args);
    else if (command == "REMOVE")
        executeRemove(args);
    else if (command == "SHOW")
        executeShow();
    else if (command == "FLUSH")
        executeFlush();
    else if (command == "EXIT")
        executeExit();
    else if (command == "CREATE_DATABASE")
        executeCreateDatabase(args);
    else if (command == "ALTER_DATABASE")
        executeAlterDatabase(args);
    else if (command == "JOIN")
        executeJoin(args);
    else if (command == "GROUP_BY")
        executeGroupBy(args);
    else if (command == "ORDER")
        executeOrder(args);
    else if (command == "MATCH")
        executeMatch(args);
    else if (command == "LIMIT")
        executeLimit(args);
    else if (command == "DISTINCT")
        executeDistinct();
    else if (command == "CREATE_INDEX")
        executeCreateIndex(args);
    else if (command == "UPDATE")
        executeUpdate(args); // Added for UPDATE command
    else if (command == "DELETE")
        executeDelete(args); // Added for DELETE command
    else if (command == "SELECT")
        executeSelect(args); // Added for SELECT command
    else
        std::cout << "Unknown command: " << command << std::endl;
}

// Implementation of executeUpdate for handling the UPDATE command
void Executor::executeUpdate(const std::vector<std::string> &args)
{
    if (args.size() < 8)
    {
        std::cout << "Invalid UPDATE command format!" << std::endl;
        return;
    }

    std::string table = args[0];
    std::string column = args[2];
    std::string value = args[4];
    std::string conditionColumn = args[6];
    std::string conditionValue = args[8];

    // Check for operators in the condition column (e.g., !=, <, >)
    std::string operatorStr = args[7];
    db.update(table, column, value, conditionColumn, conditionValue, operatorStr);
}

// Implementation of executeDelete for handling DELETE command
void Executor::executeDelete(const std::vector<std::string> &args)
{
    if (args.size() < 4)
    {
        std::cout << "Invalid DELETE command format!" << std::endl;
        return;
    }

    std::string table = args[2];
    std::string column = args[4];
    std::string conditionValue = args[6];

    db.deleteFrom(table, column, conditionValue);
}

// Implementation of executeSelect for handling SELECT command
void Executor::executeSelect(const std::vector<std::string> &args)
{
    if (args.size() < 4)
    {
        std::cout << "Invalid SELECT command format!" << std::endl;
        return;
    }

    std::string table = args[0];
    std::string column = args[2];
    std::string conditionValue = args[4];

    db.select(table, column, conditionValue);
}
