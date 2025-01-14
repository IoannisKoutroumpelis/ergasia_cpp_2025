#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Product.h"
#include <vector>
using namespace std;

class Admin : public User {
public:
    Admin(const string& username, const string& password) : User(username, password, true) {}

    void displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName);
    void addProduct(vector<Product>& products, const vector<string>& categories, const string& fileName);
    void editProduct(vector<Product>& products, const string& fileName);
    void searchProducts(const vector<Product>& products, const vector<string>& categories) const;
    void viewStatistics(const vector<Product>& products) const;
};

#endif