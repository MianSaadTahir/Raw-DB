#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <unordered_map>
#include <vector>
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
    void order(const std::string &key);
    void match(const std::string &pattern);
    void limit(int limit);
    void distinct();
    void createIndex(const std::string &key);

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
};

#endif // DATABASE_HPP
