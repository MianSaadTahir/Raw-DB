#include <iostream>
#include "../include/storage_engine/storage_engine.hpp" // Include only the StorageEngine header

using namespace rdbms;
using namespace std;

int main()
{
    // ============================================================
    //                  CUSTOM RELATIONAL DATABASE SYSTEM
    // ============================================================

    cout << "============================================================\n";
    cout << "         WELCOME TO CUSTOM RELATIONAL DATABASE SYSTEM        \n";
    cout << "============================================================\n";

    // Step 1: Initialize the Storage Engine
    cout << "\n[Step 1] Initializing the Storage Engine for table: 'students'...\n";
    StorageEngine engine("students");

    /*
        The StorageEngine internally initializes:
        - FileManager: Handles file operations for reading/writing pages
        - BufferPool: Manages limited memory cache with LRU replacement
        - B+ Tree Index: Enables efficient indexing and searching by key
    */

    // Step 2: Insert Records
    cout << "\n[Step 2] Inserting records into the 'students' table...\n";

    engine.insert(12, "Twelve");
    engine.insert(10, "Ten");
    engine.insert(5, "Five");
    engine.insert(6, "Six");
    engine.insert(7, "Seven");
    engine.insert(17, "Seventeen");
    engine.insert(20, "Twenty");
    engine.insert(30, "Thirty");

    /*
        Each insert operation:
        - Adds the key-value pair to the B+ Tree index
        - Writes the data to the appropriate page in the BufferPool
        - Evicts the least recently used page if memory is full
    */

    // Step 3: Print Current Database State
    cout << "\n[Step 3] Displaying database state (storage and indexing info):\n";
    engine.printStorage();

    /*
        Shows:
        - B+ Tree structure: how data is indexed
        - BufferPool contents: which pages are currently in memory
        - LRU Order: recently used vs older pages
    */

    // Step 4: Search Records
    cout << "\n[Step 4] Searching records using B+ Tree index:\n";

    string result1 = engine.search(12);
    string result2 = engine.search(21); // This key was never inserted

    cout << "Search for key 12: " << result1 << endl;
    cout << "Search for key 21: " << result2 << endl;

    /*
        The search uses the B+ Tree to locate the page,
        then retrieves the value from that page.
        If page is not in memory, it loads it from disk.
    */

    // Step 5: Flush All Pages to Disk
    cout << "\n[Step 5] Flushing all in-memory pages to disk...\n";
    engine.flushAll();

    /*
        Flush ensures:
        - All dirty pages in BufferPool are written to disk
        - No data is lost if program terminates
    */

    // Step 6: Final Database State
    cout << "\n[Step 6] Database state after flushing to disk:\n";
    engine.printStorage();

    /*
        After flushing, memory and disk are consistent.
        Pages on disk reflect all the inserted/updated values.
    */

    // End of Demonstration
    cout << "\n============================================================\n";
    cout << "                  END OF DATABASE DEMO                      \n";
    cout << "============================================================\n";

    return 0;
}
