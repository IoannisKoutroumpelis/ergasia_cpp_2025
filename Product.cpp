#include "Product.h"
#include "Trim.h"
#include <iomanip>
using namespace std;

// Constructor
Product::Product(const string& title, const string& description, const string& category,
                 const string& subCategory, double price, const string& unit, int quantity)
    : title(title), description(description), category(category), subCategory(subCategory),
      price(price), unit(unit), quantity(quantity) {}

// Getters
string Product::getTitle() const { return trim(title); }
string Product::getDescription() const { return trim(description); }
string Product::getCategory() const { return trim(category); }
string Product::getSubCategory() const { return trim(subCategory); }
double Product::getPrice() const { return price; }
string Product::getUnit() const { return trim(unit); }
int Product::getQuantity() const { return quantity; }

// Setters
void Product::setTitle(const string& newTitle) { title = newTitle; }
void Product::setDescription(const string& newDescription) { description = newDescription; }
void Product::setCategory(const string& newCategory) { category = newCategory; }
void Product::setSubCategory(const string& newSubCategory) { subCategory = newSubCategory; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setQuantity(int newQuantity) { quantity = newQuantity; }

// Overloaded operator<< for output
ostream& operator<<(ostream& os, const Product& product) {
    os << product.title << "@" << product.description << "@" << product.category << "@"
       << product.subCategory << "@" << fixed << setprecision(2) << product.price << "@"
       << product.unit << "@" << fixed << setprecision(0) << product.quantity;
    return os;
}

// Overloaded operator>> for input
istream& operator>>(istream& is, Product& product) {
    string priceStr;  // Temporary string to handle the price as text before converting to double

    // Διαβάστε τις ιδιότητες του Product από τη ροή εισόδου
    getline(is, product.title, '@');
    getline(is, product.description, '@');
    getline(is, product.category, '@');
    getline(is, product.subCategory, '@');

    // Διαβάστε το price ως string
    getline(is, priceStr, '@');

    if(priceStr!="")
        product.price = stod(trim(priceStr));  // Μετατροπή σε double

    getline(is, product.unit, '@');
    is >> product.quantity;
    is.ignore(); // Αγνόηση του χαρακτήρα newline

    return is;
}


// Display product details
void Product::displayProduct() const {
    cout << fixed << setprecision(2);
    cout << trim(title) << " @ " << trim(description) << " @ " << trim(category) << " @ "
         << trim(subCategory) << " @ " << price << " per " << trim(unit) << " @ "
         << quantity << " available\n";
}
