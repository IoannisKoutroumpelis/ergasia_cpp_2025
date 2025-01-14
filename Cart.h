#include <vector>
#include <string>
using namespace std;

class Cart {
private:
    vector<pair<string, int>> items;
    double totalCost;

public:
    Cart();

    void addItem(const string& title, double quantity, double price);
    void removeItem(const string& title);
    void updateItem(const string& title, double newQuantity, double price, double availableQuantity);
    void displayCart() const;
    double getTotalCost() const;
    void clearCart();
    vector<pair<string, int>> getItems() const;
};