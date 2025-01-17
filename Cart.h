#include <vector>
#include <string>
using namespace std;

// Κλάση Cart: Αντιπροσωπεύει ένα καλάθι αγορών
class Cart {
private:
    vector<pair<string, int>> items; // Λίστα προϊόντων με τις ποσότητές τους
    double totalCost; // Συνολικό κόστος των προϊόντων στο καλάθι

public:
    // Constructor: Αρχικοποιεί ένα άδειο καλάθι με συνολικό κόστος 0
    Cart();

    // Προσθέτει ένα προϊόν στο καλάθι
    // - title: Τίτλος προϊόντος
    // - quantity: Ποσότητα προϊόντος
    // - price: Τιμή προϊόντος
    void addItem(const string& title, int quantity, double price);

    // Αφαιρεί ένα προϊόν από το καλάθι
    // - title: Τίτλος προϊόντος
    // - price: Τιμή προϊόντος
    void removeItem(const string& title, double price);

    // Ενημερώνει την ποσότητα ενός προϊόντος στο καλάθι
    // - title: Τίτλος προϊόντος
    // - newQuantity: Νέα ποσότητα
    // - price: Τιμή προϊόντος
    // - availableQuantity: Διαθέσιμη ποσότητα στο απόθεμα
    void updateItem(const string& title, int newQuantity, double price, int availableQuantity);

    // Εμφανίζει το περιεχόμενο του καλαθιού
    void displayCart() const;

    // Επιστρέφει το συνολικό κόστος του καλαθιού
    double getTotalCost() const;

    // Αδειάζει το καλάθι
    void clearCart();

    // Επιστρέφει τη λίστα των προϊόντων στο καλάθι
    vector<pair<string, int>> getItems() const;
};
