#include "../include/database/database.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

Database::Database() : databaseActive(false) {}

Database::~Database()
{
    cout << "Database " << databaseName << " destroyed.\n";
}

void Database::createDatabase(const string &name)
{
    databaseName = name;
    tables.clear();
    databaseActive = true;
    cout << "Database " << name << " created and set as active.\n";
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

bool Database::update(const std::string &tableName,
                      const std::string &targetColumn,
                      const std::string &newValue,
                      const std::string &conditionColumn,
                      const std::string &conditionValue,
                      const std::string &operatorStr)
{
    auto it = tables.find(tableName);
    if (it == tables.end())
    {
        std::cout << "Table <" << tableName << "> not found.\n";
        return false;
    }

    Table &table = it->second;
    int targetColIndex = -1;
    int condColIndex = -1;
    std::string condColType;

    for (size_t i = 0; i < table.columns.size(); ++i)
    {
        if (table.columns[i].first == targetColumn)
            targetColIndex = static_cast<int>(i);
        if (table.columns[i].first == conditionColumn)
        {
            condColIndex = static_cast<int>(i);
            condColType = table.columns[i].second;
        }
    }

    if (targetColIndex == -1 || condColIndex == -1)
    {
        std::cout << "Invalid column(s).\n";
        return false;
    }

    bool updated = false;

    for (auto &row : table.rows)
    {
        std::string cell = row[condColIndex];
        bool match = false;

        if (condColType == "INT" || condColType == "BOOL")
        {
            int lhs = std::atoi(cell.c_str());
            int rhs = std::atoi(conditionValue.c_str());

            if (operatorStr == "=")
                match = lhs == rhs;
            else if (operatorStr == "!=")
                match = lhs != rhs;
            else if (operatorStr == "<")
                match = lhs < rhs;
            else if (operatorStr == ">")
                match = lhs > rhs;
            else if (operatorStr == "<=")
                match = lhs <= rhs;
            else if (operatorStr == ">=")
                match = lhs >= rhs;
        }
        else if (condColType == "FLOAT")
        {
            float lhs = std::atof(cell.c_str());
            float rhs = std::atof(conditionValue.c_str());

            if (operatorStr == "=")
                match = lhs == rhs;
            else if (operatorStr == "!=")
                match = lhs != rhs;
            else if (operatorStr == "<")
                match = lhs < rhs;
            else if (operatorStr == ">")
                match = lhs > rhs;
            else if (operatorStr == "<=")
                match = lhs <= rhs;
            else if (operatorStr == ">=")
                match = lhs >= rhs;
        }
        else // STRING
        {
            if (operatorStr == "=")
                match = cell == conditionValue;
            else if (operatorStr == "!=")
                match = cell != conditionValue;
            // optionally implement lexicographic <, > if needed
        }

        if (match)
        {
            row[targetColIndex] = newValue;
            std::cout << "Updated row: ";
            for (const auto &val : row)
                std::cout << val << " ";
            std::cout << "\n";
            updated = true;
        }
    }

    return updated;
}

bool Database::deleteFrom(const std::string &tableName,
                          const std::string &conditionColumn,
                          const std::string &conditionValue)
{
    auto it = tables.find(tableName);
    if (it == tables.end())
    {
        std::cout << "Table <" << tableName << "> not found.\n";
        return false;
    }

    Table &table = it->second;
    int condColIndex = -1;
    std::string condColType;

    for (size_t i = 0; i < table.columns.size(); ++i)
    {
        if (table.columns[i].first == conditionColumn)
        {
            condColIndex = static_cast<int>(i);
            condColType = table.columns[i].second;
            break;
        }
    }

    if (condColIndex == -1)
    {
        std::cout << "Column <" << conditionColumn << "> not found in table <" << tableName << ">.\n";
        return false;
    }

    // Extract operator and actual value (supports =, !=, <, >, <=, >=)
    std::string op = "=";
    std::string actualValue = conditionValue;

    if (conditionValue.size() >= 2)
    {
        if (conditionValue.substr(0, 2) == ">=")
        {
            op = ">=";
            actualValue = conditionValue.substr(2);
        }
        else if (conditionValue.substr(0, 2) == "<=")
        {
            op = "<=";
            actualValue = conditionValue.substr(2);
        }
        else if (conditionValue.substr(0, 2) == "!=")
        {
            op = "!=";
            actualValue = conditionValue.substr(2);
        }
        else if (conditionValue[0] == '<')
        {
            op = "<";
            actualValue = conditionValue.substr(1);
        }
        else if (conditionValue[0] == '>')
        {
            op = ">";
            actualValue = conditionValue.substr(1);
        }
        else if (conditionValue[0] == '=')
        {
            op = "=";
            actualValue = conditionValue.substr(1);
        }
    }

    bool deleted = false;

    for (auto it = table.rows.begin(); it != table.rows.end();)
    {
        std::string cell = it->at(condColIndex);
        bool match = false;

        std::string type = condColType;
        for (size_t i = 0; i < type.size(); ++i)
            type[i] = std::toupper(type[i]);

        if (type == "INT" || type == "BOOL")
        {
            int lhs = std::atoi(cell.c_str());
            int rhs = std::atoi(actualValue.c_str());

            if (op == "=")
                match = lhs == rhs;
            else if (op == "!=")
                match = lhs != rhs;
            else if (op == "<")
                match = lhs < rhs;
            else if (op == ">")
                match = lhs > rhs;
            else if (op == "<=")
                match = lhs <= rhs;
            else if (op == ">=")
                match = lhs >= rhs;
        }
        else if (type == "FLOAT")
        {
            float lhs = std::atof(cell.c_str());
            float rhs = std::atof(actualValue.c_str());

            if (op == "=")
                match = lhs == rhs;
            else if (op == "!=")
                match = lhs != rhs;
            else if (op == "<")
                match = lhs < rhs;
            else if (op == ">")
                match = lhs > rhs;
            else if (op == "<=")
                match = lhs <= rhs;
            else if (op == ">=")
                match = lhs >= rhs;
        }
        else // STRING
        {
            if (op == "=")
                match = cell == actualValue;
            else if (op == "!=")
                match = cell != actualValue;
            // Optionally handle lexicographic comparison for strings
        }

        if (match)
        {
            std::cout << "Deleted row: ";
            for (const auto &val : *it)
                std::cout << val << " ";
            std::cout << "\n";

            it = table.rows.erase(it);
            deleted = true;
        }
        else
        {
            ++it;
        }
    }

    return deleted;
}

// Add key-value pair to the database
void Database::addKeyValuePair(const std::string &key, const std::string &value)
{
    data[key] = value;
    std::cout << "Inserted: " << key << " -> " << value << std::endl;
}

// Retrieve key-value pair from the database
std::string Database::retrieveKeyValuePair(const std::string &key, const std::string &value)
{
    if (data.find(key) != data.end() && data[key] == value)
    {
        return "Found: " + key + " -> " + value;
    }
    return "Error: Value not found.";
}

// Remove key-value pair from the database
void Database::removeKeyValuePair(const std::string &key, const std::string &value)
{
    if (data.find(key) != data.end() && data[key] == value)
    {
        data.erase(key);
        std::cout << "Removed: " << key << " -> " << value << std::endl;
    }
    else
    {
        std::cout << "Error: No such key-value pair to remove." << std::endl;
    }
}


void Database::createTable(const std::string &table, const std::vector<std::pair<std::string, std::string>> &columns)
{
    if (!databaseActive)
    {
        std::cout << "Error: No active database. Please create a database first using CREATE_DATABASE.\n";
        return;
    }

    if (tables.find(table) != tables.end())
    {
        std::cout << "Error: Table " << table << " already exists.\n";
        return;
    }

    // Check for at least one column with PRIMARY_KEY or PK
    bool primaryKeyFound = false;
    for (const auto &col : columns)
    {
        if (col.second == "PRIMARY_KEY") // Correctly check for PRIMARY_KEY
        {
            primaryKeyFound = true;
            break;
        }
    }

    if (!primaryKeyFound)
    {
        std::cout << "Error: Table must have at least one column with PRIMARY_KEY.\n";
        return;
    }

    // Store the table definition
    Table newTable;
    newTable.columns = columns;
    tables[table] = newTable;

    std::cout << "Table " << table << " created.\n";
}

bool Database::insertIntoTable(const std::string &table, const std::vector<std::string> &values)
{
    auto it = tables.find(table);
    if (it == tables.end())
    {
        std::cout << "Table " << table << " not found.\n";
        return false;
    }

    std::vector<std::pair<std::string, std::string>> &columns = it->second.columns;
    std::vector<std::vector<std::string>> &rows = it->second.rows;

    size_t colCount = columns.size();

    if (values.size() % colCount != 0)
    {
        std::cout << "Error: Number of values does not match number of columns in table.\n";
        return false;
    }

    bool inserted = false;

    // Find the index of the primary key column
    int primaryKeyIndex = -1;
    for (size_t i = 0; i < columns.size(); ++i)
    {
        if (columns[i].second == "PRIMARY_KEY")
        {
            primaryKeyIndex = i;
            break;
        }
    }

    if (primaryKeyIndex == -1)
    {
        std::cout << "Error: Table does not have a primary key column.\n";
        return false;
    }

    for (size_t i = 0; i < values.size(); i += colCount)
    {
        std::vector<std::string> row;
        bool validRow = true;

        // Validate each value against its column type
        for (size_t j = 0; j < colCount; ++j)
        {
            std::string type = columns[j].second;
            std::string val = values[i + j];

            // Convert type to uppercase for consistency
            for (size_t k = 0; k < type.length(); ++k)
                type[k] = toupper(type[k]);

            // Skip validation for the primary key column
            if (j == primaryKeyIndex)
            {
                row.push_back(val);
                continue;
            }

            // Validate other types
            if (type == "INT")
            {
                for (size_t c = 0; c < val.size(); ++c)
                {
                    if (!isdigit(val[c]) && !(c == 0 && val[c] == '-'))
                    {
                        std::cout << "Type error: '" << val << "' is not a valid INT.\n";
                        validRow = false;
                        break;
                    }
                }
            }
            // Validate FLOAT
            else if (type == "FLOAT")
            {
                bool dotSeen = false;
                for (size_t c = 0; c < val.size(); ++c)
                {
                    if (val[c] == '.')
                    {
                        if (dotSeen)
                        {
                            std::cout << "Type error: '" << val << "' is not a valid FLOAT.\n";
                            validRow = false;
                            break;
                        }
                        dotSeen = true;
                    }
                    else if (!isdigit(val[c]) && !(c == 0 && val[c] == '-'))
                    {
                        std::cout << "Type error: '" << val << "' is not a valid FLOAT.\n";
                        validRow = false;
                        break;
                    }
                }
            }
            // Validate BOOL
            else if (type == "BOOL")
            {
                if (val != "true" && val != "false" && val != "1" && val != "0")
                {
                    std::cout << "Type error: '" << val << "' is not a valid BOOL (true/false/1/0).\n";
                    validRow = false;
                    break;
                }
            }
            // STRING is always valid
            else if (type != "STRING")
            {
                std::cout << "Unknown data type: " << type << "\n";
                validRow = false;
                break;
            }

            row.push_back(val);
        }

        if (!validRow)
            return false;

        // Check for primary key uniqueness
        std::string primaryKeyValue = row[primaryKeyIndex];
        for (const auto &existingRow : rows)
        {
            if (existingRow[primaryKeyIndex] == primaryKeyValue)
            {
                std::cout << "Duplicate primary key value: '" << primaryKeyValue << "'.\n";
                return false; // Primary key value must be unique
            }
        }

        // Check for other duplicates
        bool isDuplicate = false;
        for (const auto &existingRow : rows)
        {
            if (existingRow == row)
            {
                isDuplicate = true;
                break;
            }
        }

        if (isDuplicate)
        {
            std::cout << "Duplicate row not inserted: ";
            for (size_t j = 0; j < row.size(); ++j)
                std::cout << row[j] << (j + 1 == row.size() ? "" : ", ");
            std::cout << "\n";
        }
        else
        {
            rows.push_back(row);
            inserted = true;
        }
    }

    if (inserted)
    {
        std::cout << "Inserted into table: " << table << std::endl;
        return true;
    }
    else
    {
        std::cout << "No new unique rows inserted.\n";
        return false;
    }
}

std::string Database::selectFromTable(const std::string &columnsStr, const std::string &tableName)
{
    std::stringstream output;

    auto it = tables.find(tableName);
    if (it == tables.end())
    {
        output << "Table <" << tableName << "> not found.\n";
        return output.str();
    }

    const auto &table = it->second;
    const auto &tableColumns = table.columns;
    const auto &rows = table.rows;

    // Handle WHERE clause
    std::string actualColumns = columnsStr;
    std::string whereCol, op, val;

    size_t wherePos = columnsStr.find("WHERE");
    if (wherePos != std::string::npos)
    {
        actualColumns = columnsStr.substr(0, wherePos);
        std::string condition = columnsStr.substr(wherePos + 5); // skip "WHERE"

        std::vector<std::string> operators = {">=", "<=", "!=", "=", "<", ">"};
        bool opFound = false;

        for (const std::string &candidateOp : operators)
        {
            size_t pos = condition.find(candidateOp);
            if (pos != std::string::npos)
            {
                whereCol = condition.substr(0, pos);
                op = candidateOp;
                val = condition.substr(pos + candidateOp.length());
                opFound = true;
                break;
            }
        }

        if (!opFound || whereCol.empty() || op.empty() || val.empty())
        {
            output << "Invalid WHERE clause.\n";
            return output.str();
        }

        // Trim whitespaces
        whereCol.erase(remove_if(whereCol.begin(), whereCol.end(), ::isspace), whereCol.end());
        val.erase(0, val.find_first_not_of(" \t\r\n"));
        val.erase(val.find_last_not_of(" \t\r\n") + 1);
    }

    // Parse selected columns
    std::vector<std::string> selectedColumns;
    if (actualColumns.find('*') != std::string::npos)
    {
        for (const auto &col : tableColumns)
        {
            selectedColumns.push_back(col.first);
        }
    }
    else
    {
        std::stringstream ss(actualColumns);
        std::string token;
        while (std::getline(ss, token, ','))
        {
            // Trim token
            token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
            if (!token.empty())
                selectedColumns.push_back(token);
        }
    }

    // Resolve selected column indexes
    std::vector<int> colIndexes;
    for (const auto &colName : selectedColumns)
    {
        bool found = false;
        for (size_t i = 0; i < tableColumns.size(); ++i)
        {
            if (tableColumns[i].first == colName)
            {
                colIndexes.push_back(i);
                found = true;
                break;
            }
        }
        if (!found)
        {
            output << "Column '" << colName << "' does not exist in table <" << tableName << ">.\n";
            return output.str();
        }
    }

    // Resolve WHERE column index
    int whereColIndex = -1;
    std::string whereType;
    if (!whereCol.empty())
    {
        for (size_t i = 0; i < tableColumns.size(); ++i)
        {
            if (tableColumns[i].first == whereCol)
            {
                whereColIndex = static_cast<int>(i);
                whereType = tableColumns[i].second;
                break;
            }
        }
        if (whereColIndex == -1)
        {
            output << "WHERE column '" << whereCol << "' does not exist in table <" << tableName << ">.\n";
            return output.str();
        }
    }

    // Header
    output << "========== Selected columns from table: " << tableName << " ==========\n";
    for (size_t i = 0; i < colIndexes.size(); ++i)
    {
        output << tableColumns[colIndexes[i]].first;
        if (i < colIndexes.size() - 1)
            output << " | ";
    }
    output << "\n----------------------------------------\n";

    // Rows
    for (const auto &row : rows)
    {
        bool match = true;
        if (whereColIndex != -1)
        {
            std::string cell = row[whereColIndex];
            std::string valType = whereType;
            for (size_t k = 0; k < valType.length(); ++k)
                valType[k] = toupper(valType[k]);

            if (valType == "INT")
            {
                int lhs = std::atoi(cell.c_str());
                int rhs = std::atoi(val.c_str());
                if (op == "=")
                    match = lhs == rhs;
                else if (op == "!=")
                    match = lhs != rhs;
                else if (op == "<")
                    match = lhs < rhs;
                else if (op == ">")
                    match = lhs > rhs;
                else if (op == "<=")
                    match = lhs <= rhs;
                else if (op == ">=")
                    match = lhs >= rhs;
            }
            else if (valType == "FLOAT")
            {
                float lhs = std::atof(cell.c_str());
                float rhs = std::atof(val.c_str());
                if (op == "=")
                    match = lhs == rhs;
                else if (op == "!=")
                    match = lhs != rhs;
                else if (op == "<")
                    match = lhs < rhs;
                else if (op == ">")
                    match = lhs > rhs;
                else if (op == "<=")
                    match = lhs <= rhs;
                else if (op == ">=")
                    match = lhs >= rhs;
            }
            else if (valType == "STRING" || valType == "BOOL")
            {
                if (op == "=")
                    match = cell == val;
                else if (op == "!=")
                    match = cell != val;
                else
                    match = false;
            }
            else
            {
                match = false;
            }
        }

        if (match)
        {
            for (size_t i = 0; i < colIndexes.size(); ++i)
            {
                output << row[colIndexes[i]];
                if (i < colIndexes.size() - 1)
                    output << " | ";
            }
            output << "\n";
        }
    }

    output << "========================================\n";
    return output.str();
}

bool Database::join(const std::string &table1Name, const std::string &table2Name,
                    const std::string &column1, const std::string &column2)
{
    if (tables.find(table1Name) == tables.end() || tables.find(table2Name) == tables.end())
    {
        std::cout << "One or both tables not found.\n";
        return false;
    }

    Table &table1 = tables[table1Name];
    Table &table2 = tables[table2Name];

    int col1Index = -1, col2Index = -1;

    for (size_t i = 0; i < table1.columns.size(); ++i)
        if (table1.columns[i].first == column1)
            col1Index = static_cast<int>(i);

    for (size_t i = 0; i < table2.columns.size(); ++i)
        if (table2.columns[i].first == column2)
            col2Index = static_cast<int>(i);

    if (col1Index == -1 || col2Index == -1)
    {
        std::cout << "Join columns not found.\n";
        return false;
    }

    Table result;

    // Add all columns from table1
    for (const auto &col : table1.columns)
        result.columns.push_back(col);

    // Add all columns from table2
    for (const auto &col : table2.columns)
        result.columns.push_back(col);

    // Nested loop join
    for (const auto &row1 : table1.rows)
    {
        for (const auto &row2 : table2.rows)
        {
            if (row1[col1Index] == row2[col2Index])
            {
                std::vector<std::string> joinedRow = row1;
                joinedRow.insert(joinedRow.end(), row2.begin(), row2.end());
                result.rows.push_back(joinedRow);
            }
        }
    }

    std::string joinedTableName = table1Name + "_" + table2Name + "_join";
    tables[joinedTableName] = result;

    std::cout << "Joined: " << table1Name << " with " << table2Name
              << " => " << joinedTableName << "\n";

    return true;
}

bool Database::groupBy(const std::string &tableName, const std::string &columnName)
{
    auto it = tables.find(tableName);
    if (it == tables.end())
    {
        std::cout << "Table <" << tableName << "> not found.\n";
        return false;
    }

    Table &original = it->second;
    int colIndex = -1;

    for (size_t i = 0; i < original.columns.size(); ++i)
    {
        if (original.columns[i].first == columnName)
        {
            colIndex = static_cast<int>(i);
            break;
        }
    }

    if (colIndex == -1)
    {
        std::cout << "Column <" << columnName << "> not found.\n";
        return false;
    }

    std::map<std::string, std::vector<std::vector<std::string>>> groups;

    for (const auto &row : original.rows)
    {
        if (colIndex < static_cast<int>(row.size()))
        {
            std::string key = row[colIndex];
            groups[key].push_back(row);
        }
    }

    // Create a new table with name: <tableName>_grouped_by_<columnName>
    std::string newTableName = tableName + "_grouped_by_" + columnName;

    Table grouped;
    grouped.columns = original.columns;

    for (const auto &entry : groups)
    {
        for (const auto &row : entry.second)
        {
            grouped.rows.push_back(row);
        }
    }

    tables[newTableName] = grouped;

    std::cout << "Grouped by: " << columnName << " -> Created table <" << newTableName << ">\n";
    return true;
}

void Database::order(const std::string &tableName, const std::string &columnName, bool ascending)
{
    if (tables.find(tableName) == tables.end())
    {
        std::cout << "Error: Table '" << tableName << "' not found.\n";
        return;
    }

    Table &table = tables[tableName];

    // Find index of the column
    int colIndex = -1;
    for (size_t i = 0; i < table.columns.size(); ++i)
    {
        if (table.columns[i].first == columnName)
        {
            colIndex = static_cast<int>(i);
            break;
        }
    }

    if (colIndex == -1)
    {
        std::cout << "Error: Column '" << columnName << "' not found in table '" << tableName << "'.\n";
        return;
    }

    // Sort table.rows in-place
    std::sort(table.rows.begin(), table.rows.end(), [colIndex, ascending](const std::vector<std::string> &a, const std::vector<std::string> &b)
              {
        if (ascending)
            return a[colIndex] < b[colIndex];
        else
            return a[colIndex] > b[colIndex]; });

    std::cout << "Table '" << tableName << "' ordered by column '" << columnName << "' in " << (ascending ? "ASC" : "DESC") << " order.\n";
}

void Database::match(const std::string &tableName, const std::string &columnName, const std::string &pattern)
{
    auto it = tables.find(tableName);
    if (it == tables.end())
    {
        std::cout << "Error: Table '" << tableName << "' not found.\n";
        return;
    }

    const Table &table = it->second;

    // Find index of the target column
    int columnIndex = -1;
    for (size_t i = 0; i < table.columns.size(); ++i)
    {
        if (table.columns[i].first == columnName)
        {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex == -1)
    {
        std::cout << "Error: Column '" << columnName << "' not found in table '" << tableName << "'.\n";
        return;
    }

    bool matchFound = false;
    for (const auto &row : table.rows)
    {
        if (row[columnIndex].find(pattern) != std::string::npos)
        {
            matchFound = true;
            // Print entire row
            for (size_t i = 0; i < row.size(); ++i)
            {
                std::cout << row[i];
                if (i != row.size() - 1)
                    std::cout << " | ";
            }
            std::cout << "\n";
        }
    }

    if (!matchFound)
    {
        std::cout << "No match found for pattern \"" << pattern << "\" in column '" << columnName << "'.\n";
    }
}

void Database::limit(const std::string &tableName, int limit)
{
    auto it = tables.find(tableName);
    if (it == tables.end())
    {
        std::cout << "Error: Table '" << tableName << "' not found.\n";
        return;
    }

    const Table &table = it->second;

    int count = 0;
    for (const auto &row : table.rows)
    {
        if (count >= limit)
            break;

        for (size_t i = 0; i < row.size(); ++i)
        {
            std::cout << row[i];
            if (i != row.size() - 1)
                std::cout << " | ";
        }
        std::cout << "\n";
        ++count;
    }

    if (count == 0)
    {
        std::cout << "No rows to display from table '" << tableName << "'.\n";
    }
}

void Database::distinct(const std::string &tableName, const std::string &columnName)
{
    auto it = tables.find(tableName);
    if (it == tables.end())
    {
        std::cout << "Error: Table '" << tableName << "' not found.\n";
        return;
    }

    const Table &table = it->second;
    const auto &columns = table.columns;

    // Find the index of the target column
    int columnIndex = -1;
    for (size_t i = 0; i < columns.size(); ++i)
    {
        if (columns[i].first == columnName)
        {
            columnIndex = static_cast<int>(i);
            break;
        }
    }

    if (columnIndex == -1)
    {
        std::cout << "Error: Column '" << columnName << "' not found in table '" << tableName << "'.\n";
        return;
    }

    std::unordered_set<std::string> seen;
    for (const auto &row : table.rows)
    {
        const std::string &value = row[columnIndex];
        if (seen.insert(value).second) // if value was not already present
        {
            for (size_t i = 0; i < row.size(); ++i)
            {
                std::cout << row[i];
                if (i != row.size() - 1)
                    std::cout << " | ";
            }
            std::cout << "\n";
        }
    }
}

void Database::createIndex(const std::string &tableName, const std::string &columnName)
{
    // Step 1: Check if the table exists
    auto tableIt = tables.find(tableName);
    if (tableIt == tables.end())
    {
        std::cout << "Error: Table '" << tableName << "' does not exist.\n";
        return;
    }

    // Step 2: Check if the column exists in the table
    const Table &table = tableIt->second;
    int columnIndex = -1;
    for (size_t i = 0; i < table.columns.size(); ++i)
    {
        if (table.columns[i].first == columnName) // Check column name
        {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex == -1)
    {
        std::cout << "Error: Column '" << columnName << "' does not exist in table '" << tableName << "'.\n";
        return;
    }

    // Step 3: Create the index for the specified column
    // We will use a map to store the index for the column
    // The key will be the column's value, and the value will be a list of rows that have this value in the specified column

    for (const auto &row : table.rows)
    {
        const std::string &columnValue = row[columnIndex]; // Get the value from the specified column
        indexes[tableName][columnName][columnValue].push_back(row);
    }

    std::cout << "Created index for column '" << columnName << "' in table '" << tableName << "'.\n";
}
