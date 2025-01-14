#include "Customer.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Προσθήκη προϊόντος στο καλάθι
void Customer::addToCart(const vector<Product>& products) {
    string title;
    double quantity;

    cout << "Enter product title to add: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter quantity: ";
    cin >> quantity;

    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it != products.end()) {
        if (quantity <= it->getQuantity()) {
            cart.addItem(it->getTitle(), quantity, it->getPrice());
        } else {
            cout << "Not enough stock available. Adding all available quantity.\n";
            cart.addItem(it->getTitle(), it->getQuantity(), it->getPrice());
        }
    } else {
        cout << "Product not found.\n";
    }
}

// Αφαίρεση προϊόντος από το καλάθι
void Customer::removeFromCart() {
    string title;

    cout << "Enter product title to remove: ";
    cin.ignore();
    getline(cin, title);

    cart.removeItem(title);
}

// Ενημέρωση προϊόντος στο καλάθι
void Customer::updateCart(const vector<Product>& products) {
    string title;
    double quantity;

    cout << "Enter product title to update: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter new quantity: ";
    cin >> quantity;

    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it != products.end()) {
        cart.updateItem(it->getTitle(), quantity, it->getPrice(), it->getQuantity());
    } else {
        cout << "Product not found.\n";
    }
}

// Ολοκλήρωση παραγγελίας
void Customer::completeOrder(vector<Product>& products, const string& fileName) {
    string historyFileName = "files/order_history/" + username + "_history.txt";

    ofstream historyFile(historyFileName, ios::app);
    if (!historyFile.is_open()) {
        cerr << "Error: Could not open " << historyFileName << " for writing.\n";
        return;
    }

    historyFile << "---CART " << orderHistory.size() + 1 << " START---\n";
    for (const auto& item : cart.getItems()) {
        historyFile << item.second << " " << item.first << "\n";
    }
    historyFile << "---CART " << orderHistory.size() + 1 << " END---\n";
    historyFile << "Total Cost: " << fixed << setprecision(2) << cart.getTotalCost() << "\n";

    historyFile.close();
    cart.clearCart();

    // Δημιουργία εγγραφής παραγγελίας
    stringstream ss;
    ss << "---CART " << orderHistory.size() + 1 << " START---\n";
    for (const auto& item : cart.getItems()) {
        ss << item.second << " " << item.first << "\n";
    }
    ss << "---CART " << orderHistory.size() + 1 << " END---\n";
    ss << "Total Cost: " << fixed << setprecision(2) << cart.getTotalCost() << "\n";

    orderHistory.push_back(ss.str());
    cart.clearCart();

    // Αποθήκευση στο αρχείο παραγγελιών
    historyFile << ss.str();
    historyFile.close();

    // Ενημέρωση του αρχείου προϊόντων
    ofstream productFile(fileName);
    if (!productFile.is_open()) {
        cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }

    for (const auto& product : products) {
        productFile << product.getTitle() << "@" << product.getDescription() << "@"
                    << product.getCategory() << "@" << product.getSubCategory() << "@"
                    << product.getPrice() << "@" << product.getUnit() << "@"
                    << product.getQuantity() << "\n";
    }

    productFile.close();

    cout << "Order completed successfully and inventory updated.\n";
}

// Προβολή περιεχομένου καλαθιού
void Customer::viewCart() const {
    cart.displayCart();
}

// Προβολή ιστορικού παραγγελιών
void Customer::viewOrderHistory() const {
    if (orderHistory.empty()) {
        cout << "No orders in history.\n";
        return;
    }

    cout << "---Order History---\n";
    for (const auto& order : orderHistory) {
        cout << order << "\n";
    }
}

// Εμφάνιση μενού πελάτη
void Customer::displayMenu(vector<Product>& products, const string& fileName) {
    int choice;
    do {
        cout << "\n---Customer Menu---\n";
        cout << "1. Add product to cart\n";
        cout << "2. Remove product from cart\n";
        cout << "3. Update product in cart\n";
        cout << "4. View cart\n";
        cout << "5. Complete order\n";
        cout << "6. View order history\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addToCart(products);
                break;
            case 2:
                removeFromCart();
                break;
            case 3:
                updateCart(products);
                break;
            case 4:
                viewCart();
                break;
            case 5:
                completeOrder(products, fileName);
                break;
            case 6:
                viewOrderHistory();
                break;
            case 7:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}
