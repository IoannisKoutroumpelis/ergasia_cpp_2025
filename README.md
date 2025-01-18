**Το παρόν αρχείο αποτελεί επεξήγηση του τρόπου λειτουργίας του E-Shop, καθώς και των επιλογών που πάρθηκαν για την υλοποίησή του. Παρακάτω παρατίθεται ο τρόπος χρήσης της κάθε κλάσης, καθώς και η λειτουργία των συναρτήσεων - μελών της.**
**Σημείωση: για να μην επηρεάζονται τα αρχεία στο repository της εργασίας, αποφασίσαμε, κάπου στα μισά της εργασίας, να δημιουργήσουμε ένα καινούριο, πλήρως πρόχειρο repository, στο οποίο να είμαστε άνετοι να "πειράζουμε" ότι θέλουμε και να μην χρειάζεται να είναι ιδιαίτερα "καλοφτιαγμένο". Αν επιθυμείτε να δείτε σε μεγαλύτερο βάθος την πορεία της εργασίας, μπορείτε να επισκευθείται το repository IoannisKoutroumpelis/ergasia_cpp_2025,"https://github.com/IoannisKoutroumpelis/ergasia_cpp_2025.git". Καθόλη τη διάρκεια της εργασίας το repository ήταν private, ωστόσο το κάναμε public, ώστε να έχετε και εσείς πρόσβαση.**

**OOP24**
Το oop24.cpp αποτελέι το αρχείο στο οποίο βρίσκεται η main συνάρτηση του προγράμματος, δέχεται 3 ορίσματα (<categories_file> <products_file> <users_file>), καλωσορίζει και ανακατευθύνει τον χρήστη, με βάση την επιθυμία του για εγγραφή (register) ή σύνδεση (login).

**Κλάσεις**
Το πρόγραμμα αποτελέιται από τις 6 ακόλουθες κλάσεις:
1) Eshop
2) User: Αποτελεί τη βασική κλάση για τις κλάσεις Admin και Customer
3) Admin: Παράγωγη κλάση της User
4) Customer: Παράγωγη κλάση της User
5) Product
6) Cart

**Κλάση Eshop**
Η κλάση Eshop υλοποιεί τις βασικές λειτουργίες του E-Shop, δηλαδή την σύνδεση/εγγραφή χρήστη και το διάβασμα των κατηγοριών, των προϊόντων και των χρηστών από τα αντίστοιχα αρχεία.
Συγκεκριμένα:
1. Μέσω των *void* συναρτήσεων *loadCategories()*, *loadProducts()* και *loadUsers()*, ανοίγει τα αρχεία categories.txt, products.txt και users.txt αντίστοιχα για ανάγνωση και αποθηκεύει τα δεδομένα τους σε vectors, ώστε να είναι ευκολότερα προσβάσιμα τα περιεχόμενά τους, κατά τη διάρκεια εκτέλεσης του προγράμματος.
2. Χρησιμοποιεί τις *void* συναρτήσεις *login()* και *registerUser()*, ώστε, σε περίπτωση σύνδεσης χρήστη, να επαληθεύει τα στοιχεία που έδωσε ο ίδιος και να τον ανακατευθύνει σε ένα menu λειτουργιών, με βάση την ιδιότητά του (user ή admin) και, σε περίπτωση εγγραφής χρήστη, να καταχωρεί τα στοιχεία του στο αρχείο users.txt και, στη συνέχεια, να τον ανακατευθείνει και πάλι στο αντίστοιχο menu, τον τρόπο λειτουργίας του οποίου θα εξετάσουμε παρακάτω.
3. Τέλος, μέσω των *void* συναρτήσεων *updateProductsFile()* και *updateUsersFile()*, δίνεται η δυνατότητα να ενημερώνονται τα αρχεία products.txt και users.txt αντίστοιχα, για προσθήκες, αλλαγές κλπ.

**Κλάση User**
Η κλάση User αποτελεί τη βασική κλάση για τους χρήστες. Περιέχει το username και το password του κάθε χρήστη, καθώς και τον αν είναι admin ή όχι. Επίσης, υλοποιεί 3 getters που επιστρέφουν username, password, και αν ο χρήστης είναι admin ή όχι.
Συγκεκριμένα:
Έχουν οριστεί οι παρακάτω Getters:
1. *string getUsername() const*: Επιστρέφει το όνομα χρήστη.
2. *string getPassword() const*: Επιστρέφει τον κωδικό πρόσβασης.
3. *bool getIsAdmin() const*: Επιστρέφει αν ο χρήστης είναι Admin (true) ή User(false).
Σημείωση: Οι συναρτήσεις είναι const, για να εξασφαλίζεται ότι δεν αλλάζουν τις τιμές των μεταβλητών.

**Κλάση Customer**
Η κλάση Customer είναι παράγωγη κλάση της User. Ο ρόλος της είναι να διαχειρίζεται τις λειτουργίες που σχετίζονται με τις αγορές προϊόντων, καθώς και ότι άλλο αφορά τους πελάτες.
Συγκεκριμένα:
1. Η συνάρτηση *void searchProducts(const vector<Product>& products, const vector<string>& categories) const* χρησιμοποιείται από τους πελάτες για να αναζητούν προϊόντα, με βάση τον τίτλο, την κατηγορία/υποκατηγορία του προϊόντος ή και τα δύο ταυτόχρονα.
2. Η συνάρτηση *void addToCart(const vector<Product>& products)* χρησιμοποιείται από τους πελάτες για να προσθέσουν κάποιο προϊόν στο καλάθι τους. Λαμβάνεται υπόψη η διαθεσιμότητα του προϊόντος και, αν αυτή είναι μικρότερη απο την επιθυμητή ποσότητα, αλλά όχι μηδενική, τότε προστίεθται όλη η διαθέσιμη ποσότητα στο καλάθι.
3. Η συνάρτηση *void removeFromCart(vector<Product>& products)* χρησιμοποιείται από τους πελάτες για να αφαιρέσουν κάποιο προϊόν από το καλάθι τους.
4. Η συνάρτηση *void updateCart(const vector<Product>& products)* χρησιμοποιείται από τους πελάτες για να αλλάξουν την ποσότητα κάποιου προϊόντος στο καλάθι τους.
5. Η συνάρτηση *void completeOrder(vector<Product>& products, const string& fileName)* χρησιμοποιείται από τους πελάτες για να ολοκληρώσουν την παραγγελία τους. Στη συνέχεια, αλλάζουν οι διαθέσιμες ποσότητες των προϊόντων στο αρχείο products.txt, με βάση τη παραγγελία του εκάστοτε πελάτη, καθώς, επίσης, καταγράφεται και η νέα του παραγγελία στο αρχείο <username>_history.txt.
6. Η συνάρτηση *void viewCart() const* χρησιμοποιείται από τους πελάτες για να δουν τα προϊόντα και τις ποσότητές τους που έχουν βάλει στο καλάθι τους.
7. Η συνάρτηση *void viewOrderHistory() const* χρησιμοποιείται από τους πελάτες για να εμφανιστεί το ιστορικό των παραγγελιών τους.
8. Τέλος, η συνάρτηση void displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName) εμφανίζει το menu λειτουργιών του πελάτη, από το οποίο ο ίδιος επιλέγει μια από τις παραπάνω λειτουργίες ή έξοδο.

**Κλάση Admin**
Η κλάση Admin είναι παράγωγη κλάση της User. Ο ρόλος της είναι να διαχειρίζεται τις λειτουργίες που σχετίζονται με τη διαχείριση προϊόντων, καθώς και ότι άλλο αφορά τους διαχειριστές.
Συγκεκριμένα:
1. Η συνάρτηση *void displayMenu(vector<Product>& products, const vector<string>& categories, const string& fileName)* εμφανίζει το menu λειτουργιών του διαχειριστή, από το οποίο ο ίδιος επιλέγει μια από τις παρακάτω λειτουργίες ή έξοδο.
2. Η συνάρτηση *void addProduct(vector<Product>& products, const vector<string>& categories, const string& fileName)* χρησιμοποιείται για να προστεθεί κάποιο προϊόν στη λίστα των διαθέσιμων προϊόντων. Στη συνέχεια, ενημερώνεται το αρχείο products.txt, στο οποίο προστίθεται το νέο προϊόν.
3. Η συνάρτηση *void removeProduct(vector<Product>& products, const string& fileName)* χρησιμοποιείται για να αφαιρεθεί κάποιο προϊόν από τη λίστα των διαθέσιμων προϊόντων. Στη συνέχεια, ενημερώνεται το αρχείο products.txt, από το οποίο αφαιρείται το εκάστοτε προϊόν.
4. Η συνάρτηση *void editProduct(vector<Product>& products, const string& fileName)* χρησιμοποιείται για να επεξεργαστεί ο διαχειριστής τα χαρακτηριστικά κάποιου προϊόντος (πχ αλλαγή περιγραφής, αλλαγή τιμής ή ποσότητας κλπ). Στη συνέχεια, ενημερώνεται το αρχείο products.txt, με τα νέα δεδομένα του εκάστοτε προϊόντος.
5. Η συνάρτηση *void searchProducts(const vector<Product>& products)* χρησιμοποιείται για την αναζήτηση κάποιου προϊόντος, με βάση τον τίτλο, την κατηγορία/υποκατηγορία του ή και τα δύο ταυτόχρονα.
6. Η συνάρτηση *void unavailableProducts(const vector<Product>& products)* εμφανίζει τα μη διαθέσιμα προϊόντα, δηλαδή αυτά που έχουν μηδενική ποσότητα.
7. Η συνάρτηση *void top5Products(const vector<Product>& products) const* εμφανίζει τα 5 πιο δημοφιλή προϊόντα, δηλαδή αυτά που έχουν υπάρξει στις περισσότερες παραγγελίες. Αυτό επιτυγχάνεται με προσπέλαση των αρχείων ιστορικού παραγγελιών κάθε χρήστη.

**Κλάση Product**
Κάθε προϊόν είναι ένα αντικείμενο της κλάσης Product.
Συγκεκριμένα:
Έχουν οριστεί οι παρακάτω Getters:
1. *string getTitle() const*: Επιστρέφει τον τίτλο του προϊόντος.
2. *string getDescription() const*: Επιστρέφει την περιγραφή του προϊόντος.
3. *string getCategory() const*: Επιστρέφει την κατηγορία του προϊόντος.
4. *string getSubCategory() const*: Επιστρέφει την υποκατηγορία του προϊόντος.
5. *double getPrice() const*: Επιστρέφει την τιμή του προϊόντος.
6. *string getUnit() const*: Επιστρέφει τη μονάδα μέτρησης του προϊόντος [Kg/Unit].
7. *int getQuantity() const*: Επιστρέφει την ποσότητα του προϊόντος.
Σημείωση: Οι συναρτήσεις είναι const, για να εξασφαλίζεται ότι δεν αλλάζουν τις τιμές των μεταβλητών.
Επίσης, έχουν οριστεί οι παρακάτω Setters:
1. *void setTitle(const string& newTitle)*: Αλλάζει τον τίτλο του προϊόντος.
2. *void setDescription(const string& newDescription)*: Αλλάζει την περιγραφή του προϊόντος.
3. *void setCategory(const string& newCategory)*: Αλλάζει την κατηγορία του προϊόντος.
4. *void setSubCategory(const string& newSubCategory)*: Αλλάζει την υποκατηγορία του προϊόντος.
5. *void setPrice(double newPrice)*: Αλλάζει την τιμή του προϊόντος.
6. *void setQuantity(int newQuantity)*: Αλλάζει την ποσότητα του προϊόντος.
Επιπλέον, έχουν οριστεί 2 Operators ως *friend*:
1. *friend ostream& operator<<(ostream& os, const Product& product)*: Υπερφόρτωση του τελεστή εξόδου (<<) [Εξάγει τις ιδιότητες ενός προϊόντος σε ένα stream].
2. *friend istream& operator>>(istream& is, Product& product)*: Υπερφόρτωση του τελεστή εισόδου (>>) [Εισάγει τις ιδιότητες ενός προϊόντος από ένα stream].
Τέλος, έχει οριστεί και η συνάρτηση *void displayProduct() const*, η οποία εμφανίζει τα χαρακτηριστικά ενός προϊόντος.

**Κλάση Cart**
Η κλάση Cart διαχειρίζεται το καλάθι ενός πελάτη.
Συγκεκριμένα:
1. Η συνάρτηση *void addItem(const string& title, int quantity, double price)* προσθέτει ένα προϊόν στο καλάθι του πελάτη.
2. Η συνάρτηση *void removeItem(const string& title, double price)* αφαιρεί ένα προϊόν από το καλάθι του πελάτη.
3. Η συνάρτηση *void updateItem(const string& title, int newQuantity, double price, int availableQuantity)* ενημερώνει την ποσότητα ενός προϊόντος στο καλάθι του πελάτη.
4. Η συνάρτηση *void displayCart() const* εμφανίζει το περιεχόμενο του καλαθιού.
5. Η συνάρτηση *double getTotalCost() const* επιστρέφει το συνολικό κόστος.
6. Η συνάρτηση *void clearCart()* αδειάζει το καλάθι.
7. Η συνάρτηση *vector<pair<string, int>> getItems() const* επιστρέφει τη λίστα των προϊόντων που υπάρχουν στο καλάθι.

**Συνάρτηση Trim**
Έχει υλοποιηθεί ακόμη μια συνάρτηση, που δεν ανήκει σε κάποια κλάση, η συνάρτηση αυτή είναι η *string trim(const string& str)*. Η συνάρτηση Trim δέχεται μια *const* αναφορά σε συμβολοσειρά (string) και την επιστρέφει αφαιρώντας τα κενά στην αρχή και στο τέλος της. Η Trim υλοποιήθηκε για να λύσει προβλήματα, όπως το ότι δεν μπορούσαν να βρεθούν προϊόντα ή τυπώνονταν με λάθος τρόπο στο αρχείο products.txt, λόγω ύπαρξης κενών στην αρχή και στο τέλος των στοιχείων τους.
