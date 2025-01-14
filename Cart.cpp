#include "Cart.h"
#include "Trim.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Κατασκευαστής: Αρχικοποιεί το καλάθι
Cart::Cart() : totalCost(0) {}

// Προσθέτει προϊόν στο καλάθι
void Cart::addItem(const string& title, int quantity, double price) {
    auto it = find_if(items.begin(), items.end(), [&title](const pair<string, int>& item) {
        return item.first == title;
    });

    if (it != items.end()) {
        it->second += quantity;
    } else {
        items.emplace_back(title, quantity);
    }

    totalCost += price * quantity;
    cout << "Added " << quantity << " x " << title << " to the cart.\n";
}

// Αφαιρεί προϊόν από το καλάθι
void Cart::removeItem(const string& title) {
    auto it = find_if(items.begin(), items.end(), [&title](const pair<string, int>& item) {
        return item.first == title;
    });

    if (it != items.end()) {
        totalCost -= it->second;
        items.erase(it);
        cout << "Removed " << title << " from the cart.\n";
    } else {
        cout << "Product not found in the cart.\n";
    }
}

// Ενημερώνει την ποσότητα ενός προϊόντος στο καλάθι
void Cart::updateItem(const string& title, int newQuantity, double price, int availableQuantity) {
    auto it = find_if(items.begin(), items.end(), [&title](const pair<string, int>& item) {
        return item.first == title;
    });

    if (it != items.end()) {
        if (newQuantity > 0 && newQuantity <= availableQuantity) {
            totalCost += price * (newQuantity - it->second);
            it->second = newQuantity;
            cout << "Updated " << title << " to quantity: " << newQuantity << ".\n";
        } else {
            cout << "Invalid quantity. Available stock: " << availableQuantity << ".\n";
        }
    } else {
        cout << "Product not found in the cart.\n";
    }
}

// Εμφανίζει το περιεχόμενο του καλαθιού
void Cart::displayCart() const {
    if (items.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    cout << "---CART START---\n";
    for (const auto& item : items) {
        cout << item.second << " " << item.first << "\n";
    }
    cout << "---CART END---\n";
    cout << "Total Cost: " << fixed << setprecision(2) << totalCost << "\n";
}

// Επιστρέφει το συνολικό κόστος του καλαθιού
double Cart::getTotalCost() const {
    return totalCost;
}

// Καθαρίζει το περιεχόμενο του καλαθιού
void Cart::clearCart() {
    items.clear();
    totalCost = 0;
}

// Επιστρέφει τα αντικείμενα του καλαθιού
vector<pair<string, int>> Cart::getItems() const {
    return items;
}
