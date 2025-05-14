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
    else if (command == "SHOWDATABASE")
        db.showDatabase();
    else if (command == "SHOWTABLES")
        db.showAllData();
    else if (command == "FLUSH")
        executeFlush();
    else if (command == "EXIT")
        executeExit();
    else if (command == "CREATE_DATABASE")
        executeCreateDatabase(args);
    else if (command == "ALTER_DATABASE")
        executeAlterDatabase(args);
    else if (command == "CREATE_TABLE")
        executeCreateTable(args);
    else if (command == "INSERT")
        executeInsert(args);
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
        std::cout << "Usage: PUT <key> <value>\n";
        return;
    }
    db.insert(args[0], args[1]);
}

void Executor::executeGet(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: GET <column> <value>\n";
        return;
    }
    std::cout << db.select("Default", args[0], args[1]) << std::endl;
}

void Executor::executeRemove(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: REMOVE <column> <value>\n";
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
        std::cout << "Usage: CREATE_DATABASE <name>\n";
        return;
    }
    db.createDatabase(args[0]);
}

void Executor::executeAlterDatabase(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "Usage: ALTER_DATABASE <name>\n";
        return;
    }
    db.alterDatabase(args[0]);
}

void Executor::executeCreateTable(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: CREATE_TABLE <table_name> <column1:type1> <column2:type2> ...\n";
        return;
    }

    std::string tableName = args[0];
    std::vector<std::pair<std::string, std::string>> columns;

    for (size_t i = 1; i < args.size(); ++i)
    {
        size_t pos = args[i].find(':');
        if (pos == std::string::npos)
        {
            std::cout << "Invalid column definition: " << args[i] << "\n";
            return;
        }
        std::string colName = args[i].substr(0, pos);
        std::string colType = args[i].substr(pos + 1);
        columns.push_back(std::make_pair(colName, colType));
    }

    db.createTable(tableName, columns);
}

void Executor::executeInsert(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: INSERT <table> <val1> <val2> ...\n";
        return;
    }

    std::string tableName = args[0];
    std::vector<std::string> values(args.begin() + 1, args.end());

    if (!db.insertIntoTable(tableName, values))
    {
        std::cout << "Table <" << tableName << "> not found.\n";
    }
}

void Executor::executeJoin(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: JOIN <table1> <table2>\n";
        return;
    }
    db.join(args[0], args[1]);
}

void Executor::executeGroupBy(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: GROUP_BY <table> <column>\n";
        return;
    }
    db.groupBy(args[1]);
}

void Executor::executeOrder(const std::vector<std::string> &args)
{
    if (args.size() < 3)
    {
        std::cout << "Usage: ORDER <table> <column> ASC|DESC\n";
        return;
    }
    db.order(args[1]);
}

void Executor::executeMatch(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: MATCH <pattern>\n";
        return;
    }
    db.match(args[1]);
}

void Executor::executeLimit(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: LIMIT <count>\n";
        return;
    }
    db.limit(std::atoi(args[1].c_str()));
}

void Executor::executeDistinct()
{
    db.distinct();
}

void Executor::executeCreateIndex(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: CREATE_INDEX <key>\n";
        return;
    }
    db.createIndex(args[1]);
}

void Executor::executeUpdate(const std::vector<std::string> &args)
{
    if (args.size() < 6)
    {
        std::cout << "Usage: UPDATE <table> SET <column> = <value> WHERE <column> = <value>\n";
        return;
    }

    db.update(args[0], args[2], args[4], args[6], args[8], "=");
}

void Executor::executeDelete(const std::vector<std::string> &args)
{
    if (args.size() < 3)
    {
        std::cout << "Usage: DELETE <table> WHERE <column> = <value>\n";
        return;
    }

    db.deleteFrom(args[0], args[1], args[2]);
}

void Executor::executeSelect(const std::vector<std::string> &args)
{
    if (args.size() < 3)
    {
        std::cout << "Usage: SELECT <column> FROM <table>\n";
        return;
    }

    std::string tableName = args[2];
    std::string column = args[0];

    std::string result = db.selectFromTable(column, tableName);
    if (result.empty())
    {
        std::cout << "Table <" << tableName << "> not found.\n";
    }
    else
    {
        std::cout << result << std::endl;
    }
}
