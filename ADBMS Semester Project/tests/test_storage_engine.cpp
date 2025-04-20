#include "../include/storage_engine/storage_engine.hpp" 
#include <iostream>

using namespace rdbms;
using namespace std;

int main() {
    StorageEngine engine("students");

    engine.insert(12, "Twelve");
    engine.insert(10, "Ten");
    engine.insert(5, "Five");
    engine.insert(6, "Six");
    engine.insert(7, "Seven");
    engine.insert(17, "Seventeen");
    engine.insert(20, "Twenty");
    engine.insert(30, "Thirty");

    engine.printStorage();

    cout << "Search 12: " << engine.search(12) << "\n";
    cout << "Search 21: " << engine.search(21) << "\n";

    return 0;
}
