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
// - Ελέγχει τη διαθεσιμότητα προϊόντος στη λίστα `products`.
// - Αν το προϊόν βρεθεί και υπάρχει επαρκές απόθεμα, το προσθέτει στο καλάθι.
void Customer::addToCart(const vector<Product>& products) {
    string title;
    int quantity;

    cout << "Enter product title to add: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter quantity: ";
    cin >> quantity;

    // Χρήση `find_if` για αναζήτηση προϊόντος με βάση τον τίτλο.
    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title; // Λάμβανει ως όρισμα ένα lambda για τον τίτλο
    });

    if (it != products.end()) { // Αν το προϊόν βρεθεί
        if (quantity <= it->getQuantity()) { // Επαρκές απόθεμα
            cart.addItem(it->getTitle(), quantity, it->getPrice()); // Προσθήκη στο καλάθι
        } else { // Μη επαρκές απόθεμα
            cout << "Not enough stock available. Adding all available quantity.\n";
            cart.addItem(it->getTitle(), it->getQuantity(), it->getPrice());
        }
    } else {
        cout << "Product not found.\n";
    }
}

// Αφαίρεση προϊόντος από το καλάθι
// - Εντοπίζει το προϊόν στο καλάθι με βάση τον τίτλο και το αφαιρεί.
void Customer::removeFromCart(vector<Product>& products) {
    string title;

    cout << "Enter product title to remove: ";
    cin.ignore();
    getline(cin, title);

    // Χρήση `find_if` για αναζήτηση προϊόντος με βάση τον τίτλο
    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it != products.end()) {
        double price = it->getPrice();
        cart.removeItem(title, price); // Αφαίρεση προϊόντος από το καλάθι
    } else {
        cout << "Product not found.\n";
    }
}

// Ενημέρωση ποσότητας προϊόντος στο καλάθι
// - Ενημερώνει την ποσότητα ενός προϊόντος στο καλάθι εφόσον υπάρχει.
void Customer::updateCart(const vector<Product>& products) {
    string title;
    int quantity;

    cout << "Enter product title to update: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter new quantity: ";
    cin >> quantity;

    // Χρήση `find_if` για εντοπισμό προϊόντος
    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it != products.end()) {
        cart.updateItem(it->getTitle(), quantity, it->getPrice(), it->getQuantity()); // Ενημέρωση ποσότητας
    } else {
        cout << "Product not found.\n";
    }
}

// Ολοκλήρωση παραγγελίας
// - Ενημερώνει το ιστορικό παραγγελιών του χρήστη.
// - Ενημερώνει το απόθεμα προϊόντων και αδειάζει το καλάθι.
void Customer::completeOrder(vector<Product>& products, const string& fileName) {
    string historyFileName = "files/order_history/" + username + "_history.txt";

    // Υπολογισμός του αριθμού των παραγγελιών από το ιστορικό
    ifstream historyFileInput(historyFileName);
    int cartCount = 0;
    string line;

    if (historyFileInput.is_open()) {
        while (getline(historyFileInput, line)) {
            if (line.find("Total Cost: ") != string::npos) {
                cartCount++;
            }
        }
        historyFileInput.close();
    }

    // Ενημέρωση του αποθέματος προϊόντων με βάση το καλάθι
    for (auto& item : cart.getItems()) {
        auto it = find_if(products.begin(), products.end(), [&item](const Product& product) {
            return product.getTitle() == item.first;
        });
        if (it != products.end()) {
            double newQuantity = it->getQuantity() - item.second; // Μείωση αποθέματος
            it->setQuantity(newQuantity > 0 ? newQuantity : 0);
        }
    }

    // Αποθήκευση της παραγγελίας στο ιστορικό
    ofstream historyFile(historyFileName, ios::app);
    if (!historyFile.is_open()) {
        cerr << "Error: Could not open " << historyFileName << " for writing.\n";
        return;
    }

    stringstream ss;
    ss << "\n\n---CART " << cartCount + 1 << " START---\n";
    for (const auto& item : cart.getItems()) {
        ss << item.second << " " << item.first << "\n";
    }
    ss << "---CART " << cartCount + 1 << " END---\n";
    ss << "Total Cost: " << fixed << setprecision(2) << cart.getTotalCost();

    cart.clearCart(); // Αδειάζει το καλάθι
    historyFile << ss.str();
    historyFile.close();

    // Ενημέρωση του αρχείου προϊόντων
    ofstream productFile(fileName, ios::trunc);
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
        if (++it != products.end()) {
            productFile << "\n";
        }
    }
    productFile.close();
    cout << "Order completed successfully and inventory updated.\n";
}

// Προβολή περιεχομένου καλαθιού
// - Εμφανίζει τα προϊόντα και τις ποσότητές τους στο καλάθι.
void Customer::viewCart() const {
    cart.displayCart();
}

// Προβολή ιστορικού παραγγελιών
// - Διαβάζει το αρχείο ιστορικού και εμφανίζει τις καταγεγραμμένες παραγγελίες.
void Customer::viewOrderHistory() const {
    string historyFileName = "files/order_history/" + username + "_history.txt";

    ifstream historyFile(historyFileName);
    if (!historyFile.is_open()) {
        cerr << "Error: Could not open " << historyFileName << " for writing.\n";
        return;
    }

    cout << "---Order History---\n";
    string line;
    while (getline(historyFile, line)) {
        cout << line << endl;
    }
    historyFile.close();
}

// Εμφάνιση μενού πελάτη
// - Επιτρέπει στον πελάτη να αλληλεπιδράσει με το καλάθι, τα προϊόντα και το ιστορικό του.
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
