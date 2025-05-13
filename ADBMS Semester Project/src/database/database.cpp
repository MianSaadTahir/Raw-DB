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
    data.clear();
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
    data.clear();
    cout << "Database flushed.\n";
}

void Database::showAllData() const
{
    for (auto it = data.begin(); it != data.end(); ++it)
        cout << it->first << " -> " << it->second << endl;
}

bool Database::insert(const string &key, const string &value)
{
    data[key] = value;
    return true;
}

bool Database::update(const string &, const string &column, const string &newValue,
                      const string &conditionColumn, const string &conditionValue, const string &operatorStr)
{
    for (auto &entry : data)
    {
        if (entry.first == conditionColumn)
        {
            if ((operatorStr == "=" && entry.second == conditionValue) ||
                (operatorStr == "!=" && entry.second != conditionValue))
            {
                entry.second = newValue;
                cout << "Updated: " << entry.first << " -> " << newValue << endl;
                return true;
            }
        }
    }
    return false;
}

bool Database::deleteFrom(const string &, const string &column, const string &value)
{
    bool found = false;
    for (auto it = data.begin(); it != data.end();)
    {
        if (it->first == column && it->second == value)
        {
            cout << "Deleted: " << it->first << " -> " << it->second << endl;
            it = data.erase(it);
            found = true;
        }
        else
        {
            ++it;
        }
    }
    return found;
}

string Database::select(const string &, const string &column, const string &value) const
{
    for (auto it = data.begin(); it != data.end(); ++it)
        if (it->first == column && it->second == value)
            return it->second;
    return "Not found.";
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
    for (auto it = data.begin(); it != data.end(); ++it)
        orderedKeys.push_back(it->first);
    sort(orderedKeys.begin(), orderedKeys.end());
    for (size_t i = 0; i < orderedKeys.size(); ++i)
        cout << orderedKeys[i] << " -> " << data[orderedKeys[i]] << endl;
}

void Database::match(const string &pattern)
{
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        if (it->first.find(pattern) != string::npos || it->second.find(pattern) != string::npos)
            cout << it->first << " -> " << it->second << endl;
    }
}

void Database::limit(int limit)
{
    int count = 0;
    for (auto it = data.begin(); it != data.end() && count < limit; ++it, ++count)
        cout << it->first << " -> " << it->second << endl;
}

void Database::distinct()
{
    for (auto it = index.begin(); it != index.end(); ++it)
        cout << *it << " -> " << data[*it] << endl;
}

void Database::createIndex(const string &key)
{
    index.insert(key);
    cout << "Created index for: " << key << endl;
}
