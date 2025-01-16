#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Product.h"
#include "Cart.h"
#include <vector>
using namespace std;

class Customer : public User {
private:
    Cart cart;
public:
    Customer(const string& username, const string& password) : User(username, password, false) {}

    void addToCart(const vector<Product>& products);
    void removeFromCart(vector<Product>& products);
    void updateCart(const vector<Product>& products);
    void completeOrder(vector<Product>& products, const string& fileName);
    void viewCart() const;
    void viewOrderHistory() const;
    void displayMenu(vector<Product>& products, const string& fileName);
};

#endif