#include "Eshop.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <categories_file> <products_file> <users_file>\n";
        return 1;
    }

    Eshop shop(argv[1], argv[2], argv[3]);
    string choice;

    do {
        cout << "\nWelcome to the e-shop!!!\n";
        cout << "Do you want to login or register? (enter option):";
        cin >> choice;

        if(choice == "login") {
            shop.login();
        }
        else if(choice == "register") {
            shop.registerUser();
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}