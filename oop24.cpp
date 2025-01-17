#include "Eshop.h"

// Σημείο εκκίνησης του προγράμματος
int main(int argc, char* argv[]) {
    // Έλεγχος σωστής χρήσης του προγράμματος
    if (argc != 4) { // Αναμένει 3 ορίσματα γραμμής εντολών
        cerr << "Usage: " << argv[0] << " <categories_file> <products_file> <users_file>\n";
        return 1; // Επιστρέφει κωδικό σφάλματος
    }

    // Δημιουργία αντικειμένου Eshop με τα παρεχόμενα αρχεία
    Eshop shop(argv[1], argv[2], argv[3]);

    string choice;
    cout << "Welcome to the e-shop!!!\n";

    // Κύκλος επιλογών για σύνδεση ή εγγραφή
    do {
        cout << "Do you want to login or register? (enter option): ";
        cin >> choice;

        if (choice == "login") {
            shop.login(); // Καλεί τη μέθοδο login για σύνδεση χρήστη
            return 0; // Τερματίζει το πρόγραμμα μετά τη σύνδεση
        }
        else if (choice == "register") {
            shop.registerUser(); // Καλεί τη μέθοδο registerUser για εγγραφή νέου χρήστη
            return 0; // Τερματίζει το πρόγραμμα μετά την εγγραφή
        }
        else {
            cout << "Invalid choice. Try again.\n"; // Μήνυμα για μη έγκυρη επιλογή
        }
    } while (true); // Επαναλαμβάνει μέχρι να δοθεί έγκυρη επιλογή
}
