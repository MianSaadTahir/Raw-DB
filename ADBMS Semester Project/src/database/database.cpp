#include "../include/database/database.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Database::Database() : databaseName("Default") {}

Database::~Database()
{
    cout << "Database " << databaseName << " destroyed.\n";
}

void Database::createDatabase(const string &name)
{
    databaseName = name;
    tables.clear();
    cout << "Created database: " << name << endl;
}

void Database::alterDatabase(const string &name)
{
    databaseName = name;
    cout << "Altered to database: " << name << endl;
}

void Database::showDatabase() const
{
    cout << "Current database: " << databaseName << endl;
}

void Database::flushDatabase()
{
    tables.clear();
    cout << "Database flushed.\n";
}

void Database::showAllData() const
{
    for (const auto &table : tables)
    {
        const std::string &tableName = table.first;
        const Table &tbl = table.second;

        std::cout << "\n========== Table: " << tableName << " ==========\n";

        // Print column headers
        for (size_t i = 0; i < tbl.columns.size(); ++i)
        {
            std::cout << tbl.columns[i].first; // column name
            if (i != tbl.columns.size() - 1)
                std::cout << " | ";
        }
        std::cout << "\n";

        // Print a separator
        for (size_t i = 0; i < tbl.columns.size(); ++i)
        {
            std::cout << "-----------";
        }
        std::cout << "\n";

        // Print rows
        for (const auto &row : tbl.rows)
        {
            for (size_t i = 0; i < row.size(); ++i)
            {
                std::cout << row[i];
                if (i != row.size() - 1)
                    std::cout << " | ";
            }
            std::cout << "\n";
        }
        std::cout << "======================================\n";
    }
}

bool Database::insert(const string &key, const string &value)
{
    tables["default"].rows.push_back({key, value});
    return true;
}

bool Database::update(const string &, const string &column, const string &newValue,
                      const string &conditionColumn, const string &conditionValue, const string &operatorStr)
{
    for (auto &table : tables)
    {
        for (auto &row : table.second.rows)
        {
            if (row[0] == conditionColumn)
            {
                if ((operatorStr == "=" && row[1] == conditionValue) ||
                    (operatorStr == "!=" && row[1] != conditionValue))
                {
                    row[1] = newValue;
                    cout << "Updated: " << row[0] << " -> " << newValue << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Database::deleteFrom(const string &, const string &column, const string &value)
{
    bool found = false;
    for (auto &table : tables)
    {
        for (auto it = table.second.rows.begin(); it != table.second.rows.end();)
        {
            if (it->at(0) == column && it->at(1) == value)
            {
                cout << "Deleted: " << it->at(0) << " -> " << it->at(1) << endl;
                it = table.second.rows.erase(it);
                found = true;
            }
            else
            {
                ++it;
            }
        }
    }
    return found;
}

string Database::select(const string &, const string &column, const string &value) const
{
    for (const auto &table : tables)
    {
        for (const auto &row : table.second.rows)
        {
            if (row[0] == column && row[1] == value)
            {
                return row[1];
            }
        }
    }
    return "Not found.";
}

void Database::createTable(const string &table, const vector<pair<string, string>> &columns)
{
    Table newTable;
    newTable.columns = columns;
    tables[table] = newTable;
    cout << "Table " << table << " created." << endl;
}

bool Database::insertIntoTable(const std::string &table, const std::vector<std::string> &values)
{
    auto it = tables.find(table);
    if (it != tables.end())
    {
        // Find number of columns in the table
        size_t colCount = it->second.columns.size();

        // Ensure values are divisible by colCount for proper row creation
        if (values.size() % colCount != 0)
        {
            cout << "Error: Number of values does not match the number of columns in the table.\n";
            return false;
        }

        // Insert values row by row
        for (size_t i = 0; i < values.size(); i += colCount)
        {
            std::vector<std::string> row(values.begin() + i, values.begin() + i + colCount);
            it->second.rows.push_back(row); // Insert row into table
        }

        cout << "Inserted into table: " << table << endl;
        return true;
    }
    cout << "Table " << table << " not found.\n";
    return false;
}

string Database::selectFromTable(const string &columns, const string &table)
{
    auto it = tables.find(table);
    if (it != tables.end())
    {
        stringstream result;
        for (const auto &row : it->second.rows)
        {
            result << row[0] << " "; // Selects the first column by default, adjust based on columns
            result << endl;
        }
        return result.str();
    }
    return "";
}

void Database::join(const string &k1, const string &k2)
{
    cout << "Joined: " << k1 << " with " << k2 << endl;
}

void Database::groupBy(const string &key)
{
    cout << "Grouped by: " << key << endl;
}

void Database::order(const string &key)
{
    orderedKeys.clear();
    for (const auto &table : tables)
    {
        for (const auto &row : table.second.rows)
        {
            orderedKeys.push_back(row[0]);
        }
    }
    sort(orderedKeys.begin(), orderedKeys.end());
    for (size_t i = 0; i < orderedKeys.size(); ++i)
    {
        cout << orderedKeys[i] << " -> " << orderedKeys[i] << endl;
    }
}

void Database::match(const string &pattern)
{
    for (const auto &table : tables)
    {
        for (const auto &row : table.second.rows)
        {
            if (row[0].find(pattern) != string::npos || row[1].find(pattern) != string::npos)
            {
                cout << row[0] << " -> " << row[1] << endl;
            }
        }
    }
}

void Database::limit(int limit)
{
    int count = 0;
    for (const auto &table : tables)
    {
        for (const auto &row : table.second.rows)
        {
            if (count >= limit)
                return;
            cout << row[0] << " -> " << row[1] << endl;
            ++count;
        }
    }
}

void Database::distinct()
{
    unordered_set<string> unique;
    for (const auto &table : tables)
    {
        for (const auto &row : table.second.rows)
        {
            unique.insert(row[0]);
        }
    }
    for (const auto &item : unique)
    {
        cout << item << endl;
    }
}

void Database::createIndex(const string &key)
{
    index.insert(key);
    cout << "Created index for: " << key << endl;
}
