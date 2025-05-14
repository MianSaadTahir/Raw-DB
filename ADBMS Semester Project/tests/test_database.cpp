#include "../include/database/database.hpp"
#include <iostream>
#include <cassert>

void testKeyValueOperations()
{
    Database db;

    std::cout << "Running key-value tests..." << std::endl;

    // Test 1: Add key-value pair
    db.addKeyValuePair("name", "Alice");
    assert(db.data["name"] == "Alice");

    // Test 2: Retrieve key-value pair (should match)
    std::string result = db.retrieveKeyValuePair("name", "Alice");
    assert(result == "Found: name -> Alice");

    // Test 3: Retrieve key-value pair (should not match)
    result = db.retrieveKeyValuePair("name", "Bob");
    assert(result == "Error: Value not found.");

    // Test 4: Remove key-value pair (should succeed)
    db.removeKeyValuePair("name", "Alice");
    assert(db.data.find("name") == db.data.end());

    // Test 5: Remove again (should fail gracefully)
    db.removeKeyValuePair("name", "Alice");

    std::cout << "All key-value tests passed!" << std::endl;
}

int main()
{
    testKeyValueOperations();
    return 0;
}
