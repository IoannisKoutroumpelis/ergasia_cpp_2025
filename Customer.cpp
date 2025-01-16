#include "Customer.h"
#include "Product.h"
#include "Eshop.h"
#include "Trim.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// Προσθήκη προϊόντος στο καλάθι
void Customer::addToCart(const vector<Product>& products) {
    string title;
    int quantity;

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
void Customer::removeFromCart(vector<Product>& products) {
    string title;

    cout << "Enter product title to remove: ";
    cin.ignore();
    getline(cin, title);
    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });
    double price = it->getPrice();
    cart.removeItem(title, price);
}

// Ενημέρωση προϊόντος στο καλάθι
void Customer::updateCart(const vector<Product>& products) {
    string title;
    int quantity;

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

    fstream historyFile(historyFileName, ios::app);
    if (!historyFile.is_open()) {
        cerr << "Error: Could not open " << historyFileName << " for writing.\n";
        return;
    }

    // Δημιουργία εγγραφής παραγγελίας
    stringstream ss;
    ss << "\n\n---CART " << orderHistory.size() + 1 << " START---\n";
    for (const auto& item : cart.getItems()) {
        ss << item.second << " " << item.first << "\n";
    }
    ss << "---CART " << orderHistory.size() + 1 << " END---\n";
    ss << "Total Cost: " << fixed << setprecision(2) << cart.getTotalCost();

    for (auto& item : cart.getItems()) {
        auto it = find_if(products.begin(), products.end(), [&item](const Product& product) {
            return product.getTitle() == item.first;
        });
        if (it != products.end()) {
            double newQuantity = it->getQuantity() - item.second;
            it->setQuantity(newQuantity > 0 ? newQuantity : 0);
        }
    }
    
    orderHistory.push_back(ss.str());
    // Αποθήκευση στο αρχείο παραγγελιών
    historyFile << ss.str();
    historyFile.close();

    // Ενημέρωση του αρχείου προϊόντων
    ofstream productFile(fileName);
    if (!productFile.is_open()) {
        cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }

    auto it = products.begin();
    while (it != products.end()) {
        productFile << it->getTitle() << " @ " << it->getDescription() << " @ "
                    << it->getCategory() << " @ " << it->getSubCategory() << " @ "
                    << fixed << setprecision(2) << it->getPrice() << " @ "
                    << it->getUnit() << " @ " << fixed << setprecision(0) << it->getQuantity();

        // Προσθήκη νέας γραμμής εκτός από το τελευταίο στοιχείο
        if (++it != products.end()) {
            productFile << "\n";
        }
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
        cout << "---Customer Menu---\n";
        cout << "1. Search for a product\n";
        cout << "2. Add product to cart\n";
        cout << "3. Update product from cart\n";
        cout << "4. Remove product from cart\n";
        cout << "5. Complete order\n";
        cout << "6. View order history\n";
        cout << "7. View cart\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 2:
                addToCart(products);
                break;
            case 3:
                updateCart(products);
                break;
            case 4:
                removeFromCart(products);
                break;
            case 5:
                completeOrder(products, fileName);
                break;
            case 6:
                viewOrderHistory();
                break;
            case 7:
                viewCart();
                break;
            case 8:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}
