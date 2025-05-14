#include "../include/query_processor/executor.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

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
    bool hasPrimaryKey = false;

    // Parse columns and check for PRIMARY_KEY or PK
    for (size_t i = 1; i < args.size(); ++i)
    {
        size_t pos = args[i].find(':');
        if (pos == std::string::npos || pos == 0 || pos == args[i].length() - 1)
        {
            std::cout << "Invalid column definition: " << args[i] << "\n";
            return;
        }

        std::string colName = args[i].substr(0, pos);
        std::string colType = args[i].substr(pos + 1);

        // Convert type to uppercase for consistency
        for (size_t j = 0; j < colType.length(); ++j)
            colType[j] = toupper(colType[j]);

        // If the column is a PK or PRIMARY_KEY, handle it as a primary key
        if (colType == "PK" || colType == "PRIMARY_KEY")
        {
            colType = "PRIMARY_KEY"; // Treat it as PRIMARY_KEY in the database
            columns.push_back(std::make_pair(colName, colType));
            hasPrimaryKey = true; // Mark primary key presence
        }
        else if (colType == "INT" || colType == "STRING" || colType == "FLOAT" || colType == "BOOL")
        {
            columns.push_back(std::make_pair(colName, colType)); // Regular column
        }
        else
        {
            std::cout << "Unsupported data type: " << colType << "\n";
            return;
        }
    }

    // Ensure at least one primary key column is present
    if (!hasPrimaryKey)
    {
        std::cout << "Error: Table must have at least one primary key column.\n";
        return;
    }

    // Create the table with the column definitions
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

    // Call insertIntoTable, which already handles primary key checks
    if (!db.insertIntoTable(tableName, values))
    {
        std::cout << "Error: Insertion failed. Table <" << tableName << "> may not exist or primary key constraints not met.\n";
    }
    else
    {
        std::cout << "Inserted values into table <" << tableName << ">.\n";
    }
}

void Executor::executeJoin(const std::vector<std::string> &args)
{
    if (args.size() != 6 || args[2] != "ON" || args[4] != "=")
    {
        std::cout << "Usage: JOIN <table1> <table2> ON <column1> = <column2>\n";
        return;
    }

    std::string table1 = args[0];
    std::string table2 = args[1];
    std::string column1 = args[3];
    std::string column2 = args[5];

    if (!db.join(table1, table2, column1, column2))
    {
        std::cout << "Join failed.\n";
    }
}

void Executor::executeGroupBy(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cout << "Usage: GROUP_BY <table> <column>\n";
        return;
    }

    std::string tableName = args[0];
    std::string columnName = args[1];

    if (!db.groupBy(tableName, columnName))
    {
        std::cout << "GROUP_BY failed. Table or column not found.\n";
    }
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

#include <algorithm> // Add this at the top of executor.cpp

void Executor::executeUpdate(const std::vector<std::string> &args)
{
    if (args.size() < 8 || args[1] != "SET")
    {
        std::cout << "Usage: UPDATE <table> SET <column> = <value> WHERE <column> <op> <value>\n";
        return;
    }

    std::string tableName = args[0];

    // Parse SET clause
    std::string setColumn = args[2];
    if (args[3] != "=")
    {
        std::cout << "Expected '=' in SET clause.\n";
        return;
    }

    std::string setValue = args[4];
    if (!setValue.empty() && setValue.front() == '"' && setValue.back() == '"')
        setValue = setValue.substr(1, setValue.size() - 2);

    // Parse WHERE clause
    if (args[5] != "WHERE")
    {
        std::cout << "Expected WHERE clause after SET.\n";
        return;
    }

    if (args.size() < 9)
    {
        std::cout << "Incomplete WHERE clause.\n";
        return;
    }

    std::string conditionColumn = args[6];
    std::string op = args[7];
    std::string conditionValue = args[8];

    // Remove quotes if present
    if (!conditionValue.empty() && conditionValue.front() == '"' && conditionValue.back() == '"')
        conditionValue = conditionValue.substr(1, conditionValue.size() - 2);

    // Validate operator
    const std::string validOpsArr[] = {"=", "!=", "<", ">", "<=", ">="};
    bool isValidOp = false;
    for (size_t i = 0; i < sizeof(validOpsArr) / sizeof(validOpsArr[0]); ++i)
    {
        if (validOpsArr[i] == op)
        {
            isValidOp = true;
            break;
        }
    }

    if (!isValidOp)
    {
        std::cout << "Invalid operator in WHERE clause.\n";
        return;
    }

    // Call Database::update
    if (!db.update(tableName, setColumn, setValue, conditionColumn, conditionValue, op))
    {
        std::cout << "Update failed or no rows matched condition.\n";
    }
}

void Executor::executeDelete(const std::vector<std::string> &args)
{
    if (args.empty())
    {
        std::cout << "Usage: DELETE <table> [WHERE <column> <op> <value>]\n";
        return;
    }

    std::string tableName = args[0];

    if (args.size() == 1)
    {
        std::cout << "WHERE clause is required to delete specific rows.\n";
        return;
    }

    if (args.size() < 5 || args[1] != "WHERE")
    {
        std::cout << "Usage: DELETE <table> WHERE <column> <op> <value>\n";
        return;
    }

    std::string column = args[2];
    std::string op = args[3];
    std::string value = args[4];

    // Remove quotes from string values
    if (!value.empty() && value.front() == '"' && value.back() == '"')
    {
        value = value.substr(1, value.size() - 2);
    }

    // Validate operator
    const std::string validOps[] = {"=", "!=", "<", ">", "<=", ">="};
    bool isValidOp = false;
    for (size_t i = 0; i < sizeof(validOps) / sizeof(validOps[0]); ++i)
    {
        if (validOps[i] == op)
        {
            isValidOp = true;
            break;
        }
    }

    if (!isValidOp)
    {
        std::cout << "Invalid operator in WHERE clause. Supported operators: = != < > <= >=\n";
        return;
    }

    // Encode the operator into the value string (e.g., >=100)
    std::string conditionValue = op + value;

    if (!db.deleteFrom(tableName, column, conditionValue))
    {
        std::cout << "No rows deleted.\n";
    }
}

void Executor::executeSelect(const std::vector<std::string> &args)
{
    if (args.size() < 3 || args[1] != "FROM")
    {
        std::cout << "Usage: SELECT <column1,column2,...|*> FROM <table> [WHERE <column><op><value>]\n";
        return;
    }

    std::string columnList = args[0]; // e.g., "name,salary" or "*"
    std::string tableName = args[2];

    std::string fullColumnExpr = columnList;

    // Reconstruct WHERE clause if present
    if (args.size() > 3)
    {
        std::stringstream ss;
        for (size_t i = 3; i < args.size(); ++i)
        {
            ss << args[i];
            if (i < args.size() - 1)
                ss << " ";
        }

        fullColumnExpr += " " + ss.str(); // Append everything after "FROM" as part of full expression
    }

    std::string result = db.selectFromTable(fullColumnExpr, tableName);

    if (result.empty())
    {
        std::cout << "Table <" << tableName << "> not found or invalid column(s).\n";
    }
    else
    {
        std::cout << result;
    }
}
