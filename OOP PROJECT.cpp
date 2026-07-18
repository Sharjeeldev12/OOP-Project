#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//------------------------------------- Abstract Class
class CategoryBase {
public:
    virtual string getCategoryName() = 0;
};

class Vegetarian : public CategoryBase {
public:
    string getCategoryName() override {
        return "Vegetarian";
    }
};

class Vegan : public CategoryBase {
public:
    string getCategoryName() override {
        return "Vegan";
    }
};

class GlutenFree : public CategoryBase {
public:
    string getCategoryName() override {
        return "Gluten-Free";
    }
};
class Drinks : public CategoryBase {
public:
    string getCategoryName() override {
        return "Drinks";
    }
};

// Get category name based on an integer value
string getCategoryName(int category) {
    switch (category) {
        case 1: return Vegetarian().getCategoryName();
        case 2: return Vegan().getCategoryName();
        case 3: return GlutenFree().getCategoryName();
        case 4: return Drinks().getCategoryName(); 
        default: return "Unknown";
    }
}


//-------------------------------------- Menuitems Class
class Menuitems {
    int category;
    float price;
    int available;
    int sales;
    char name[100];

public:
    Menuitems() {
        category = 0;
        price = 0.0;
        available = 0;
        sales = 0;
        name[0] = '\0'; 
    }

    void inputDetails(const char* itemName) {
    strcpy(name, itemName);  // Assign the name directly
    cout << "Select category:" << endl;
    cout << "1: Vegetarian" << endl;
    cout << "2: Vegan" << endl;
    cout << "3: Gluten-Free" << endl;
    cout << "4: Drinks" << endl; 
    cin >> category;

    cout << "Enter price: ";
    cin >> price;

    cout << "Enter available quantity: ";
    cin >> available;

    sales = 0;  // Set initial sales to zero
}

    void displayDetails() const {
    cout << name << " - $" << price << " (available " << available << ")" << endl;
}



    bool isMatch(const char* searchName) const {
        return strcmp(name, searchName) == 0;
    }

   void modifyDetails() {
    cout << "Enter new price: ";
    cin >> price;

    cout << "Enter new available quantity: ";
    cin >> available;
}


    void saveToFile(ofstream& outFile) const {
        outFile << name << '\n' << category << '\n' << price << '\n' << available << '\n' << sales << '\n';
    }

    bool loadFromFile(ifstream& inFile) {
        if (!inFile.getline(name, 50)) return false; // Read name
        inFile >> category >> price >> available >> sales;
        inFile.ignore(); // Ignore trailing newline
        return true;
    }

    int getCategory() const {
        return category;
    }

    bool isAvailable() const {
        return available;
    }

    float getPrice() const {
        return price;
    }
    int getSales() const {
    return sales;
    }

    const char* getName() const {
    return name;
    }


    void increaseSales(int quantity) {
        sales += quantity;
    }
};

// ------------------------------------- MenuManager Class
class MenuManager {
    Menuitems menu[100];
    int itemCount=0;

public:
    MenuManager(){
        loadMenuFromFile();
    }

    void menuManagement() {
    int choice;
    do {
        cout << "\nMenu Management System" << endl;
        cout << "1. Add Menu Item" << endl;
        cout << "2. Display Menu by Category" << endl;
        cout << "3. Modify Menu Item" << endl;
        cout << "4. Remove Menu Item" << endl;
        cout << "5. Display Total Sales" << endl; 
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
			addMenuItem(); 
			break;
            case 2: 
			displayMenuByCategory();
			 break;
            case 3: 
			modifyMenuItem(); 
			break;
            case 4: 
			removeMenuItem(); 
			break;
            case 5: 
			displayTotalSales(); 
			break; 
            case 6: 
			break;
            default: 
			cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);
}


    void addMenuItem() {
    if (itemCount < 100) {
        char tempName[50];
        cout << "Enter item name: ";
        cin.ignore();
        cin.getline(tempName, 50);

        // Check for duplicate name
        for (int i = 0; i < itemCount; i++) {
            if (menu[i].isMatch(tempName)) {
                cout << "Error: Duplicate item name. Please use a unique name." << endl;
                return;
            }
        }

        // Now call inputDetails to fill the rest of the details
        menu[itemCount].inputDetails(tempName); // Pass the name as a parameter
        itemCount++;
        saveMenuToFile();
    } else {
        cout << "Menu is full! Cannot add more items." << endl;
    }
    system("cls");  // Clear the screen
}

    void displayMenuByCategory() const {
    int category;
    cout << "Select category to display:" << endl;
    cout << "1: Vegetarian" << endl;
    cout << "2: Vegan" << endl;
    cout << "3: Gluten-Free" << endl;
    cout << "4: Drinks" << endl;  
    cout << "Enter your choice: ";
    cin >> category;

    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (menu[i].getCategory() == category) {
            menu[i].displayDetails();
            found = true;
        }
    }

    if (!found) {
        cout << "No items found in the selected category." << endl;
    }
}

    void modifyMenuItem() {
    cout << "\n---- Full Menu ----" << endl;
    displayFullMenu();  // Show the full menu before modifying
    
    char itemName[50];
    cout << "Enter the item name to modify: ";
    cin.ignore();  // Clear the buffer before using getline
    cin.getline(itemName, 50);

    bool found = false;
    for (int i = 0; i < itemCount; i++) {
        if (menu[i].isMatch(itemName)) {
            menu[i].modifyDetails();
            found = true;
            saveMenuToFile();
            break;
        }
    }

    if (!found) {
        cout << "Item not found." << endl;
    }
    cout << "\nPress any key to continue...";
    cin.get();  // Wait for user to press a key
    system("cls");  // Clear the screen
}

    void displayFullMenu() const {
    if (itemCount == 0) {
        cout << "No items in the menu." << endl;
    } else {
        cout << "---- Menu ----" << endl;
        for (int i = 0; i < itemCount; i++) {
            menu[i].displayDetails();
        }
    }
}


    bool updateSales(const char* itemName, int quantity, double& totalBill) {
    bool itemFound = false;
    for (int i = 0; i < itemCount; i++) {
        if (menu[i].isMatch(itemName) && menu[i].isAvailable()) {
            if (menu[i].getPrice() >= quantity) {  // Check sufficient quantity
                menu[i].increaseSales(quantity);
                totalBill += menu[i].getPrice() * quantity;
                itemFound = true;
            } else {
                cout << "Insufficient quantity available for " << itemName << "." << endl;
            }
            break;
        }
    }
    return itemFound;
}

    void removeMenuItem() {
        char itemName[50];
        cout << "Enter the name of the menu item to remove: ";
        cin.ignore();
        cin.getline(itemName, 50);

        bool found = false;
        for (int i = 0; i < itemCount; i++) {
            if (menu[i].isMatch(itemName)) {
                for (int j = i; j < itemCount - 1; j++) {
                    menu[j] = menu[j + 1];
                }
                itemCount--;
                saveMenuToFile();
                cout << " Menu item /"  << itemName << "/ removed successfully."<<endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Menu item not found."<<endl;
        }
    }
    void displayTotalSales() const {
    cout << "\nTotal Sales of Each Product:" << endl;
    for (int i = 0; i < itemCount; i++) {
        float totalSales = menu[i].getPrice() * menu[i].getSales();
        cout << menu[i].getName() << " (" 
             << getCategoryName(menu[i].getCategory()) << ")  $"
             << menu[i].getPrice() << "  (sales " 
             << menu[i].getSales() << ")  (sales price " 
             << totalSales << "$)" << endl;
    }
    cout << "\nPress any key to continue...";
    cin.ignore();  // To clear the newline character left by previous input
    cin.get();  // Wait for user input
    system("cls");
}

    void saveMenuToFile() const {
        ofstream outFile("menu.txt", ios::trunc);
        if (!outFile) {
            cout << "ErSSror: Could not open file for writing."<<endl;
            return;
        }

        for (int i = 0; i < itemCount; i++) {
            menu[i].saveToFile(outFile);
        }
    }

    void loadMenuFromFile() {
        ifstream inFile("menu.txt");
        if (!inFile) {
            cout << "No existing menu file found. Starting with an empty menu."<<endl;
            return;
        }

        while (inFile) {
            Menuitems item;
            if (item.loadFromFile(inFile)) {
                menu[itemCount++] = item;
            }
        }
    }
};

// ------------------------------------- Customer Class
class Customer {
    string name, contact;
    int dietaryPreference;
    int id, loyaltyPoints = 0;
    double totalSpending = 0;

public:
    Customer() {}

    Customer(int id, string name, string contact, int dietaryPreference)
    {
    	this->id=id;
    	this->name=name;
    	this->contact=contact;
    	this->dietaryPreference=dietaryPreference;
	}

    void recordOrder(double amount) {
        totalSpending += amount;
        loyaltyPoints += static_cast<int>(amount / 50);
    }

    void displayDetails() const {
        cout << "ID: " << id << endl<< "Name: " << name << endl<< "Contact: " << contact << endl<< "Diet: ";
        switch (dietaryPreference) {
            case 1: cout << "Vegetarian"; break;
            case 2: cout << "Vegan"; break;
            case 3: cout << "Gluten-Free"; break;
            default: cout << "Unknown"; break;
        }
        cout << endl<< "Spending: $" << totalSpending << endl<< "Loyalty Points: " << loyaltyPoints << endl;
    }

    int getId() const { return id; }
    int getLoyaltyPoints() const { return loyaltyPoints; }

    void useLoyaltyPoints(int points) {
        loyaltyPoints -= points;
    }

    void saveToFile(ofstream& outFile) const {
        outFile << id << " " << name << " " << contact << " " << dietaryPreference << " " << totalSpending << " " << loyaltyPoints << endl;
    }

    void loadFromFile(ifstream& inFile) {
        inFile >> id >> name >> contact >> dietaryPreference >> totalSpending >> loyaltyPoints;
    }
};

// ------------------------------------- Customer Registration Class
class CustomerRegistration {
public:
    void registerCustomer() {
        string name, contact;
        int diet;

        cout << "Enter customer name: ";
        cin.ignore(); 
        getline(cin, name);
        cout << "Enter contact details: ";
        getline(cin, contact);
        cout << "Enter dietary preference (1 for Vegetarian, 2 for Vegan, 3 for Gluten-Free): ";
        cin >> diet;

        // Determine unique customer ID
        ifstream inFile("customers.txt");
        int id = 1;
        if (inFile.is_open()) {
            Customer temp;
            while (inFile) {
                temp.loadFromFile(inFile);
                if (inFile) id = temp.getId() + 1;
            }
        }
        inFile.close();

        // Create new customer
        Customer newCustomer(id, name, contact, diet);

        // Append the new customer to the file
        ofstream outFile("customers.txt", ios::app);
        if (outFile.is_open()) {
            newCustomer.saveToFile(outFile);
            outFile.close();
            cout << "Customer registered successfully! ID: " << id << endl;
        } else {
            cout << "Error: Could not open file for writing." << endl;
        }

        // Pause before returning to the menu
        cout << "\nPress any key to continue...";
        cin.ignore();  
        cin.get();  
        system("cls");  // Clear screen
    }

    void displayCustomerDetails() {
        int id;
        cout << "Enter customer ID to view details: ";
        cin >> id;

        ifstream inFile("customers.txt");
        bool found = false;
        if (inFile.is_open()) {
            while (inFile) {
                Customer temp;
                temp.loadFromFile(inFile);
                if (temp.getId() == id) {
                    temp.displayDetails();
                    found = true;
                    break;
                }
            }
            inFile.close();
        } else {
            cout << "Error: Could not open file for reading." << endl;
            return;
        }

        if (!found) {
            cout << "Customer with ID " << id << " not found." << endl;
        }

        // Pause before returning to the menu
        cout << "\nPress any key to continue...";
        cin.ignore();  
        cin.get();  
        system("cls");  // Clear screen
    }

    void removeCustomer() {
        int customerId;
        cout << "Enter the ID of the customer to remove: ";
        cin >> customerId;

        ifstream inFile("customers.txt");
        ofstream outFile("temp.txt");

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Error: Could not open files." << endl;
            return;
        }

        bool found = false;
        while (inFile) {
            Customer temp;
            temp.loadFromFile(inFile);
            if (inFile) {
                if (temp.getId() == customerId) {
                    found = true;
                } else {
                    temp.saveToFile(outFile);
                }
            }
        }

        inFile.close();
        outFile.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");

        if (found) {
            cout << "Customer with ID " << customerId << " removed successfully." << endl;
        } else {
            cout << "Customer not found." << endl;
        }

        // Pause before returning to the menu
        cout << "\nPress any key to continue...";
        cin.ignore();  
        cin.get();  
        system("cls");  // Clear screen
    }

    void CustomerRegister() {
        int choice;
        do {
            cout << endl << "Customer Management System" << endl;
            cout << "1. Register Customer" << endl;
            cout << "2. Display Customer Details" << endl;
            cout << "3. Remove Customer" << endl;
            cout << "4. Return to main menu" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: 
				registerCustomer(); 
				break;
                case 2: 
				displayCustomerDetails(); 
				break;
                case 3: 
				removeCustomer(); 
				break;
                case 4: 
				cout << "Exiting..." << endl; 
				break;
                default: 
				cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 4);
    }
};

//------------------------------------- OrderTaking class
class OrderTaking {
public:
    void placeOrder(MenuManager& menuManager, CustomerRegistration& customerRegistration) {
        int customerId;
        cout << "Enter your Customer ID: ";
        cin >> customerId;

        Customer customer;
        if (!findCustomerById(customerId, customer)) {
            cout << "Customer not registered. Please register first."<< endl;
            customerRegistration.registerCustomer();
            return;
        }

        cout << "Welcome, " << customerId << "!"<< endl;
        menuManager.displayMenuByCategory();

        vector<pair<string, int>> orders; // Stores item name and quantity
        char moreItems;
        do {
            string itemName;
            int quantity;
            cout << "Enter the name of the item you want to order: ";
            cin.ignore();
            getline(cin, itemName);

            cout << "Enter the quantity: ";
            cin >> quantity;

            orders.push_back({itemName, quantity});

            cout << "Do you want to order more items? (y/n): ";
            cin >> moreItems;
        } while (tolower(moreItems) == 'y');

        double totalBill = 0;
        for (const auto& order : orders) {
            if (menuManager.updateSales(order.first.c_str(), order.second, totalBill)) {
                cout << order.second << " x " << order.first << " added to your order."<< endl;
            } else {
                cout << "Item " << order.first << " not found or unavailable."<< endl;
            }
        }

        displayBillDetails(customer, orders, totalBill);
        updateCustomerFile(customer);
    }

    bool findCustomerById(int id, Customer& customer) {
        ifstream inFile("customers.txt");
        if (!inFile.is_open()) {
            cout << "Error: Could not open customer file."<< endl;
            return false;
        }

        while (inFile) {
            Customer temp;
            temp.loadFromFile(inFile);
            if (temp.getId() == id) {
                customer = temp;
                inFile.close();
                return true;
            }
        }

        inFile.close();
        return false;
    }

    void updateCustomerFile(const Customer& customer) {
        ifstream inFile("customers.txt");
        ofstream outFile("temp.txt");

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Error: Could not open files."<< endl;
            return;
        }

        while (inFile) {
            Customer temp;
            temp.loadFromFile(inFile);
            if (inFile) {
                if (temp.getId() == customer.getId()) {
                    customer.saveToFile(outFile);
                } else {
                    temp.saveToFile(outFile);
                }
            }
        }

        inFile.close();
        outFile.close();

        remove("customers.txt");
        rename("temp.txt", "customers.txt");
    }

    void displayBillDetails(Customer& customer, const vector<pair<string, int>>& orders, double& totalBill) {
    cout << endl<< "----- Bill Details -----"<< endl;
    cout << "Customer ID: " << customer.getId() << endl;
    cout << "Items Ordered:"<< endl;

    for (const auto& order : orders) {
        cout << order.first << " x " << order.second << endl;
    }

    cout << "Total Bill: $" << totalBill << endl;
    cout << "Available Loyalty Points: " << customer.getLoyaltyPoints()<< endl;

    char usePoints;
    cout << "Do you want to use loyalty points? (y/n): ";
    cin >> usePoints;

    if (tolower(usePoints) == 'y') {
        int pointsToUse;
		if (customer.getLoyaltyPoints() < static_cast<int>(totalBill)) {
	    	pointsToUse = customer.getLoyaltyPoints();
		} else {
    		pointsToUse = static_cast<int>(totalBill);
		}

        totalBill -= pointsToUse;
        customer.useLoyaltyPoints(pointsToUse);
        cout << "Loyalty points applied: " << pointsToUse << endl;
    }

    cout << "Final Bill: $" << totalBill << endl;
    customer.recordOrder(totalBill);

    // Pause for the user to view details
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

};


int main() {
    MenuManager menuManager;
    CustomerRegistration customerRegistration;
    OrderTaking orderTaking;

    int choice;

    do {
        system("cls");
        cout << "1. Modify Menu"<< endl;
        cout << "2. Customer Registration"<< endl;
        cout << "3. Place an Order"<< endl;
        cout << "4. Exit"<< endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                menuManager.menuManagement();
                break;
            case 2: 
                customerRegistration.CustomerRegister();
                break;
            case 3: {
                orderTaking.placeOrder(menuManager, customerRegistration);
                break;
            }
            case 4:
                cout << "Exiting program."<< endl;
                break;
            default:
                cout << "Invalid choice! Please try again."<< endl;
        }
    } while (choice != 4);
    return 0;
}