#ifndef TABLE_HPP
#define TABLE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

enum class DataType
{
    INT,
    STRING,
    FLOAT,
    BOOL
};

class Value
{
public:
    DataType type;
    int intValue;
    std::string stringValue;
    float floatValue;
    bool boolValue;

    Value(); // Default constructor

    Value(int v);
    Value(float v);
    Value(bool v);
    Value(const std::string &v);
    Value(const char *v); // Support const char*

    bool operator==(const Value &other) const;
    std::string toString() const;
};

// Hash function for Value to use in unordered_map/set if needed
namespace std
{
    template <>
    struct hash<Value>
    {
        size_t operator()(const Value &v) const;
    };
}

struct Column
{
    std::string name;
    DataType type;
    bool isPrimaryKey;

    Column(const std::string &n, DataType t, bool isPK = false)
        : name(n), type(t), isPrimaryKey(isPK) {}
};

typedef std::unordered_map<std::string, Value> Row;

class Table
{
private:
    std::string tableName;
    std::vector<Column> columns;
    std::vector<Row> rows;
    std::string primaryKeyName; // NEW: Primary key column name

    std::vector<std::vector<Value>> selectFilteredRows(const std::string &columnName, const Value &matchValue) const;

public:
    Table(const std::string &name);

    void addColumn(const std::string &name, DataType type, bool isPrimaryKey = false);

    bool insertRow(const std::vector<Value> &values); // Returns false on PK violation

    void showSchema() const;
    void showAllRows() const;

    const std::string &getName() const;
    const std::vector<Column> &getColumns() const;
    const std::vector<Row> &getRows() const;

    void setPrimaryKey(const std::string &colName); // NEW: Set PK column
    const std::string &getPrimaryKey() const;       // NEW: Get PK column
};

#endif
