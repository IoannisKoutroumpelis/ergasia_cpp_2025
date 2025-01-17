#include "Product.h" 
#include "Trim.h"
#include <iomanip>
using namespace std;

// Constructor: Αρχικοποιεί τις τιμές του προϊόντος με τις αντίστοιχες παραμέτρους
Product::Product(const string& title, const string& description, const string& category,
                 const string& subCategory, double price, const string& unit, int quantity)
    : title(title), description(description), category(category), subCategory(subCategory),
      price(price), unit(unit), quantity(quantity) {}

// Getters: Επιστρέφουν τις τιμές των πεδίων του αντικειμένου, εφαρμόζοντας trim στα string
string Product::getTitle() const { return trim(title); }
string Product::getDescription() const { return trim(description); }
string Product::getCategory() const { return trim(category); }
string Product::getSubCategory() const { return trim(subCategory); }
double Product::getPrice() const { return price; }
string Product::getUnit() const { return trim(unit); }
int Product::getQuantity() const { return quantity; }

// Setters: Ενημερώνουν τις τιμές των πεδίων του αντικειμένου
void Product::setTitle(const string& newTitle) { title = newTitle; }
void Product::setDescription(const string& newDescription) { description = newDescription; }
void Product::setCategory(const string& newCategory) { category = newCategory; }
void Product::setSubCategory(const string& newSubCategory) { subCategory = newSubCategory; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setQuantity(int newQuantity) { quantity = newQuantity; }

// Υπερφορτωμένος τελεστής εξόδου (<<)
// Εξάγει τις ιδιότητες του προϊόντος στο ρεύμα εξόδου με διαχωριστή '@'
ostream& operator<<(ostream& os, const Product& product) {
    os << product.title << "@" << product.description << "@" << product.category << "@"
       << product.subCategory << "@" << fixed << setprecision(2) << product.price << "@"
       << product.unit << "@" << fixed << setprecision(0) << product.quantity;
    return os;
}

// Υπερφορτωμένος τελεστής εισόδου (>>)
// Εισάγει τις ιδιότητες του προϊόντος από το ρεύμα εισόδου
istream& operator>>(istream& is, Product& product) {
    string priceStr;  // Προσωρινή μεταβλητή για το price ως string

    // Διαβάζει τις ιδιότητες του προϊόντος από το ρεύμα εισόδου
    getline(is, product.title, '@');
    getline(is, product.description, '@');
    getline(is, product.category, '@');
    getline(is, product.subCategory, '@');

    // Διαβάζει το price ως string και το μετατρέπει σε double
    getline(is, priceStr, '@');
    if(priceStr != "")
        product.price = stod(trim(priceStr));

    getline(is, product.unit, '@');
    is >> product.quantity;  // Διαβάζει την ποσότητα
    is.ignore(); // Αγνοεί τον χαρακτήρα newline

    return is;
}

// Εμφάνιση λεπτομερειών προϊόντος
// Εκτυπώνει τα χαρακτηριστικά του προϊόντος σε μορφοποιημένη έξοδο
void Product::displayProduct() const {
    cout << fixed << setprecision(2);
    cout << trim(title) << " @ " << trim(description) << " @ " << trim(category) << " @ "
         << trim(subCategory) << " @ " << price << " per " << trim(unit) << " @ "
         << quantity << " available\n";
}
