#include "../include/database/database.hpp"
#include <iostream>
#include <cassert>

void testInsertAndSelect()
{
    Database db;
    db.insert("key1", "value1");
    db.insert("key2", "value2");

    assert(db.select("Default", "key1", "value1") == "value1");
    assert(db.select("Default", "key2", "value2") == "value2");
    assert(db.select("Default", "key3", "value3") == "Not found.");

    std::cout << "testInsertAndSelect passed.\n";
}

void testUpdate()
{
    Database db;
    db.insert("name", "Alice");
    bool updated = db.update("Default", "name", "Bob", "name", "Alice", "=");
    assert(updated);
    assert(db.select("Default", "name", "Bob") == "Bob");

    std::cout << "testUpdate passed.\n";
}

void testDelete()
{
    Database db;
    db.insert("temp", "delete_me");
    bool deleted = db.deleteFrom("Default", "temp", "delete_me");
    assert(deleted);
    assert(db.select("Default", "temp", "delete_me") == "Not found.");

    std::cout << "testDelete passed.\n";
}

void testFlushAndShow()
{
    Database db;
    db.insert("a", "1");
    db.insert("b", "2");
    db.flushDatabase();
    assert(db.select("Default", "a", "1") == "Not found.");
    std::cout << "testFlushAndShow passed.\n";
}

void testJoinGroupByOrder()
{
    Database db;
    db.insert("c", "3");
    db.insert("d", "4");

    db.join("c", "d"); // Just prints
    db.groupBy("c");   // Just prints
    db.order("c");     // Should print keys in order

    std::cout << "testJoinGroupByOrder passed.\n";
}

void testMatchLimitDistinctIndex()
{
    Database db;
    db.insert("fruit", "apple");
    db.insert("fruit2", "banana");
    db.match("apple");
    db.limit(1);
    db.createIndex("fruit");
    db.distinct();

    std::cout << "testMatchLimitDistinctIndex passed.\n";
}

int main()
{
    testInsertAndSelect();
    testUpdate();
    testDelete();
    testFlushAndShow();
    testJoinGroupByOrder();
    testMatchLimitDistinctIndex();

    std::cout << "All database tests passed.\n";
    return 0;
}
