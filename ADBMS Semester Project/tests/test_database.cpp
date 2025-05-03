#include "../include/database/database.hpp"
#include <iostream>
#include <cassert>

using namespace std;

// Test basic CRUD operations (Create, Read, Update, Delete)
void testBasicCRUD() {
    cout << "\n===== [TEST] Basic CRUD Operations =====\n";

    Database db;
    db.createDatabase("TestDB");

    cout << "-> Inserting 'key1' with value 'value1'\n";
    assert(db.insert("key1", "value1") == true);

    string val = db.get("key1");
    cout << "-> Retrieved 'key1': " << val << "\n";
    assert(val == "value1");

    cout << "-> Updating 'key1' to value 'value2'\n";
    assert(db.update("key1", "value2") == true);

    val = db.get("key1");
    cout << "-> Retrieved 'key1' after update: " << val << "\n";
    assert(val == "value2");

    cout << "-> Removing 'key1'\n";
    assert(db.remove("key1") == true);

    val = db.get("key1");
    cout << "-> Retrieving 'key1' after removal: " << val << "\n";
    assert(val == "Error: Key not found.");
}

// Test flushing the database and displaying data
void testFlushAndShow() {
    cout << "\n===== [TEST] Flush & Show All Data =====\n";

    Database db;
    db.insert("user1", "Alice");
    db.insert("user2", "Bob");

    cout << "-> Current database contents:\n";
    db.showAllData();

    cout << "-> Flushing all data from database...\n";
    db.flushDatabase();

    string val = db.get("user1");
    cout << "-> Retrieving 'user1' after flush: " << val << "\n";
    assert(val == "Error: Key not found.");
}

// Test advanced features: ordering, matching, limiting, indexing
void testExtras() {
    cout << "\n===== [TEST] Advanced Functionalities =====\n";

    Database db;
    db.insert("alpha", "100");
    db.insert("beta", "200");
    db.insert("gamma", "300");
    db.insert("delta", "100");

    cout << "\n-> Ordering entries by key:\n";
    db.order("any");

    cout << "\n-> Matching keys/values containing 'a':\n";
    db.match("a");

    cout << "\n-> Limiting results to 2 entries:\n";
    db.limit(2);

    cout << "\n-> Creating index on key 'alpha':\n";
    db.createIndex("alpha");

    cout << "\n-> Displaying distinct values:\n";
    db.distinct();
}

int main() {
    cout << "=========================================\n";
    cout << "         RUNNING DATABASE TESTS          \n";
    cout << "=========================================\n";

    testBasicCRUD();
    testFlushAndShow();
    testExtras();

    cout << "\nAll database tests passed successfully!\n";
    return 0;
}
