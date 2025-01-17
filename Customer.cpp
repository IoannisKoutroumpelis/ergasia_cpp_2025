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

// Αναζητά προϊόντα με βάση τίτλο, κατηγορία ή συνδυασμό αυτών
void Customer::searchProducts(const vector<Product>& products, const vector<string>& categories) const {
    int choice;
    do {
        cout << "1. Search by title\n";
        cout << "2. Search by category\n";
        cout << "3. Search by title and category\n";
        cout << "4. View all products\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        // Αναζήτηση προϊόντων ανάλογα με την επιλογή του χρήστη
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
            string category;
            do {
                cout << "Select Category: ";
                getline(cin, category);
            } while (category != "Food" && category != "Drink" && category != "Clothing" && category != "Book" && category != "Tech");

            cout << "Do you want to search by Subcategory as well? [Y/N]: ";
            string choice2;
            cin >> choice2;
            if (choice2 == "y") {
                string subCategory;
                if (category == "Food") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Fruit" && subCategory != "Vegetable" && subCategory != "Meat" && subCategory != "Seafood" && subCategory != "Dairy" && subCategory != "Sweet" && subCategory != "Baked");
                } else if (category == "Drink") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Juice" && subCategory != "Soft Drink" && subCategory != "Coffee" && subCategory != "Tea" && subCategory != "Dairy" && subCategory != "Alcohol");
                } else if (category == "Clothing") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Shirt" && subCategory != "Pant" && subCategory != "Hat" && subCategory != "Shoe");
                } else if (category == "Book") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Mystery" && subCategory != "Sci-Fi" && subCategory != "Romance" && subCategory != "Comedy" && subCategory != "Academic" && subCategory != "Comic");
                } else {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Computer" && subCategory != "Laptop" && subCategory != "Phone" && subCategory != "Tablet");
                }
                for (const auto& product : products) {
                    if (product.getSubCategory().find(subCategory) != string::npos) {
                        product.displayProduct();
                    }
                }
            } else {
                for (const auto& product : products) {
                    if (product.getCategory().find(category) != string::npos) {
                        product.displayProduct();
                    }
                }
            }
        } else if (choice == 3) {
            string title;
            cout << "Enter product title: ";
            getline(cin, title);

            cout << "Available categories:\n";
            for (size_t i = 0; i < categories.size(); ++i) {
                cout << i + 1 << ". " << categories[i] << endl;
            }
            string category;
            do {
                cout << "Select Category: ";
                getline(cin, category);
            } while (category != "Food" && category != "Drink" && category != "Clothing" && category != "Book" && category != "Tech");
            cout << "Do you want to search by Subcategory as well? [Y/N]: ";
            string choice2;
            cin >> choice2;
            if (choice2 == "y") {
                string subCategory;
                if (category == "Food") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Fruit" && subCategory != "Vegetable" && subCategory != "Meat" && subCategory != "Seafood" && subCategory != "Dairy" && subCategory != "Sweet" && subCategory != "Baked");
                } else if (category == "Drink") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Juice" && subCategory != "Soft Drink" && subCategory != "Coffee" && subCategory != "Tea" && subCategory != "Dairy" && subCategory != "Alcohol");
                } else if (category == "Clothing") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Shirt" && subCategory != "Pant" && subCategory != "Hat" && subCategory != "Shoe");
                } else if (category == "Book") {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Mystery" && subCategory != "Sci-Fi" && subCategory != "Romance" && subCategory != "Comedy" && subCategory != "Academic" && subCategory != "Comic");
                } else {
                    do {
                        cout << "Give subcategory: ";
                        getline(cin, subCategory);
                    } while (subCategory != "Computer" && subCategory != "Laptop" && subCategory != "Phone" && subCategory != "Tablet");
                }
                for (const auto& product : products) {
                    if (product.getTitle().find(title) != string::npos &&
                        product.getSubCategory().find(subCategory) != string::npos) {
                        product.displayProduct();
                    }
                }
            } else {
                for (const auto& product : products) {
                    if (product.getTitle().find(title) != string::npos &&
                        product.getCategory().find(category) != string::npos) {
                        product.displayProduct();
                    }
                }
            }
        } else if (choice == 4) {
            // Προβάλλει όλα τα προϊόντα
            for (const auto& product : products) {
                product.displayProduct();
            }
        } else {
            // Εμφάνιση μηνύματος για μη έγκυρη επιλογή
            cout << "Invalid choice. Please try again.\n";
        }
    } while(choice < 1 || choice > 4);
}

// Προσθήκη προϊόντος στο καλάθι
// - Ελέγχει τη διαθεσιμότητα προϊόντος στη λίστα products.
// - Αν το προϊόν βρεθεί και υπάρχει επαρκές απόθεμα, το προσθέτει στο καλάθι.
void Customer::addToCart(const vector<Product>& products) {
    string title;
    int quantity;

    cout << "Enter product title to add: ";
    cin.ignore();
    getline(cin, title);

    cout << "Enter quantity: ";
    cin >> quantity;

    // Χρήση find_if για αναζήτηση προϊόντος με βάση τον τίτλο.
    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it != products.end()) { // Αν το προϊόν βρεθεί
        if (quantity <= it->getQuantity()) { // Επαρκές απόθεμα
            cart.addItem(it->getTitle(), quantity, it->getPrice()); // Προσθήκη στο καλάθι
        } else if (it->getQuantity() > 0){ // Μη επαρκές απόθεμα, αλλά όχι μηδενικό
            cout << "Not enough stock available. Adding all available quantity.\n";
            cart.addItem(it->getTitle(), it->getQuantity(), it->getPrice());
        } else { // Μηδενικό απόθεμα
            cout << "No stock available.\n";
        }
    } else { // Αν το προϊόν δεν βρεθεί
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

    // Χρήση find_if για αναζήτηση προϊόντος με βάση τον τίτλο
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

    // Χρήση find_if για εντοπισμό προϊόντος με βάση τον τίτλο
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

    ifstream historyFileInput(historyFileName);
    int cartCount = 0;
    string line;

    // Υπολογισμός του αριθμού των παραγγελιών από το ιστορικό
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
void Customer::displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName) {
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
            case 1:
                searchProducts(products, categories);
                break;
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