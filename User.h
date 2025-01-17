#ifndef USER_H
#define USER_H

#include "Product.h"
#include <string>
#include <vector>
using namespace std;

// Κλάση User: Βασική κλάση που αντιπροσωπεύει έναν χρήστη του συστήματος (Admin ή Customer)
class User {
protected:
    string username;   // Όνομα χρήστη
    string password;   // Κωδικός πρόσβασης
    bool isAdmin;      // Σημαία που δηλώνει αν ο χρήστης είναι Admin (true) ή Customer (false)

public:
    // Κατασκευαστής: Αρχικοποιεί έναν χρήστη με όνομα χρήστη, κωδικό και ρόλο (Admin/Customer)
    User(const string& username, const string& password, bool isAdmin)
        : username(username), password(password), isAdmin(isAdmin) {}

    // Επιστρέφει το όνομα χρήστη
    // - Χρησιμοποιεί `const` για να διασφαλίσει ότι η μέθοδος δεν τροποποιεί το αντικείμενο
    string getUsername() const;

    // Επιστρέφει τον κωδικό πρόσβασης
    // - Χρησιμοποιείται για εσωτερική επαλήθευση του χρήστη
    string getPassword() const;

    // Επιστρέφει αν ο χρήστης είναι Admin
    // - Χρησιμοποιείται για να διαφοροποιηθεί η πρόσβαση στις λειτουργίες
    bool getIsAdmin() const;

    // Εικονικός καταστροφέας: Διασφαλίζει τη σωστή καταστροφή αντικειμένων από υποκλάσεις
    virtual ~User() {}
};

#endif
