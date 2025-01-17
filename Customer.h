#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Product.h"
#include "Cart.h"
#include <vector>
using namespace std;

// Κλάση Customer: Υποκλάση της User που αντιπροσωπεύει έναν πελάτη
class Customer : public User {
private:
    Cart cart; // Αντικείμενο που αποθηκεύει τα προϊόντα που έχει προσθέσει ο πελάτης στο καλάθι του

public:
    // Constructor: Αρχικοποιεί έναν πελάτη με όνομα χρήστη και κωδικό πρόσβασης
    // - Η τρίτη παράμετρος (false) δηλώνει ότι ο χρήστης δεν είναι Admin
    Customer(const string& username, const string& password) : User(username, password, false) {}

    void searchProducts(const vector<Product>& products, const vector<string>& categories) const;

    // Προσθέτει ένα προϊόν στο καλάθι
    // - Χρησιμοποιεί ένα const vector<Product>& για να διασφαλιστεί ότι η λίστα προϊόντων δεν επηρεάζεται
    void addToCart(const vector<Product>& products);

    // Αφαιρεί ένα προϊόν από το καλάθι
    // - Δέχεται ένα vector<Product>& επειδή ενδέχεται να χρειαστεί ενημέρωση του αποθέματος του προϊόντος
    void removeFromCart(vector<Product>& products);

    // Ενημερώνει την ποσότητα ενός προϊόντος στο καλάθι
    // - Χρησιμοποιεί const vector<Product>& για να διαβάσει πληροφορίες προϊόντων χωρίς να τις τροποποιήσει
    void updateCart(const vector<Product>& products);

    // Ολοκληρώνει την παραγγελία του πελάτη
    // - Ενημερώνει το απόθεμα προϊόντων (vector<Product>&) και γράφει το ιστορικό της παραγγελίας σε αρχείο
    void completeOrder(vector<Product>& products, const string& fileName);

    // Προβάλλει το περιεχόμενο του καλαθιού
    // - Η μέθοδος είναι const επειδή δεν τροποποιεί την κατάσταση του αντικειμένου
    void viewCart() const;

    // Εμφανίζει το ιστορικό παραγγελιών του πελάτη
    // - Χρησιμοποιεί const για να εγγυηθεί ότι δεν επηρεάζονται οι μεταβλητές της κλάσης
    void viewOrderHistory() const;

    // Εμφανίζει το μενού επιλογών του πελάτη
    // - Διαχειρίζεται τις επιλογές του πελάτη και αλληλεπιδρά με τα προϊόντα (vector<Product>&)
    void displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName);
};

#endif
