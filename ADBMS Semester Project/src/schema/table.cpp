#include "../include/schema/table.hpp"

// ---------------- Value methods ------------------

Value::Value() : type(DataType::STRING), stringValue("") {}

Value::Value(int v) : type(DataType::INT), intValue(v) {}

Value::Value(float v) : type(DataType::FLOAT), floatValue(v) {}

Value::Value(bool v) : type(DataType::BOOL), boolValue(v) {}

Value::Value(const std::string &v) : type(DataType::STRING), stringValue(v) {}

Value::Value(const char *v) : type(DataType::STRING), stringValue(v) {}

std::string Value::toString() const
{
    switch (type)
    {
    case DataType::INT:
        return std::to_string(intValue);
    case DataType::FLOAT:
        return std::to_string(floatValue);
    case DataType::BOOL:
        return boolValue ? "true" : "false";
    case DataType::STRING:
        return stringValue;
    default:
        return "";
    }
}

// ---------------- Table methods ------------------

Table::Table(const std::string &name) : tableName(name) {}

void Table::addColumn(const std::string &name, DataType type)
{
    columns.emplace_back(name, type);
    std::cout << "Column added: " << name << "\n";
}

void Table::insertRow(const std::vector<Value> &values)
{
    if (values.size() != columns.size())
    {
        std::cerr << "Error: Value count does not match column count.\n";
        return;
    }
    Row row;
    for (size_t i = 0; i < columns.size(); ++i)
    {
        row[columns[i].name] = values[i];
    }
    rows.push_back(row);
    std::cout << "Row inserted.\n";
}

void Table::showSchema() const
{
    std::cout << "\n--- Table Schema ---\n";
    std::cout << "Table: " << tableName << "\nSchema:\n";
    for (const auto &col : columns)
    {
        std::cout << "- " << col.name << ": ";
        switch (col.type)
        {
        case DataType::INT:
            std::cout << "INT";
            break;
        case DataType::STRING:
            std::cout << "STRING";
            break;
        case DataType::FLOAT:
            std::cout << "FLOAT";
            break;
        case DataType::BOOL:
            std::cout << "BOOL";
            break;
        }
        std::cout << "\n";
    }
}

void Table::showAllRows() const
{
    std::cout << "\n--- Rows in Table: " << tableName << " ---\n";
    for (const auto &row : rows)
    {
        for (const auto &col : columns)
        {
            std::cout << col.name << ": " << row.at(col.name).toString() << " | ";
        }
        std::cout << "\n";
    }
}
