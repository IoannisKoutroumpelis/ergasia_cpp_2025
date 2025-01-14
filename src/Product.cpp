#include "Product.h"
#include <iomanip>
using namespace std;

// Constructor
Product::Product(const string& title, const string& description, const string& category,
                 const string& subCategory, double price, const string& unit, double quantity)
    : title(title), description(description), category(category), subCategory(subCategory),
      price(price), unit(unit), quantity(quantity) {}

// Getters
string Product::getTitle() const { return title; }
string Product::getDescription() const { return description; }
string Product::getCategory() const { return category; }
string Product::getSubCategory() const { return subCategory; }
double Product::getPrice() const { return price; }
string Product::getUnit() const { return unit; }
double Product::getQuantity() const { return quantity; }

// Setters
void Product::setTitle(const string& newTitle) { title = newTitle; }
void Product::setDescription(const string& newDescription) { description = newDescription; }
void Product::setCategory(const string& newCategory) { category = newCategory; }
void Product::setSubCategory(const string& newSubCategory) { subCategory = newSubCategory; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setQuantity(double newQuantity) { quantity = newQuantity; }

// Overloaded operator<< for output
ostream& operator<<(ostream& os, const Product& product) {
    os << product.title << "@" << product.description << "@" << product.category << "@"
       << product.subCategory << "@" << fixed << setprecision(2) << product.price << "@"
       << product.unit << "@" << product.quantity;
    return os;
}

// Overloaded operator>> for input
istream& operator>>(istream& is, Product& product) {
    getline(is, product.title, '@');
    getline(is, product.description, '@');
    getline(is, product.category, '@');
    getline(is, product.subCategory, '@');
    is >> product.price;
    is.ignore(1, '@');
    getline(is, product.unit, '@');
    is >> product.quantity;
    is.ignore(); // Ignore the newline character
    return is;
}

// Display product details
void Product::displayProduct() const {
    cout << fixed << setprecision(2);
    cout << title << " @ " << description << " @ " << category << " @ "
         << subCategory << " @ " << price << " per " << unit << " @ "
         << quantity << " available\n";
}
