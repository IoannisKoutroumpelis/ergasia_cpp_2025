#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
using namespace std;

// Κλάση Product: Αντιπροσωπεύει ένα προϊόν
class Product {
private:
    string title;         // Τίτλος του προϊόντος
    string description;   // Περιγραφή του προϊόντος
    string category;      // Κατηγορία του προϊόντος
    string subCategory;   // Υποκατηγορία του προϊόντος
    double price;         // Τιμή ανά μονάδα
    string unit;          // Μονάδα μέτρησης (Kg, Unit)
    int quantity;         // Διαθέσιμη ποσότητα

public:
    // Constructor: Αρχικοποιεί το προϊόν με προκαθορισμένες ή παρεχόμενες τιμές
    Product(const string& title = "", const string& description = "",
            const string& category = "", const string& subCategory = "",
            double price = 0.0, const string& unit = "", int quantity = 0.0);

    // Getters: Επιστρέφουν τις τιμές των χαρακτηριστικών
    // Χρησιμοποιούν const για να διασφαλίσουν ότι δεν τροποποιούν το αντικείμενο
    string getTitle() const;
    string getDescription() const;
    string getCategory() const;
    string getSubCategory() const;
    double getPrice() const;
    string getUnit() const;
    int getQuantity() const;

    // Setters: Ενημερώνουν τις τιμές των χαρακτηριστικών
    void setTitle(const string& newTitle);
    void setDescription(const string& newDescription);
    void setCategory(const string& newCategory);
    void setSubCategory(const string& newSubCategory);
    void setPrice(double newPrice);
    void setQuantity(int newQuantity);

    // Υπερφορτωμένοι τελεστές εισόδου/εξόδου
    // - operator<<: Εξάγει τις ιδιότητες του προϊόντος σε ένα stream
    // - operator>>: Εισάγει τις ιδιότητες του προϊόντος από ένα stream
    friend ostream& operator<<(ostream& os, const Product& product);
    friend istream& operator>>(istream& is, Product& product);

    // Εμφάνιση χαρακτηριστικών προϊόντος
    // Εμφανίζει τα χαρακτηριστικά του προϊόντος σε μορφοποιημένη έξοδο
    void displayProduct() const;
};

#endif
