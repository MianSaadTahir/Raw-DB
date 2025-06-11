#include "../include/schema/table.hpp"
#include <iostream>

int main()
{
    std::cout << "=====================\n";
    std::cout << "TESTING TABLE SCHEMA\n";
    std::cout << "=====================\n";

    Table users("Users");

    users.addColumn("id", DataType::INT);
    users.addColumn("name", DataType::STRING);
    users.addColumn("balance", DataType::FLOAT);
    users.addColumn("is_active", DataType::BOOL);

    std::cout << "\n--- Table Schema ---\n";
    users.showSchema();

    std::cout << "\n--- Inserting Valid Rows ---\n";
    users.insertRow({Value(1), Value("Alice"), Value(1500.50f), Value(true)});
    users.insertRow({Value(2), Value("Bob"), Value(899.99f), Value(false)});

    std::cout << "\n--- Inserting Invalid Row (should fail) ---\n";
    users.insertRow({Value(3), Value("Charlie")});

    std::cout << "\n--- Displaying Rows ---\n";
    users.showAllRows();

    std::cout << "\nAll tests passed.\n";
    return 0;
}
