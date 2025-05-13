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
        args.push_back(word);

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
        executeUpdate(args);
    else if (command == "DELETE")
        executeDelete(args);
    else if (command == "SELECT")
        executeSelect(args);
    else
        std::cout << "Unknown command: " << command << std::endl;
}

void Executor::executePut(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "PUT <key> <value>\n";
        return;
    }
    db.insert(args[0], args[1]);
}

void Executor::executeGet(const std::vector<std::string> &args)
{
    std::cout << db.select("Default", args[0], args[1]) << std::endl;
}

void Executor::executeRemove(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "REMOVE <column> <value>\n";
        return;
    }
    db.deleteFrom("Default", args[0], args[1]);
}

void Executor::executeShow()
{
    db.showAllData();
}

void Executor::executeFlush()
{
    db.flushDatabase();
}

void Executor::executeExit()
{
    std::cout << "Exiting database.\n";
    exit(0);
}

void Executor::executeCreateDatabase(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "CREATE_DATABASE <name>\n";
        return;
    }
    db.createDatabase(args[0]);
}

void Executor::executeAlterDatabase(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "ALTER_DATABASE <name>\n";
        return;
    }
    db.alterDatabase(args[0]);
}

void Executor::executeJoin(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "JOIN <key1> <key2>\n";
        return;
    }
    db.join(args[0], args[1]);
}

void Executor::executeGroupBy(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "GROUP_BY <key>\n";
        return;
    }
    db.groupBy(args[0]);
}

void Executor::executeOrder(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "ORDER <key>\n";
        return;
    }
    db.order(args[0]);
}

void Executor::executeMatch(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "MATCH <pattern>\n";
        return;
    }
    db.match(args[0]);
}

void Executor::executeLimit(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "LIMIT <count>\n";
        return;
    }
    db.limit(std::atoi(args[0].c_str()));
}

void Executor::executeDistinct()
{
    db.distinct();
}

void Executor::executeCreateIndex(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "CREATE_INDEX <key>\n";
        return;
    }
    db.createIndex(args[0]);
}

void Executor::executeUpdate(const std::vector<std::string> &args)
{
    if (args.size() < 9)
    {
        std::cout << "UPDATE <table> SET <column> = <value> WHERE <col> <op> <val>\n";
        return;
    }
    db.update(args[0], args[2], args[4], args[6], args[8], args[7]);
}

void Executor::executeDelete(const std::vector<std::string> &args)
{
    if (args.size() < 3)
    {
        std::cout << "DELETE FROM <table> WHERE <column> <value>\n";
        return;
    }
    db.deleteFrom(args[0], args[1], args[2]);
}

void Executor::executeSelect(const std::vector<std::string> &args)
{
    if (args.size() < 3)
    {
        std::cout << "SELECT <table> <column> <value>\n";
        return;
    }
    std::cout << db.select(args[0], args[1], args[2]) << std::endl;
}
