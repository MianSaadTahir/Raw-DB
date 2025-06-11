#include "../include/security/access_control.hpp"
#include <iostream>

using namespace rdbms;

void testAccessControl()
{
    AccessControl ac;

    std::cout << "[TEST] Adding users...\n";
    ac.addUser("admin", "adminpass", Role::ADMIN);
    ac.addUser("user1", "user1pass", Role::USER);

    std::cout << "[TEST] Authenticating users...\n";
    std::cout << "Admin correct password: " << (ac.authenticate("admin", "adminpass") ? "PASS" : "FAIL") << "\n";
    std::cout << "Admin wrong password: " << (ac.authenticate("admin", "wrong") ? "PASS" : "FAIL") << "\n";

    std::cout << "[TEST] Checking user roles...\n";
    Role r = ac.getUserRole("admin");
    std::cout << "Role for admin: " << (r == Role::ADMIN ? "ADMIN" : "NOT ADMIN") << "\n";

    r = ac.getUserRole("unknown");
    std::cout << "Role for unknown: " << (r == Role::GUEST ? "GUEST" : "NOT GUEST") << "\n";
}

int main()
{
    testAccessControl();
    return 0;
}
