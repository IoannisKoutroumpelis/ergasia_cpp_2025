#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
using namespace std;

class Product {
private:
    string title;
    string description;
    string category;
    string subCategory;
    double price;
    string unit;
    int quantity;

public:
    Product(const string& title = "", const string& description = "",
            const string& category = "", const string& subCategory = "",
            double price = 0.0, const string& unit = "", int quantity = 0.0);

    // Getters
    string getTitle() const;
    string getDescription() const;
    string getCategory() const;
    string getSubCategory() const;
    double getPrice() const;
    string getUnit() const;
    int getQuantity() const;

    // Setters
    void setTitle(const string& newTitle);
    void setDescription(const string& newDescription);
    void setCategory(const string& newCategory);
    void setSubCategory(const string& newSubCategory);
    void setPrice(double newPrice);
    void setQuantity(int newQuantity);

    // Overloaded operators
    friend ostream& operator<<(ostream& os, const Product& product);
    friend istream& operator>>(istream& is, Product& product);

    void displayProduct() const;
};

#endif