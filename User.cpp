#include "User.h"

// Επιστρέφει το όνομα χρήστη
string User::getUsername() const {
    return username;
}

// Επιστρέφει τον κωδικό πρόσβασης
string User::getPassword() const{
    return password;
}

// Επιστρέφει αν ο χρήστης είναι admin (true) ή όχι (false)
bool User::getIsAdmin() const {
    return isAdmin;
}