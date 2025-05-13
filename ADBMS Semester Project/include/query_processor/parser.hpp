#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

enum class CommandType
{
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
    CREATE_INDEX,
    UPDATE // Added for UPDATE functionality
};

struct ParsedCommand
{
    CommandType type;
    std::vector<std::string> args;
};

class Parser
{
public:
    static ParsedCommand parseFullCommand(const std::string &input);

private:
    static std::vector<std::string> tokenize(const std::string &input);
    static std::string toLower(const std::string &str);
};

#endif
