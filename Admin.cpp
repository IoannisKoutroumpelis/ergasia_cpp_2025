#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

// Προσθήκη νέου προϊόντος
void Admin::addProduct(vector<Product>& products, const vector<string>& categories, const string& fileName) {
    string title, description, category, subCategory, unit;
    double price;
    int quantity;

    cout << "Enter product title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter description: ";
    getline(cin, description);

    cout << "Available categories:\n";
    for (size_t i = 0; i < categories.size(); ++i) {
        cout << i + 1 << ". " << categories[i] << endl;
    }
    cout << "Select category: ";
    getline(cin, category);

    cout << "Enter subcategory: ";
    getline(cin, subCategory);

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter unit (Kg/Unit): ";
    cin >> unit;

    cout << "Enter quantity: ";
    cin >> quantity;

    products.emplace_back(title, description, category, subCategory, price, unit, quantity);

    // Ενημέρωση του αρχείου προϊόντων
    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }
    file << endl << title << " @ " << description << " @ " << category << " @ " << subCategory << " @ " 
         << fixed << setprecision(2)  << price << " @ " << unit << " @ " << fixed << setprecision(0) << quantity << endl;
    file.close();

    cout << "Product added successfully.\n";
}

// Επεξεργασία προϊόντος
void Admin::editProduct(vector<Product>& products, const string& fileName) {
    string title;
    cout << "Enter product title to edit: ";
    cin.ignore();
    getline(cin, title);

    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it == products.end()) {
        cout << "Product not found.\n";
        return;
    }

    string newDescription, newCategory, newSubCategory, newUnit;
    double newPrice;
    int newQuantity;

    cout << "Enter new description (or press Enter to keep current): ";
    getline(cin, newDescription);
    if (!newDescription.empty()) it->setDescription(newDescription);

    cout << "Enter new price (or -1 to keep current): ";
    cin >> newPrice;
    if (newPrice >= 0) it->setPrice(newPrice);

    cout << "Enter new quantity (or -1 to keep current): ";
    cin >> newQuantity;
    if (newQuantity >= 0) it->setQuantity(newQuantity);

    // Ενημέρωση αρχείου
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }
    for (const auto& product : products) {
        file << product.getTitle() << "@" << product.getDescription() << "@" << product.getCategory() << "@" 
             << product.getSubCategory() << "@" << product.getPrice() << "@" << product.getUnit() << "@" 
             << product.getQuantity() << endl;
    }
    file.close();

    cout << "Product updated successfully.\n";
}

// Αναζήτηση προϊόντων
void Admin::searchProducts(const vector<Product>& products, const vector<string>& categories) const {
    cout << "1. Search by title\n2. Search by category\nEnter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string title;
        cout << "Enter product title: ";
        getline(cin, title);

        for (const auto& product : products) {
            if (product.getTitle().find(title) != string::npos) {
                product.displayProduct();
            }
        }
    } else if (choice == 2) {
        cout << "Available categories:\n";
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << i + 1 << ". " << categories[i] << endl;
        }
        int catChoice;
        cout << "Select category (number): ";
        cin >> catChoice;

        if (catChoice < 1 || static_cast<size_t>(catChoice) > categories.size()) {
            cout << "Invalid category.\n";
            return;
        }

        for (const auto& product : products) {
            if (product.getCategory() == categories[catChoice - 1]) {
                product.displayProduct();
            }
        }
    } else {
        cout << "Invalid choice.\n";
    }
}

// Προβολή στατιστικών
void Admin::viewStatistics(const vector<Product>& products) const {
    cout << "1. View unavailable products\n2. View top ordered products\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Unavailable products:\n";
        for (const auto& product : products) {
            if (product.getQuantity() == 0) {
                product.displayProduct();
            }
        }
    } else if (choice == 2) {
        cout << "Feature not yet implemented: Top ordered products.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

void Admin::displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName) {
    int choice;
    do {
        cout << "\n---Admin Menu---\n";
        cout << "1. Add Product\n2. Edit Product\n3. Remove Product\n4. Search Product\n5. Show Unavailable Products\n6. Show Top 5 Products\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct(products, categories, fileName);
                break;
            case 2:
                editProduct(products, fileName);
                break;
            case 4:
                searchProducts(products, categories);
                break;
            case 7:
                cout << "Exiting Admin Menu.\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
}