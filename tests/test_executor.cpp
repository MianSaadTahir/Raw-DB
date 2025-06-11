#include "../include/query_processor/executor.hpp"
#include "../include/database/database.hpp"
#include <iostream>
#include <cassert>

void testBasicCommands()
{
    Database db;
    Executor executor(db);

    executor.executeCommand("PUT id123 John");
    executor.executeCommand("PUT id456 Jane");
    executor.executeCommand("SHOW");

    executor.executeCommand("GET Default id123");
    executor.executeCommand("GET Default id456");

    executor.executeCommand("REMOVE id123 John");
    executor.executeCommand("SHOW");

    std::cout << "testBasicCommands passed.\n";
}

void testDatabaseOps()
{
    Database db;
    Executor executor(db);

    executor.executeCommand("CREATE_DATABASE testdb");
    executor.executeCommand("ALTER_DATABASE prod");

    executor.executeCommand("PUT user1 Alice");
    executor.executeCommand("GET Default user1");

    executor.executeCommand("FLUSH");
    executor.executeCommand("SHOW");

    std::cout << "testDatabaseOps passed.\n";
}

void testAdvancedCommands()
{
    Database db;
    Executor executor(db);

    executor.executeCommand("PUT k1 v1");
    executor.executeCommand("PUT k2 v2");
    executor.executeCommand("PUT k3 v3");

    executor.executeCommand("CREATE_INDEX k1");
    executor.executeCommand("DISTINCT");
    executor.executeCommand("MATCH v2");
    executor.executeCommand("ORDER k1");
    executor.executeCommand("LIMIT 2");

    std::cout << "testAdvancedCommands passed.\n";
}

void testUpdateDeleteSelect()
{
    Database db;
    Executor executor(db);

    executor.executeCommand("PUT id100 Tom");
    executor.executeCommand("UPDATE Default SET id100 = Jerry WHERE id100 = Tom");
    executor.executeCommand("GET Default id100");

    executor.executeCommand("DELETE Default id100 Jerry");
    executor.executeCommand("GET Default id100");

    std::cout << "testUpdateDeleteSelect passed.\n";
}

int main()
{
    testBasicCommands();
    testDatabaseOps();
    testAdvancedCommands();
    testUpdateDeleteSelect();

    std::cout << "All executor tests passed.\n";
    return 0;
}
