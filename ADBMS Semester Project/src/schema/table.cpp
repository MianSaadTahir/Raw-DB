#include "../include/schema/table.hpp"

// ---------------- Value methods ------------------

Value::Value() : type(DataType::STRING), stringValue("") {}

Value::Value(int v) : type(DataType::INT), intValue(v) {}

Value::Value(float v) : type(DataType::FLOAT), floatValue(v) {}

Value::Value(bool v) : type(DataType::BOOL), boolValue(v) {}

Value::Value(const std::string &v) : type(DataType::STRING), stringValue(v) {}

Value::Value(const char *v) : type(DataType::STRING), stringValue(v) {}

bool Value::operator==(const Value &other) const
{
    if (type != other.type)
        return false;
    switch (type)
    {
    case DataType::INT:
        return intValue == other.intValue;
    case DataType::FLOAT:
        return floatValue == other.floatValue;
    case DataType::BOOL:
        return boolValue == other.boolValue;
    case DataType::STRING:
        return stringValue == other.stringValue;
    default:
        return false;
    }
}

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

Table::Table(const std::string &name) : tableName(name), primaryKeyName("") {}

void Table::addColumn(const std::string &name, DataType type, bool isPrimaryKey)
{
    columns.emplace_back(name, type, isPrimaryKey);
    if (isPrimaryKey)
    {
        primaryKeyName = name;
    }
    std::cout << "Column added: " << name << (isPrimaryKey ? " [PRIMARY KEY]" : "") << "\n";
}

bool Table::insertRow(const std::vector<Value> &values)
{
    if (values.size() != columns.size())
    {
        std::cerr << "Error: Value count does not match column count.\n";
        return false;
    }

    // Check primary key uniqueness
    if (!primaryKeyName.empty())
    {
        size_t pkIndex = 0;
        for (; pkIndex < columns.size(); ++pkIndex)
        {
            if (columns[pkIndex].name == primaryKeyName)
                break;
        }

        if (pkIndex >= columns.size())
        {
            std::cerr << "Internal error: Primary key column not found.\n";
            return false;
        }

        const Value &pkVal = values[pkIndex];
        for (const Row &existingRow : rows)
        {
            if (existingRow.at(primaryKeyName) == pkVal)
            {
                std::cerr << "Error: Duplicate value for PRIMARY KEY '" << primaryKeyName << "'.\n";
                return false;
            }
        }
    }

    Row row;
    for (size_t i = 0; i < columns.size(); ++i)
    {
        row[columns[i].name] = values[i];
    }
    rows.push_back(row);
    std::cout << "Row inserted.\n";
    return true;
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
        if (col.isPrimaryKey)
        {
            std::cout << " [PRIMARY KEY]";
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

const std::string &Table::getName() const
{
    return tableName;
}

const std::vector<Column> &Table::getColumns() const
{
    return columns;
}

const std::vector<Row> &Table::getRows() const
{
    return rows;
}

// --- NEW: Primary Key Support ---

void Table::setPrimaryKey(const std::string &colName)
{
    primaryKeyName = colName;
}

const std::string &Table::getPrimaryKey() const
{
    return primaryKeyName;
}
