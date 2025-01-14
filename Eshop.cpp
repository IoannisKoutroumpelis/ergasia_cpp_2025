#include "Eshop.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Κατασκευαστής: Αποθηκεύει τα paths και φορτώνει τα δεδομένα
Eshop::Eshop(const string& categoriesFile, const string& productsFile, const string& usersFile)
    : categoriesFile(categoriesFile), productsFile(productsFile), usersFile(usersFile) {
    loadCategories();
    loadProducts();
    loadUsers();
}

// Καταστροφέας: Διαγράφει δυναμικούς χρήστες από τη μνήμη
Eshop::~Eshop() {
    for (auto user : users) {
        delete user;
    }
}

// Φόρτωση κατηγοριών από αρχείο
void Eshop::loadCategories() {
    ifstream file(categoriesFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << categoriesFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        categories.push_back(line);
    }
    file.close();
}

// Φόρτωση προϊόντων από αρχείο
void Eshop::loadProducts() {
    ifstream file(productsFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << productsFile << endl;
        return;
    }

    Product product;
    while (file >> product) {
        products.push_back(product);
    }
    file.close();
}

// Φόρτωση χρηστών από αρχείο
void Eshop::loadUsers() {
    ifstream file(usersFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << usersFile << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        int isAdmin;

        getline(ss, username, ',');
        getline(ss, password, ',');
        ss >> isAdmin;

        if (isAdmin) {
            users.push_back(new Admin(username, password));
        } else {
            users.push_back(new Customer(username, password));
        }
    }
    file.close();
}

// Ενημέρωση αρχείου προϊόντων
void Eshop::updateProductsFile() {
    ofstream file(productsFile, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << productsFile << " for writing.\n";
        return;
    }

    for (const auto& product : products) {
        file << product << endl;
    }
    file.close();
}

// Ενημέρωση αρχείου χρηστών
void Eshop::updateUsersFile() {
    ofstream file(usersFile, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << usersFile << " for writing.\n";
        return;
    }

    for (const auto& user : users) {
        file << user->getUsername() << "," << user->getPassword() << ","
             << (user->getIsAdmin() ? 1 : 0) << endl;
    }
    file.close();
}

// Εγγραφή νέου χρήστη
void Eshop::registerUser() {
    string username, password;
    int isAdmin;

    cout << "Please enter your username: ";
    cin >> username;
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            cout << "Username already exists.\n";
            return;
        }
    }

    cout << "Please enter your password: ";
    cin >> password;

    cout << "Is the user an admin? (1 for yes, 0 for no): ";
    cin >> isAdmin;

    if (isAdmin) {
        users.push_back(new Admin(username, password));
    } else {
        users.push_back(new Customer(username, password));
    }

    updateUsersFile();
    cout << "User registered successfully.\n";
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

    if (it != users.end()) {
        cout << "Welcome " << username << "!" << endl;
        if ((*it)->getIsAdmin()) {
            dynamic_cast<Admin*>(*it)->displayMenu(products, categories, productsFile);
        } else {
            dynamic_cast<Customer*>(*it)->displayMenu(products, productsFile);
        }
    } else {
        cout << "Invalid credentials. Please try again.\n";
    }
}