#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <map>

class Database
{
public:
    Database();
    ~Database();

    std::map<std::string, std::string> data;

    void createDatabase(const std::string &name);
    void alterDatabase(const std::string &name);
    void showDatabase() const;
    void flushDatabase();
    void showAllData() const;

    bool insert(const std::string &key, const std::string &value);
    bool update(const std::string &table, const std::string &column, const std::string &newValue,
                const std::string &conditionColumn, const std::string &conditionValue, const std::string &operatorStr);
    bool deleteFrom(const std::string &table, const std::string &conditionColumn, const std::string &conditionValue);
    std::string select(const std::string &table, const std::string &column, const std::string &conditionValue) const;

    void createTable(const std::string &table, const std::vector<std::pair<std::string, std::string>> &columns);
    bool insertIntoTable(const std::string &table, const std::vector<std::string> &values);
    std::string selectFromTable(const std::string &columns, const std::string &table);

    bool join(const std::string &table1Name, const std::string &table2Name, const std::string &column1, const std::string &column2);
    bool groupBy(const std::string &tableName, const std::string &columnName);
    void order(const std::string &tableName, const std::string &columnName, bool ascending);
    void match(const std::string &tableName, const std::string &columnName, const std::string &pattern);
    void limit(const std::string &tableName, int limit);
    void distinct(const std::string &tableName, const std::string &columnName);
    void createIndex(const std::string &tableName, const std::string &columnName);

    void addKeyValuePair(const std::string &key, const std::string &value);
    std::string retrieveKeyValuePair(const std::string &key, const std::string &value);
    void removeKeyValuePair(const std::string &key, const std::string &value);

private:
    struct Table
    {
        std::vector<std::pair<std::string, std::string>> columns;
        std::vector<std::vector<std::string>> rows;
    };

    bool databaseActive;
    std::string databaseName;
    std::unordered_map<std::string, Table> tables;
    std::unordered_set<std::string> index;
    std::vector<std::string> orderedKeys;
    std::map<std::string, std::map<std::string, std::map<std::string, std::vector<std::vector<std::string>>>>> indexes;
};

#endif // DATABASE_HPP
