#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <unordered_set>

class Database
{
public:
    Database();
    ~Database();

    void createDatabase(const std::string &name);
    void alterDatabase(const std::string &name);
    void showDatabase() const;
    void flushDatabase();

    bool insert(const std::string &key, const std::string &value);
    bool update(const std::string &table, const std::string &column, const std::string &newValue,
                const std::string &conditionColumn, const std::string &conditionValue, const std::string &operatorStr);
    bool deleteFrom(const std::string &table, const std::string &conditionColumn, const std::string &conditionValue);
    std::string select(const std::string &table, const std::string &column, const std::string &conditionValue) const;

    void showAllData() const;

    void join(const std::string &key1, const std::string &key2);
    void groupBy(const std::string &key);
    void order(const std::string &key);
    void match(const std::string &pattern);
    void limit(int limit);
    void distinct();
    void createIndex(const std::string &key);

private:
    std::string databaseName;
    std::unordered_map<std::string, std::string> data;
    std::unordered_set<std::string> index;
    std::vector<std::string> orderedKeys;
};

#endif // DATABASE_HPP
