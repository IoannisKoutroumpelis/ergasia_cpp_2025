#include "Cart.h"
#include "Trim.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Κατασκευαστής: Αρχικοποιεί το καλάθι
// - Ορίζει το συνολικό κόστος (`totalCost`) στο 0, καθώς το καλάθι ξεκινάει άδειο
Cart::Cart() : totalCost(0) {}

// Προσθέτει προϊόν στο καλάθι
// - Ελέγχει αν το προϊόν υπάρχει ήδη στη λίστα `items` που αποθηκεύει το καλάθι.
// - Αν υπάρχει, ενημερώνει την ποσότητά του.
// - Αν δεν υπάρχει, προσθέτει το προϊόν ως νέο στοιχείο στη λίστα.
void Cart::addItem(const string& title, int quantity, double price) {
    // Αναζήτηση του προϊόντος στη λίστα `items` χρησιμοποιώντας τη συνάρτηση `find_if`.
    // - `find_if`: Επιστρέφει έναν iterator που δείχνει στο στοιχείο που ταιριάζει στο κριτήριο.
    auto it = find_if(items.begin(), items.end(), [&title](const pair<string, int>& item) {
        return item.first == title; // Συγκρίνει τον τίτλο του προϊόντος
    });

    // Αν το προϊόν βρεθεί, ενημερώνει την ποσότητα
    if (it != items.end()) {
        it->second += quantity; // Αυξάνει την ποσότητα του προϊόντος
    } else {
        // Αν δεν βρεθεί, το προσθέτει στη λίστα `items` χρησιμοποιώντας `emplace_back`.
        items.emplace_back(title, quantity); // Προσθήκη νέου προϊόντος
    }

    // Ενημερώνει το συνολικό κόστος του καλαθιού
    totalCost += price * quantity;

    // Εμφάνιση μηνύματος για την επιτυχή προσθήκη
    cout << "Added " << quantity << " x " << title << " to the cart.\n";
}

// Αφαιρεί προϊόν από το καλάθι
// - Εντοπίζει το προϊόν στη λίστα `items` και το αφαιρεί.
// - Αν το προϊόν δεν βρεθεί, εμφανίζει μήνυμα σφάλματος.
void Cart::removeItem(const string& title, double price) {
    // Αναζήτηση του προϊόντος στη λίστα `items` χρησιμοποιώντας `find_if`.
    auto it = find_if(items.begin(), items.end(), [&title](const pair<string, int>& item) {
        return item.first == title;
    });

    if (it != items.end()) { // Αν το προϊόν βρεθεί
        // Μείωση του συνολικού κόστους με βάση την ποσότητα και την τιμή του προϊόντος
        totalCost -= it->second * price;
        items.erase(it); // Αφαίρεση του προϊόντος από τη λίστα
        cout << "Removed " << title << " from the cart.\n";
    } else {
        // Εμφάνιση μηνύματος αν το προϊόν δεν βρεθεί
        cout << "Product not found in the cart.\n";
    }
}

// Ενημερώνει την ποσότητα ενός προϊόντος στο καλάθι
// - Ελέγχει αν το προϊόν υπάρχει και αν η νέα ποσότητα είναι έγκυρη.
// - Ενημερώνει την ποσότητα και το συνολικό κόστος.
void Cart::updateItem(const string& title, int newQuantity, double price, int availableQuantity) {
    // Αναζήτηση του προϊόντος στη λίστα `items`
    auto it = find_if(items.begin(), items.end(), [&title](const pair<string, int>& item) {
        return item.first == title;
    });

    if (it != items.end()) { // Αν το προϊόν βρεθεί
        if (newQuantity > 0 && newQuantity <= availableQuantity) { // Έλεγχος εγκυρότητας ποσότητας
            // Ενημέρωση του συνολικού κόστους
            totalCost += price * (newQuantity - it->second);
            it->second = newQuantity; // Ενημέρωση ποσότητας
            cout << "Updated " << title << " to quantity: " << newQuantity << ".\n";
        } else {
            // Μήνυμα σφάλματος αν η ποσότητα δεν είναι έγκυρη
            cout << "Invalid quantity. Available stock: " << availableQuantity << ".\n";
        }
    } else {
        // Μήνυμα σφάλματος αν το προϊόν δεν βρεθεί
        cout << "Product not found in the cart.\n";
    }
}

// Εμφανίζει το περιεχόμενο του καλαθιού
// - Ελέγχει αν το καλάθι είναι άδειο.
// - Εμφανίζει τα προϊόντα και τις ποσότητές τους σε μορφοποιημένη έξοδο.
void Cart::displayCart() const {
    if (items.empty()) { // Έλεγχος αν το καλάθι είναι άδειο
        cout << "Cart is empty.\n";
        return;
    }

    // Εμφάνιση περιεχομένων του καλαθιού
    cout << "---CART START---\n";
    for (const auto& item : items) {
        cout << item.second << " " << item.first << "\n"; // Εμφάνιση ποσότητας και τίτλου
    }
    cout << "---CART END---\n";
    // Εμφάνιση του συνολικού κόστους
    cout << "Total Cost: " << fixed << setprecision(2) << totalCost << "\n";
}

// Επιστρέφει το συνολικό κόστος του καλαθιού
// - Επιστρέφει το `totalCost` χωρίς να το τροποποιεί.
double Cart::getTotalCost() const {
    return totalCost;
}

// Καθαρίζει το περιεχόμενο του καλαθιού
// - Διαγράφει όλα τα στοιχεία από τη λίστα `items`.
// - Μηδενίζει το συνολικό κόστος (`totalCost`).
void Cart::clearCart() {
    items.clear(); // Διαγραφή όλων των στοιχείων από τη λίστα
    totalCost = 0; // Επαναφορά του συνολικού κόστους
}

// Επιστρέφει τα αντικείμενα του καλαθιού
// - Επιστρέφει αντίγραφο της λίστας `items`.
// - Χρησιμοποιεί `const` για να διασφαλίσει ότι η μέθοδος δεν τροποποιεί την κατάσταση του αντικειμένου.
vector<pair<string, int>> Cart::getItems() const {
    return items; // Επιστροφή αντιγράφου των στοιχείων
}
