#include <iostream>
#include "../include/storage_engine/storage_engine.hpp"  // We only need to include the StorageEngine header

using namespace rdbms;
using namespace std;

int main() {
    // --- Initial Greetings ---
    cout << "---------------------------------------------\n";
    cout << "Welcome to the Custom RDBMS Simulation!\n";
    cout << "---------------------------------------------\n";
    
    // --- Initialize Storage Engine ---
    cout << "\nInitializing the Storage Engine for the 'students' database...\n";
    StorageEngine engine("students");  // Initialize StorageEngine for the table 'students'

    // --- Inserting Records into the Database ---
    cout << "\nInserting records into the 'students' database:\n";
    engine.insert(12, "Twelve");    // Insert record with key 12
    engine.insert(10, "Ten");       // Insert record with key 10
    engine.insert(5, "Five");       // Insert record with key 5
    engine.insert(6, "Six");        // Insert record with key 6
    engine.insert(7, "Seven");      // Insert record with key 7
    engine.insert(17, "Seventeen"); // Insert record with key 17
    engine.insert(20, "Twenty");    // Insert record with key 20
    engine.insert(30, "Thirty");    // Insert record with key 30

    // --- Display Current Storage ---  
    cout << "\nDatabase Storage after insertions (BufferPool & FileManager working):\n";
    engine.printStorage();  // Prints the current state of the storage (BufferPool and index)

    // --- Display the BufferPool's LRU Cache ---
    cout << "\nBufferPool LRU Cache (Most recently used pages shown first):\n";
    // This is already handled by printStorage(), so no need for a separate call to printLRU
    // engine.printLRU(); // This is not necessary anymore
    
    // --- Searching for Records ---
    cout << "\nSearching for records in the database using B+ Tree index:\n";
    cout << "Search for key 12: " << engine.search(12) << endl;   // Should return "Twelve"
    cout << "Search for key 21: " << engine.search(21) << endl;   // Should return "Key not found"

    // --- Flushing All Pages to Disk ---
    cout << "\nFlushing all pages from memory to disk...\n";
    engine.flushAll();  // Writes all dirty pages back to disk, ensuring data is persistent on disk
    
    // --- Display Storage After Flushing ---
    cout << "\nDisplaying database storage after flushing (Data written back to disk):\n";
    engine.printStorage();  // Displays final storage status after flushing to disk

    // --- End of the Demonstration ---
    cout << "\n=== END OF DEMONSTRATION ===\n";
    cout << "---------------------------------------------\n";
    
    return 0;
}