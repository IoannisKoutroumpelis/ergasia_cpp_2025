#ifndef USER_H
#define USER_H

#include "Product.h"
#include <string>
#include <vector>
using namespace std;

class User {
protected:
    string username;
    string password;
    bool isAdmin; // true for Admin, false for Customer

public:
    User(const string& username, const string& password, bool isAdmin)
        : username(username), password(password), isAdmin(isAdmin) {}

    string getUsername() const;
    string getPassword() const;
    bool getIsAdmin() const;

    virtual ~User() {}
};

#endif