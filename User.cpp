#include "User.h"

// Επιστρέφει το όνομα χρήστη
string User::getUsername() const {
    return username;
}

// Επιστρέφει τον κωδικό πρόσβασης
string User::getPassword() const{
    return password;
}

// Επιστρέφει αν ο χρήστης είναι admin (1) ή όχι (0)
bool User::getIsAdmin() const {
    return isAdmin;
}