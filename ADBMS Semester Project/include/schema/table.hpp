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

    std::string toString() const;
};

struct Column
{
    std::string name;
    DataType type;
    Column(const std::string &n, DataType t) : name(n), type(t) {}
};

typedef std::unordered_map<std::string, Value> Row;

class Table
{
private:
    std::string tableName;
    std::vector<Column> columns;
    std::vector<Row> rows;

public:
    Table(const std::string &name);
    void addColumn(const std::string &name, DataType type);
    void insertRow(const std::vector<Value> &values);
    void showSchema() const;
    void showAllRows() const;
};

#endif
