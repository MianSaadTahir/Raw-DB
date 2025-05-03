#include "../include/database/database.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

Database::Database() : databaseName("Default") {}

Database::~Database() {
    cout << "Database " << databaseName << " is being destroyed.\n";
}

void Database::createDatabase(const string& name) {
    databaseName = name;
    data.clear();
    cout << "Database " << name << " created successfully.\n";
}

void Database::alterDatabase(const string& name) {
    databaseName = name;
    cout << "Database altered: " << name << ".\n";
}

void Database::showDatabase() const {
    cout << "Current database: " << databaseName << "\n";
}

void Database::flushDatabase() {
    data.clear();
    cout << "All data has been flushed from database " << databaseName << ".\n";
}

bool Database::insert(const string& key, const string& value) {
    data[key] = value;
    cout << "Inserted/Updated: " << key << " -> " << value << "\n";
    return true;
}

bool Database::update(const string& key, const string& value) {
    auto it = data.find(key);
    if (it != data.end()) {
        data[key] = value;
        cout << "Updated: " << key << " -> " << value << "\n";
        return true;
    }
    cout << "Error: Key " << key << " not found.\n";
    return false;
}

bool Database::remove(const string& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        data.erase(it);
        cout << "Removed: " << key << "\n";
        return true;
    }
    cout << "Error: Key " << key << " not found.\n";
    return false;
}

string Database::get(const string& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    return "Error: Key not found.";
}

void Database::showAllData() const {
    if (data.empty()) {
        cout << "No data to display.\n";
        return;
    }
    for (auto it = data.begin(); it != data.end(); ++it) {
        cout << it->first << " -> " << it->second << "\n";
    }
}

void Database::join(const string& key1, const string& key2) {
    cout << "Joining " << key1 << " and " << key2 << "\n";
}

void Database::groupBy(const string& key) {
    cout << "Grouping by: " << key << "\n";
}

void Database::order(const string& key) {
    cout << "Ordering by: " << key << "\n";
    orderedKeys.clear();
    for (auto it = data.begin(); it != data.end(); ++it) {
        orderedKeys.push_back(it->first);
    }
    sort(orderedKeys.begin(), orderedKeys.end());
    for (auto it = orderedKeys.begin(); it != orderedKeys.end(); ++it) {
        cout << *it << " -> " << data[*it] << "\n";
    }
}

void Database::match(const string& pattern) {
    cout << "Matching pattern: " << pattern << "\n";
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it->first.find(pattern) != string::npos || it->second.find(pattern) != string::npos) {
            cout << it->first << " -> " << it->second << "\n";
        }
    }
}

void Database::limit(int limit) {
    int count = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (count++ >= limit) break;
        cout << it->first << " -> " << it->second << "\n";
    }
}

void Database::distinct() {
    cout << "Distinct entries:\n";
    for (auto it = index.begin(); it != index.end(); ++it) {
        cout << *it << " -> " << data[*it] << "\n";
    }
}

void Database::createIndex(const string& key) {
    index.insert(key);
    cout << "Index created for key: " << key << "\n";
}
