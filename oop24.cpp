#include "Eshop.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <categories_file> <products_file> <users_file>\n";
        return 1;
    }

    Eshop shop(argv[1], argv[2], argv[3]);
    string choice;

    do {
        cout << "\n---Eshop Main Menu---\n";
        cout << "1. Login\n2. Register\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == "login") {
            shop.login();
        }
        else if(choice == "register") {
            shop.registerUser();
        }
        else if(choice == "exit") {
            cout << "Exiting. Goodbye!\n";
            return 0;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}