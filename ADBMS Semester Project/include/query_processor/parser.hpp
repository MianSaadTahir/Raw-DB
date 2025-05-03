#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

// Enum for all command types
enum class CommandType {
    INVALID,
    PUT,
    GET,
    REMOVE,
    SHOW,
    FLUSH,
    EXIT,
    CREATE_DATABASE,
    ALTER_DATABASE,
    JOIN,
    GROUP_BY,
    ORDER,
    MATCH,
    LIMIT,
    DISTINCT,
    CREATE_INDEX
};

// Structure to hold parsed command and its arguments
struct ParsedCommand {
    CommandType type;
    std::vector<std::string> args;
};

class Parser {
public:
    // Main function to parse full command line and return ParsedCommand
    static ParsedCommand parseFullCommand(const std::string& input);

private:
    // Helper function to tokenize the input string
    static std::vector<std::string> tokenize(const std::string& input);

    // Helper function to convert string to lowercase
    static std::string toLower(const std::string& str);
};

#endif // PARSER_HPP
