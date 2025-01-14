#ifndef ESHOP_H
#define ESHOP_H

#include "Admin.h"
#include "Customer.h"
#include "Product.h"
#include <vector>
#include <string>
using namespace std;

class Eshop {
private:
    vector<Product> products;      // Λίστα προϊόντων
    vector<string> categories;     // Λίστα κατηγοριών
    vector<User*> users;           // Λίστα χρηστών (Admin/Customer)

    string categoriesFile;         // Path για το αρχείο κατηγοριών
    string productsFile;           // Path για το αρχείο προϊόντων
    string usersFile;              // Path για το αρχείο χρηστών

    void loadCategories();
    void loadProducts();
    void loadUsers();

    void updateProductsFile();
    void updateUsersFile();

public:
    Eshop(const string& categoriesFile, const string& productsFile, const string& usersFile);
    ~Eshop();

    void login();
    void registerUser();
};

#endif