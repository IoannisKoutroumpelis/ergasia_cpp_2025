#include "Admin.h"
#include "Trim.h"
#include <iostream>
//#include <map>
//#include <vector>
//#include <experimental/filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
//namespace fs = std::experimental::filesystem; // Εναλλακτικό namespace
using namespace std;

// Προσθήκη νέου προϊόντος
void Admin::addProduct(vector<Product>& products, const vector<string>& categories, const string& fileName) {
    string title, description, category, subCategory, unit;
    double price;
    int quantity;

    cout << "Give product title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Give product description: ";
    getline(cin, description);
    
    do {
        cout << "Give one of the following categories:\n";
        for (size_t i = 0; i < categories.size(); ++i) {
            cout << i + 1 << ". " << categories[i] << endl;
        }
        getline(cin, category);
    } while (category != "Food" || category != "Drink" || category != "Clothing" || category != "Book" || category != "Tech");

    cout << "Give subcategory: ";
    getline(cin, subCategory);

    do {
        cout << "Give product price: ";
        cin >> price;
    } while (price < 0);

    do {
        cout << "Give measurement type[Kg/Unit]: ";
        cin >> unit;
    } while (unit != "Kg" || unit != "Unit");

    do {
        cout << "Give amount of " << unit << ": ";
        cin >> quantity;
    } while (quantity < 0);

    products.emplace_back(title, description, category, subCategory, price, unit, quantity);

    // Ενημέρωση του αρχείου προϊόντων
    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }
    file << endl << title << " @ " << description << " @ " << category << " @ " << subCategory << " @ " 
         << fixed << setprecision(2)  << price << " @ " << unit << " @ " << fixed << setprecision(0) << quantity;
    file.close();

    cout << "Product added successfully!\n";
}

// Επεξεργασία προϊόντος
void Admin::editProduct(vector<Product>& products, const string& fileName) {
    string title;
    cout << "Enter product title to edit: ";
    cin.ignore();
    getline(cin, title);
    title = trim(title);


    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it == products.end()) {
        cout << "Product not found.\n";
        return;
    }

    Product& product = *it;
    int choice;
    while (true) {
        cout << "Enter number of field you want to edit: 1. Title 2. Description 3. Category and Subcategory 4. Price 5. Quantity 6. Nothing\n";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, try again.\n";
            continue;
        }
        break;
    }

    cin.ignore(); // Clear the input buffer for getline

    switch (choice) {
        case 1: {
            cout << "Enter new Title: ";
            string newTitle;
            getline(cin, newTitle);
            product.setTitle(trim(newTitle));
            break;
        }
        case 2: {
            cout << "Enter new Description: ";
            string newDescription;
            getline(cin, newDescription);
            product.setDescription(trim(newDescription));
            break;
        }
        case 3: {
            cout << "Enter new Category: ";
            string newCategory;
            getline(cin, newCategory);
            product.setCategory(trim(newCategory));
            cout << "Enter new Subcategory: ";
            string newSubcategory;
            getline(cin, newSubcategory);
            product.setSubCategory(trim(newSubcategory));
            break;
        }
        case 4: {
            cout << "Enter new Price: ";
            double newPrice;
            cin >> newPrice;
            if (cin.fail() || newPrice < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid price.\n";
            } 
            else {
                product.setPrice(newPrice);
            }
            break;
        }
        case 5: {
            cout << "Enter new Quantity: ";
            int newQuantity;
            cin >> newQuantity;
            if (cin.fail() || newQuantity < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid quantity.\n";
                } 
            else {
                product.setQuantity(newQuantity);
            }
            break;
        }
        default:
        return;
    }    
    // Ενημέρωση αρχείου
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }
    for (size_t i = 0; i < products.size(); i++) {
        const auto& product = products[i];
        file << product.getTitle() << " @ " << product.getDescription() << " @ " << product.getCategory() << " @ " 
             << product.getSubCategory() << " @ " << fixed << setprecision(2) << product.getPrice() << " @ "<< fixed << setprecision(0) << product.getUnit() << " @ " 
             << product.getQuantity();
    // Προσθήκη νέας γραμμής εκτός από την τελευταία εγγραφή
        if (i < products.size() - 1) {
            file << endl;
        }
    }
    file.close();

    cout << "Product updated successfully.\n";
}

void Admin::removeProduct(vector<Product>& products, const string& fileName) {
    string title;
    cout << "Enter product title to remove: ";
    cin.ignore();
    getline(cin, title);

    auto it = find_if(products.begin(), products.end(), [&title](const Product& p) {
        return p.getTitle() == title;
    });

    if (it == products.end()) {
        cout << "Product not found.\n";
        return;
    }

    // Remove the product from the vector
    products.erase(it);

    // Update the file with the remaining products
    ofstream file(fileName, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }

    for (const auto& product : products) {
        file << product.getTitle() << " @ " << product.getDescription() << " @ "
             << product.getCategory() << " @ " << product.getSubCategory() << " @ "
             << fixed << setprecision(2) << product.getPrice() << " @ " << product.getUnit() << " @ "
             << fixed << setprecision(0) << product.getQuantity() << endl;
    }

    file.close();

    cout << "Product removed successfully.\n";
}

void Admin::searchProducts(const vector<Product>& products, const vector<string>& categories) const {
    cout << "1. Search by title\n";
    cout << "2. Search by category\n";
    cout << "3. Search by title and category\n";
    cout << "4. View all products\n";
    cout << "Enter your choice: ";

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
        cin.ignore();

        if (catChoice < 1 || static_cast<size_t>(catChoice) > categories.size()) {
            cout << "Invalid category.\n";
            return;
        }

        string selectedCategory = categories[catChoice - 1];
        for (const auto& product : products) {
            if (product.getCategory().find(selectedCategory) != string::npos) {
                product.displayProduct();
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

        int catChoice;
        cout << "Select category (number): ";
        cin >> catChoice;
        cin.ignore();

        if (catChoice < 1 || static_cast<size_t>(catChoice) > categories.size()) {
            cout << "Invalid category.\n";
            return;
        }

        string selectedCategory = categories[catChoice - 1];
        for (const auto& product : products) {
            if (product.getTitle().find(title) != string::npos &&
                product.getCategory().find(selectedCategory) != string::npos) {
                product.displayProduct();
            }
        }
    } else if (choice == 4) {
        for (const auto& product : products) {
            product.displayProduct();
        }
    } else {
        cout << "Invalid choice. Please try again.\n";
    }
}

void Admin::unavailableProducts() const {
    const string productsFilePath = "files/products.txt"; // Σταθερή διαδρομή για το αρχείο προϊόντων

    ifstream productsFile(productsFilePath);
    if (!productsFile.is_open()) {
        cerr << "Error: Could not open " << productsFilePath << endl;
        return;
    }

    string line;
    cout << "Unavailable Products:\n";
    bool found = false;

    while (getline(productsFile, line)) {
        size_t lastSeparator = line.find_last_of('@');
        if (lastSeparator == string::npos) continue;

        string quantityStr = line.substr(lastSeparator + 1);
        double quantity = stod(quantityStr);

        if (quantity == 0) {
            size_t titleSeparator = line.find('@');
            if (titleSeparator != string::npos) {
                string title = line.substr(0, titleSeparator);
                cout << "- " << title << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "All products are available.\n";
    }

    productsFile.close();
}

void Admin::top5Products(const vector<Product>& products) const {
   /* const string orderHistoryPath = "files/order_history/";
    map<string, int> productCount;

    for (const auto& entry : fs::directory_iterator(orderHistoryPath)) {
        if (fs::is_regular_file(entry) && entry.path().extension() == ".txt") {
            ifstream historyFile(entry.path());
            if (!historyFile.is_open()) {
                cerr << "Error: Could not open " << entry.path() << endl;
                continue;
            }

            string line;
            while (getline(historyFile, line)) {
                if (!line.empty() && isdigit(line[0])) {
                    size_t spacePos = line.find(' ');
                    if (spacePos != string::npos) {
                        string title = line.substr(spacePos + 1);
                        productCount[title]++;
                    }
                }
            }
            historyFile.close();
        }
    }

    vector<pair<string, int>> sortedProducts(productCount.begin(), productCount.end());
    sort(sortedProducts.begin(), sortedProducts.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second > a.second;
    });

    cout << "Top 5 Most Popular Products:\n";
    for (size_t i = 0; i < min(sortedProducts.size(), size_t(5)); ++i) {
        cout << i + 1 << ". " << sortedProducts[i].first << " - " << sortedProducts[i].second << " times\n";
    }*/
}

void Admin::displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName) {
    int choice;
    do {
        cout << "---Admin Menu---\n";
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
            case 3:
                removeProduct(products, fileName);
                break;
            case 4:
                searchProducts(products, categories);
                break;
            case 5:
                unavailableProducts();
                break;
            case 6:
                top5Products(products);
                break;
            case 7:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 7);
}