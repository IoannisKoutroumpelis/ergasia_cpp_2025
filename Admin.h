#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Product.h"
#include <vector>
using namespace std;

// Κλάση Admin: Υποκλάση της User που αντιπροσωπεύει έναν διαχειριστή
class Admin : public User {
public:
    // Κατασκευαστής: Δημιουργεί έναν Admin χρήστη με όνομα χρήστη και κωδικό πρόσβασης
    Admin(const string& username, const string& password) : User(username, password, true) {}

    // Εμφανίζει το μενού του διαχειριστή
    void displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName);

    // Προσθέτει ένα νέο προϊόν στη λίστα προϊόντων
    void addProduct(vector<Product>& products, const vector<string>& categories, const string& fileName);

    // Αφαιρεί ένα προϊόν από τη λίστα προϊόντων
    void removeProduct(vector<Product>& products, const string& fileName);

    // Επεξεργάζεται τις λεπτομέρειες ενός προϊόντος
    void editProduct(vector<Product>& products, const string& fileName);

    // Αναζητά προϊόντα με βάση τίτλο ή κατηγορία
    void searchProducts(const vector<Product>& products, const vector<string>& categories) const;

    // Εμφανίζει τα προϊόντα που δεν έχουν διαθέσιμο απόθεμα
    void unavailableProducts() const;

    // Εμφανίζει τα 5 πιο δημοφιλή προϊόντα
    void top5Products(const vector<Product>& products) const;
};

#endif
