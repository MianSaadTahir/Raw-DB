#include "../include/database/database.hpp"
#include "../include/query_processor/executor.hpp"
#include <iostream>

using namespace std;

// Simulate real command execution
void simulateCommands(Executor& executor) {
    cout << "\n===== [TEST] Executor Command Simulation =====\n";

    cout << "\n> CREATE_DATABASE TestExecDB\n";
    executor.executeCommand("CREATE_DATABASE TestExecDB");

    cout << "\n> PUT key1 val1\n";
    executor.executeCommand("PUT key1 val1");

    cout << "\n> GET key1\n";
    executor.executeCommand("GET key1");

    cout << "\n> PUT key1 val2 (simulated update)\n";
    executor.executeCommand("PUT key1 val2");

    cout << "\n> GET key1 (after update)\n";
    executor.executeCommand("GET key1");

    cout << "\n> REMOVE key1\n";
    executor.executeCommand("REMOVE key1");

    cout << "\n> GET key1 (should be missing)\n";
    executor.executeCommand("GET key1");

    cout << "\n> PUT key2 val2\n";
    executor.executeCommand("PUT key2 val2");

    cout << "\n> PUT key3 val3\n";
    executor.executeCommand("PUT key3 val3");

    cout << "\n> ORDER dummy\n";
    executor.executeCommand("ORDER dummy");

    cout << "\n> LIMIT 1\n";
    executor.executeCommand("LIMIT 1");

    cout << "\n> MATCH val\n";
    executor.executeCommand("MATCH val");

    cout << "\n> CREATE_INDEX key2\n";
    executor.executeCommand("CREATE_INDEX key2");

    cout << "\n> DISTINCT\n";
    executor.executeCommand("DISTINCT");

    cout << "\n> FLUSH\n";
    executor.executeCommand("FLUSH");

    cout << "\n> SHOW (should be empty)\n";
    executor.executeCommand("SHOW");
}

int main() {
    cout << "=========================================\n";
    cout << "         RUNNING EXECUTOR TESTS          \n";
    cout << "=========================================\n";

    Database db;
    Executor executor(db);
    simulateCommands(executor);

    cout << "\nAll executor commands executed successfully!\n";
    return 0;
}
