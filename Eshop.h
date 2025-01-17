#ifndef ESHOP_H
#define ESHOP_H

#include "Admin.h"
#include "Customer.h"
#include "Product.h"
#include <vector>
#include <string>
using namespace std;

// Κλάση Eshop: Αντιπροσωπεύει το ηλεκτρονικό κατάστημα και διαχειρίζεται κατηγορίες, προϊόντα και χρήστες
class Eshop {
private:
    vector<Product> products;      // Λίστα που αποθηκεύει όλα τα προϊόντα του καταστήματος
    vector<string> categories;     // Λίστα με τις διαθέσιμες κατηγορίες προϊόντων
    vector<User*> users;           // Δυναμική λίστα με δείκτες χρηστών (Admin/Customer)

    string categoriesFile;         // Path για το αρχείο που περιέχει τις κατηγορίες
    string productsFile;           // Path για το αρχείο που περιέχει τα προϊόντα
    string usersFile;              // Path για το αρχείο που περιέχει τους χρήστες

    // Ιδιωτικές μέθοδοι για φόρτωση δεδομένων από αρχεία
    void loadCategories(); // Φορτώνει κατηγορίες από το αρχείο
    void loadProducts();   // Φορτώνει προϊόντα από το αρχείο
    void loadUsers();      // Φορτώνει χρήστες από το αρχείο

    // Ιδιωτικές μέθοδοι για ενημέρωση αρχείων
    void updateProductsFile(); // Ενημερώνει το αρχείο προϊόντων
    void updateUsersFile();    // Ενημερώνει το αρχείο χρηστών

public:
    // Constructor: Αρχικοποιεί το κατάστημα με τα paths των αρχείων και φορτώνει τα δεδομένα
    Eshop(const string& categoriesFile, const string& productsFile, const string& usersFile);

    // Destructor: Απελευθερώνει τη μνήμη που χρησιμοποιείται για τους δυναμικούς χρήστες
    ~Eshop();

    // Επιτρέπει σε έναν χρήστη να συνδεθεί
    // - Διαχειρίζεται Admin και Customer μέσω της λίστας `users`
    void login();

    // Εγγράφει έναν νέο χρήστη (Admin ή Customer)
    // - Δημιουργεί νέο αντικείμενο χρήστη και το αποθηκεύει στη λίστα `users`
    void registerUser();
};

#endif
