#include "Eshop.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Constructor: Αποθηκεύει τα paths και φορτώνει τα δεδομένα
Eshop::Eshop(const string& categoriesFile, const string& productsFile, const string& usersFile): categoriesFile(categoriesFile), productsFile(productsFile), usersFile(usersFile) {
    loadCategories(); // Καλεί τη συνάρτηση για να φορτώσει τις κατηγορίες από το αρχείο
    loadProducts();   // Καλεί τη συνάρτηση για να φορτώσει τα προϊόντα από το αρχείο
    loadUsers();      // Καλεί τη συνάρτηση για να φορτώσει τους χρήστες από το αρχείο
}

// Destructor: Διαγράφει δυναμικούς χρήστες από τη μνήμη
Eshop::~Eshop() {
    for (auto user : users) { // Διαγράφει κάθε χρήστη που αποθηκεύεται δυναμικά
        delete user;
    }
}

// Φόρτωση κατηγοριών από αρχείο
void Eshop::loadCategories() {
    ifstream file(categoriesFile); // Ανοίγει το αρχείο κατηγοριών
    if (!file.is_open()) { // Ελέγχει αν το αρχείο δεν άνοιξε
        cerr << "Error: Could not open " << categoriesFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) { // Διαβάζει κάθε γραμμή του αρχείου
        categories.push_back(line); // Προσθέτει την κατηγορία στη λίστα
    }
    file.close(); // Κλείνει το αρχείο
}

// Φόρτωση προϊόντων από αρχείο
void Eshop::loadProducts() {
    ifstream file(productsFile); // Ανοίγει το αρχείο προϊόντων
    if (!file.is_open()) { // Ελέγχει αν το αρχείο δεν άνοιξε
        cerr << "Error: Could not open " << productsFile << endl;
        return;
    }

    Product product;
    while (file >> product) { // Διαβάζει προϊόντα από το αρχείο
        products.push_back(product); // Προσθέτει το προϊόν στη λίστα
    }
    file >> product; // Τελική ανάγνωση προϊόντος
    products.push_back(product); // Προσθήκη στη λίστα
    file.close(); // Κλείνει το αρχείο
}

// Φόρτωση χρηστών από αρχείο
void Eshop::loadUsers() {
    ifstream file(usersFile); // Ανοίγει το αρχείο χρηστών
    if (!file.is_open()) { // Ελέγχει αν το αρχείο δεν άνοιξε
        cerr << "Error: Could not open " << usersFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) { // Διαβάζει κάθε γραμμή του αρχείου
        stringstream ss(line);
        string username, password;
        int isAdmin;

        getline(ss, username, ','); // Διαβάζει το όνομα χρήστη
        getline(ss, password, ','); // Διαβάζει τον κωδικό
        ss >> isAdmin; // Ελέγχει αν είναι διαχειριστής

        if (isAdmin) { // Αν είναι διαχειριστής
            users.push_back(new Admin(username, password));
        } else { // Αν είναι πελάτης
            users.push_back(new Customer(username, password));
        }
    }
    file.close(); // Κλείνει το αρχείο
}

// Ενημέρωση αρχείου προϊόντων
void Eshop::updateProductsFile() {
    ofstream file(productsFile, ios::trunc); // Ανοίγει το αρχείο για εγγραφή
    if (!file.is_open()) { // Ελέγχει αν το αρχείο δεν άνοιξε
        cerr << "Error: Could not open " << productsFile << " for writing.\n";
        return;
    }

    for (const auto& product : products) { // Γράφει κάθε προϊόν στο αρχείο
        file << product << endl;
    }
    file.close(); // Κλείνει το αρχείο
}

// Ενημέρωση αρχείου χρηστών
void Eshop::updateUsersFile() {
    ofstream file(usersFile, ios::trunc); // Ανοίγει το αρχείο για εγγραφή
    if (!file.is_open()) { // Ελέγχει αν το αρχείο δεν άνοιξε
        cerr << "Error: Could not open " << usersFile << " for writing.\n";
        return;
    }

    for (const auto& user : users) { // Γράφει κάθε χρήστη στο αρχείο
        file << user->getUsername() << "," << user->getPassword() << ","
             << (user->getIsAdmin() ? 1 : 0) << endl;
    }
    file.close(); // Κλείνει το αρχείο
}

// Εγγραφή νέου χρήστη
void Eshop::registerUser() {
    string username, password;
    string isAdmin;

    cout << "Please enter your username: ";
    cin >> username;
    for (const auto& user : users) { // Ελέγχει αν υπάρχει το όνομα χρήστη
        if (user->getUsername() == username) {
            cout << "Username already exists.\n";
            return;
        }
    }

    cout << "Please enter your password: ";
    cin >> password;

    cout << "Are you an admin user? (Y/N): ";
    cin >> isAdmin;

    if (isAdmin == "y") { // Αν είναι διαχειριστής
        users.push_back(new Admin(username, password));
        updateUsersFile(); // Ενημερώνει το αρχείο χρηστών
        cout << "Thanks for signing up! You are automatically logged-in as " << username << endl;
        auto it = users.end() - 1;
        dynamic_cast<Admin*>(*it)->displayMenu(products, categories, productsFile);
    } else { // Αν είναι πελάτης
        users.push_back(new Customer(username, password));
        updateUsersFile(); // Ενημερώνει το αρχείο χρηστών
        cout << "Thanks for signing up! You are automatically logged-in as " << username << endl;
        auto it = users.end() - 1;
        dynamic_cast<Customer*>(*it)->displayMenu(products, productsFile);
    }
}

// Είσοδος χρήστη
void Eshop::login() {
    string username, password;

    cout << "Please enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;

    auto it = find_if(users.begin(), users.end(), [&username, &password](User* user) {
        return user->getUsername() == username && user->getPassword() == password;
    });

    if (it != users.end()) { // Αν βρεθεί ο χρήστης
        cout << "\nWelcome " << username << "!\n" << endl;
        if ((*it)->getIsAdmin()) { // Αν είναι διαχειριστής
            dynamic_cast<Admin*>(*it)->displayMenu(products, categories, productsFile);
        } else { // Αν είναι πελάτης
            dynamic_cast<Customer*>(*it)->displayMenu(products, productsFile);
        }
    } else { // Αν δεν βρεθεί ο χρήστης
        cout << "Invalid credentials. Please try again.\n";
    }
}
