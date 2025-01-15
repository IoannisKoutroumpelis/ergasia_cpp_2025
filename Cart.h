#include <vector>
#include <string>
using namespace std;

class Cart {
private:
    vector<pair<string, int>> items;
    double totalCost;

public:
    Cart();

    void addItem(const string& title, int quantity, double price);
    void removeItem(const string& title, double price);
    void updateItem(const string& title, int newQuantity, double price, int availableQuantity);
    void displayCart() const;
    double getTotalCost() const;
    void clearCart();
    vector<pair<string, int>> getItems() const;
};