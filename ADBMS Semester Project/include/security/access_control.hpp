#ifndef ACCESS_CONTROL_HPP
#define ACCESS_CONTROL_HPP

#include <string>
#include <unordered_map>

namespace rdbms
{

    enum class Role
    {
        ADMIN,
        USER,
        GUEST
    };

    class User
    {
    public:
        std::string username;
        std::string password;
        Role role;

        User() : username(""), password(""), role(Role::GUEST) {} // ✅ Default constructor

        User(const std::string &username, const std::string &password, Role role);

        bool checkPassword(const std::string &pwd) const;
    };

    class AccessControl
    {
    private:
        std::unordered_map<std::string, User> users;

    public:
        AccessControl();

        bool addUser(const std::string &username, const std::string &password, Role role);
        bool authenticate(const std::string &username, const std::string &password) const;
        Role getUserRole(const std::string &username) const;
    };

}

#endif // ACCESS_CONTROL_HPP
