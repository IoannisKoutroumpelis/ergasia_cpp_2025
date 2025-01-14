#include "Trim.h"
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// Συνάρτηση trim για αφαίρεση κενών
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) {
        return ""; // Αν το string είναι μόνο κενά, επιστρέφουμε κενό string
    }

    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}