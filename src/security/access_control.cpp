#include "../include/security/access_control.hpp"

namespace rdbms
{

    User::User(const std::string &username, const std::string &password, Role role)
        : username(username), password(password), role(role) {}

    bool User::checkPassword(const std::string &pwd) const
    {
        return password == pwd;
    }

    AccessControl::AccessControl() {}

    bool AccessControl::addUser(const std::string &username, const std::string &password, Role role)
    {
        if (users.find(username) != users.end())
        {
            return false; // User already exists
        }
        users[username] = User(username, password, role);
        return true;
    }

    bool AccessControl::authenticate(const std::string &username, const std::string &password) const
    {
        auto it = users.find(username);
        if (it == users.end())
        {
            return false;
        }
        return it->second.checkPassword(password);
    }

    Role AccessControl::getUserRole(const std::string &username) const
    {
        auto it = users.find(username);
        if (it != users.end())
        {
            return it->second.role;
        }
        return Role::GUEST; // default fallback
    }

}
