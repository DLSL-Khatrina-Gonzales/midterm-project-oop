#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// Function to convert string to lowercase
string toLowerCase(const string &str) {
    string lowerStr = str;
    for (char &c : lowerStr) {
        c = tolower(c);
    }
    return lowerStr;
}

// Function to validate integer input (for quantity)
bool isValidInteger(const string& input) {
    for (char c : input) {
        if (!isdigit(c)) { // Ensure all characters are digits
            return false;
        }
    }
    return !input.empty(); // Return true if the string is not empty
}

// Function to validate float input (for price)
bool isValidFloat(const string& input) {
    bool hasDot = false;
    for (char c : input) {
        if (!isdigit(c)) {
            if (c == '.' && !hasDot) {
                hasDot = true; // Allow only one decimal point
            } else {
                return false; // Invalid if non-digit or more than one decimal point
            }
        }
    }
    return !input.empty(); // Return true if the string is not empty
}

void clearInput() {
    cin.clear();
    cin.ignore();
}

// Abstract base class for Items
class Item {
private:
    string id, name, category;
    int quantity;
    float price;

public:
    // Pure virtual function to enforce implementation in derived classes
    virtual void setItem(string itemId, string itemName, int itemQuantity, float itemPrice, string itemCategory) = 0;

    // Set item quantity with validation
    void setQuantity(int newQuantity) {
        if (newQuantity >= 0) {
            quantity = newQuantity;
        } else {
            cout << "Quantity cannot be negative!" << endl;
        }
    }

    // Set item price with validation
    void setPrice(float newPrice) {
        if (newPrice >= 0) {
            price = newPrice;
        } else {
            cout << "Price cannot be negative!" << endl;
        }
    }

    string getId() { return id; }
    string getName() { return name; }
    int getQuantity() { return quantity; }
    float getPrice() { return price; }
    string getCategory() { return category; }

    void updatePrice(float newPrice) {
        price = newPrice;
    }

    void updateQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    void setId(string itemId) { id = itemId; }
    void setName(string itemName) { name = itemName; }
    void setCategory(string itemCategory) { category = itemCategory; }
};

// Derived class for general Item
class GeneralItem : public Item {
public:
    void setItem(string itemId, string itemName, int itemQuantity, float itemPrice, string itemCategory) override {
        setId(itemId);
        setName(itemName);
        setQuantity(itemQuantity);
        setPrice(itemPrice);
        setCategory(itemCategory);
    }
};

class Inventory {
private:
    GeneralItem items[1000]; // Assuming a maximum of 1000 items
    int itemCount = 0;

public:
    Inventory() : itemCount(0) {}

    int getCategoryChoice() {
    cout << "\n1 - Clothing\n2 - Electronics\n3 - Entertainment\n4 - Return to Main Menu\n";
    string categoryChoiceInput; // Use a string to read input first
    cout << "\nEnter Category: ";
    cin >> categoryChoiceInput; // Read input as string

    // Validate the input before converting to integer
    if (!isValidInteger(categoryChoiceInput)) {
        cout << "\nInvalid input! Please enter a number." << endl;
        clearInput(); // Clear the input buffer
        return -1; // Return -1 to indicate invalid input
    }

    // Convert the valid string input to integer
    int categoryChoice = stoi(categoryChoiceInput); 

    // Validate the range of categoryChoice
    if (categoryChoice < 1 || categoryChoice > 4) {
        cout << "\nCategory " << categoryChoice << " does not exist! Please try again.\n";
        return -1; // Return -1 for invalid category choice
    }

    return categoryChoice; // Return the valid category choice
}

    void printItemHeader() {
        cout << "\n------------------------------------------------------------------------------------------------------------\n";
        cout << left << setw(20) << "ID" << setw(20) << "Name" << setw(20) << "Quantity" << setw(20) << "Price" << setw(20) << "Category" << endl;
        cout << "------------------------------------------------------------------------------------------------------------\n";
    }

    void addItem() {
        cout << "\n===================== Add Item =====================\n";
        int categoryChoice = getCategoryChoice();
        if (categoryChoice == 4) return; // Handle return to main menu

        string category;
        switch (categoryChoice) {
            case 1: category = "Clothing"; break;
            case 2: category = "Electronics"; break;
            case 3: category = "Entertainment"; break;
            default:
                cout << "Category " << categoryChoice << " does not exist! Please try again.\n";
            return;
        }

        string id, name, quantityInput, priceInput;
        int quantity;
        float price;

        cout << "Enter Item ID: ";
        clearInput(); 
        getline(cin, id);

        cout << "Enter Item Name: ";
        getline(cin, name);

        // Validate Item Quantity input (integer)
        cout << "Enter Item Quantity: ";  
        while (true) {
            getline(cin, quantityInput); // Read as string

            if (!isValidInteger(quantityInput)) {  // Invalid input
                cout << "Invalid input! Please enter a valid integer for quantity: ";
            } else {
                quantity = stoi(quantityInput); // Convert to integer
                if (quantity > 0) {
                    break; // Valid input, exit loop
                } else {
                cout << "Quantity must be greater than 0! Please enter again: ";
                }
            }
        }

        // Validate Item Price input (float)
        cout << "Enter Item Price: ";
        while (true) {
            getline(cin, priceInput); // Read as string

            if (!isValidFloat(priceInput)) { // Invalid input
                cout << "Invalid input! Please enter a valid price: ";
            } else {
                price = stof(priceInput); // Convert to float
                if (price > 0) {
                    break; // Valid input, exit loop
                } else {
                    cout << "Price must be greater than 0! Please enter again: ";
                }
            }
        }
    
        items[itemCount++].setItem(id, name, quantity, price, category);
        cout << "\nItem added successfully!\n";
    }

    void updateItem() {
        cout << "\n=================== Update Item ====================\n";

        string id;
        cout << "Enter Item ID to Update: ";
        cin >> id;
        id = toLowerCase(id); // Convert user input to lowercase

        for (int i = 0; i < itemCount; i++) {
            if (toLowerCase(items[i].getId()) == id) { // Compare in lowercase
                int choice;
                cout << "\nUpdate Information\n1 - Price\n2 - Quantity\n";
                cout << "\nEnter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    string newPriceInput;
                    float newPrice;

                    cout << "Enter new Price: ";
                    clearInput();
                    while (true) {
                    getline(cin, newPriceInput);

                        if (isValidFloat(newPriceInput)) {
                            newPrice = stof(newPriceInput); // Convert to float
                            if (newPrice > 0) break; // Ensure the price is positive
                            cout << "Price must be greater than 0! Please enter again: ";
                        } else {
                        cout << "Invalid input! Please enter a valid price: ";
                        }
                    }

                    float oldPrice = items[i].getPrice();
                    items[i].updatePrice(newPrice);

                    cout << "\nPrice of " << items[i].getName() << " is updated from " 
                        << fixed << setprecision(2) << oldPrice << " Php to " 
                        << fixed << setprecision(2) << newPrice << " Php.\n";
                
                } else if (choice == 2) {
                    string newQuantityInput;
                    int newQuantity;

                    cout << "Enter new Quantity: ";
                    while (true) {
                    getline(cin, newQuantityInput);

                        if (isValidInteger(newQuantityInput)) {
                            newQuantity = stoi(newQuantityInput); // Convert to integer
                            if (newQuantity > 0) break; // Ensure quantity is positive
                            cout << "Quantity must be greater than 0! Please enter again: ";
                        } else {
                            cout << "Invalid input! Please enter a valid quantity: ";
                        }
                    }

            int oldQuantity = items[i].getQuantity();
            items[i].updateQuantity(newQuantity);

            cout << "\nQuantity of " << items[i].getName() << " is updated from " 
                    << oldQuantity << " to " << newQuantity << ".\n";
            }

            // Prompt user to go back to the menu
            cout << "\nPress Enter to go back to the Menu...";
            clearInput();
            cin.get(); // Wait for Enter
            return;
        }
    }
        // If item not found
        cout << "\nItem ID not found!\n";
        cout << "\nPress Enter to go back to the Menu...";
        clearInput();
        cin.get(); // Wait for Enter
    }

    void removeItem() {
        cout << "\n==================== Remove Item ====================\n";

        string id;
        cout << "\nEnter Item ID to Remove: ";
        cin >> id;
        id = toLowerCase(id); // Convert user input to lowercase

        for (int i = 0; i < itemCount; i++) {
            if (toLowerCase(items[i].getId()) == id) { // Compare in lowercase
                cout << "\nItem " << items[i].getName() << " has been removed from the inventory.\n";
                for (int j = i; j < itemCount - 1; j++) {
                    items[j] = items[j + 1];
                }
                itemCount--;

                cout << "\nPress Enter to go back to the Menu...";
                clearInput();
                cin.get(); // Wait for user to press Enter
                return;
            }
        }
    
        // If item not found
        cout << "\nItem ID not found!\n";
        cout << "\nPress Enter to go back to the Menu...";
        clearInput();
        cin.get(); // Wait for user to press Enter
    }   

    void displayItemsByCategory() {
        cout << "\n============= Display Items by Category =============\n";
    
        string categoryInput;
        int categoryChoice;

        // Loop until valid input is received
        while (true) {
            categoryChoice = getCategoryChoice();

            if (categoryChoice == 4) {
            return; // Return to main menu
        }

        // Convert category choice to string to validate
        categoryInput = to_string(categoryChoice);
        if (isValidInteger(categoryInput) && categoryChoice >= 1 && categoryChoice <= 3) {
            break; // Valid input, exit loop
        } else {
            cout << "\nInvalid choice! Please enter a valid number between 1 and 3.\n";
        }
    }

        string category;
        switch (categoryChoice) {
            case 1:
                category = "Clothing";
                break;
            case 2:
                category = "Electronics";
                break;
            case 3:
                category = "Entertainment";
                break;
            default:
                cout << "\nCategory " << categoryChoice << " does not exist! Please try again.\n";
                cout << "\nPress Enter to go back to the Menu...";
                clearInput();
                cin.get();
                return;
            }

        cout << "\nDisplaying Items in Category: " << category << endl;
        printItemHeader();  // Call the header function here

        bool itemFound = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i].getCategory() == category) {
                cout << left << setw(20) << items[i].getId()
                    << setw(20) << items[i].getName()
                    << setw(20) << items[i].getQuantity()
                    << setw(20) << fixed << setprecision(2) << items[i].getPrice()
                    << setw(20) << items[i].getCategory() << endl;
                itemFound = true;
            }
        }

        if (!itemFound) {
            cout << "\nNo items found in this category.\n";
        }

        cout << "\nPress Enter to go back to the Menu...";
        clearInput();
        cin.get(); // Wait for Enter
    }

    void displayAllItems() {
        cout << "\n================= Display All Items =================\n";
        printItemHeader();  // Call the header function here

        for (int i = 0; i < itemCount; i++) {
            cout << left << setw(20) << items[i].getId() 
                 << setw(20) << items[i].getName() 
                 << setw(20) << items[i].getQuantity() 
                 << setw(20) << fixed << setprecision(2) << items[i].getPrice() 
                 << setw(20) << items[i].getCategory() << endl;
        }

        cout << "\nPress Enter to go back to the Menu...";
        clearInput();
        cin.get();  // Wait for Enter
    }

    void searchItem() {
        cout << "\n==================== Search Item ====================\n";
    
        string id;
        cout << "Enter Item ID: ";
        cin >> id;
        id = toLowerCase(id); // Convert input to lowercase for case-insensitive search

        bool found = false;

        printItemHeader();  // Call the header function here

        for (int i = 0; i < itemCount; i++) {
            if (toLowerCase(items[i].getId()) == id) { // Compare in lowercase
                cout << left << setw(20) << items[i].getId() 
                     << setw(20) << items[i].getName() 
                     << setw(20) << items[i].getQuantity() 
                     << setw(20) << fixed << setprecision(2) << items[i].getPrice() 
                     << setw(20) << items[i].getCategory() << endl;
                found = true;
                break;  // Exit loop as item is found
            }
        }

        if (!found) {
            cout << "\nItem ID not found!\n";
        }

        cout << "\nPress Enter to go back to the Menu...";
        clearInput();
        cin.get();  // Wait for Enter
    }

    void sortItems() {
        string sortChoiceInput, orderChoiceInput;
        int sortChoice, orderChoice;

        // Sort Menu
        while (true) {
            cout << "\n==================== Sort Items ====================\n";
            cout << "\nSort by:\n1 - Quantity\n2 - Price\n3 - Return to Main Menu\n";
            cout << "\nEnter your choice: ";
            getline(cin, sortChoiceInput);  // Use getline to read input

            if (!isValidInteger(sortChoiceInput)) {  // Invalid input
                cout << "\nInvalid input! Please enter a valid integer for sort choice.\n";
            } else {
                sortChoice = stoi(sortChoiceInput); // Convert to integer
                if (sortChoice >= 1 && sortChoice <= 3) {
                    break; // Valid input, exit loop
                } else {
                    cout << "\nInvalid choice! Please enter a valid number between 1 and 3.\n";
                }
            }
        }

        if (sortChoice == 3) {
            return; // Exit sorting
    }

        // Sort Order Menu
        while (true) {
            cout << "\nSort order:\n1 - Ascending\n2 - Descending\n3 - Return to Main Menu\n";
            cout << "\nEnter your choice: ";
            getline(cin, orderChoiceInput);  // Use getline to read input

            if (!isValidInteger(orderChoiceInput)) {  // Invalid input
            cout << "\nInvalid input! Please enter a valid integer for order choice.\n";
            } else {
                orderChoice = stoi(orderChoiceInput); // Convert to integer
                if (orderChoice >= 1 && orderChoice <= 3) {
                    break; // Valid input, exit loop
                } else {
                    cout << "\nInvalid choice! Please enter a valid number between 1 and 3.\n";
                }
            }
        }

        if (orderChoice == 3) {
            return; // Exit sorting
        }

        // Sorting the items based on user choices
        for (int i = 0; i < itemCount - 1; i++) {
            for (int j = 0; j < itemCount - i - 1; j++) {
                bool swap = false;

                if (sortChoice == 1) { // Quantity
                    swap = (orderChoice == 1) ? (items[j].getQuantity() > items[j + 1].getQuantity()) : (items[j].getQuantity() < items[j + 1].getQuantity());
                } else if (sortChoice == 2) { // Price
                    swap = (orderChoice == 1) ? (items[j].getPrice() > items[j + 1].getPrice()) : (items[j].getPrice() < items[j + 1].getPrice());
                } else if (sortChoice == 3) { // ID
                    swap = (orderChoice == 1) ? (items[j].getId() > items[j + 1].getId()) : (items[j].getId() < items[j + 1].getId());
                } else if (sortChoice == 4) { // Name
                    swap = (orderChoice == 1) ? (items[j].getName() > items[j + 1].getName()) : (items[j].getName() < items[j + 1].getName());
                }

                if (swap) {
                    // Swap IDs for display (since ID is a string, use a temporary variable)
                    string tempId = items[j].getId();
                    items[j].setId(items[j + 1].getId());
                    items[j + 1].setId(tempId);

                    // Swap names for display (also using a temporary variable)
                    string tempName = items[j].getName();
                    items[j].setName(items[j + 1].getName());
                    items[j + 1].setName(tempName);

                    // Swap quantities
                    items[j].setQuantity(items[j].getQuantity() + items[j + 1].getQuantity());
                    items[j + 1].setQuantity(items[j].getQuantity() - items[j + 1].getQuantity());
                    items[j].setQuantity(items[j].getQuantity() - items[j + 1].getQuantity());

                    // Swap prices
                    items[j].setPrice(items[j].getPrice() + items[j + 1].getPrice());
                    items[j + 1].setPrice(items[j].getPrice() - items[j + 1].getPrice());
                    items[j].setPrice(items[j].getPrice() - items[j + 1].getPrice());
                }
            }       
        }

        // Displaying sorted items
        string sortCriteria;
        switch (sortChoice) {
            case 1: sortCriteria = "Quantity"; break;
            case 2: sortCriteria = "Price"; break;
            case 3: sortCriteria = "ID"; break;
            case 4: sortCriteria = "Name"; break;
        }
    
        string sortOrder = (orderChoice == 1) ? "Ascending" : "Descending";
    
        cout << "\nSorted Items by " << sortCriteria << " (" << sortOrder << "):\n";
        printItemHeader();  // Call the header function here
    
        for (int i = 0; i < itemCount; i++) {
            cout << setw(20) << items[i].getId() 
                << setw(20) << items[i].getName() 
                << setw(20) << items[i].getQuantity()
                << setw(20) << fixed << setprecision(2) << items[i].getPrice() 
                << setw(20) << items[i].getCategory() << endl;
        }

        cout << "\nPress Enter to go back to the Menu...\n";
        clearInput(); // To handle the Enter key
        cin.get(); // Wait for Enter
    }

    void displayLowStockItems() {
        int threshold = 5; // Threshold is set to 5 as per the example
        cout << "\n============== Display Low Stock Items ==============\n";
        cout << "Displaying Low Stock Items (Quantity 5 and below):\n";
        printItemHeader();  // Call the header function here

        bool itemFound = false;
        for (int i = 0; i < itemCount; i++) {
            if (items[i].getQuantity() <= threshold) {
                cout << left << setw(20) << items[i].getId()
                     << setw(20) << items[i].getName()
                     << setw(20) << items[i].getQuantity()
                     << setw(20) << fixed << setprecision(2) << items[i].getPrice()
                     << setw(20) << items[i].getCategory() << endl;
                itemFound = true;
            }
        }

        if (!itemFound) {
            cout << "\nNo items with quantity 5 or below.\n";
        }

        cout << "\nPress Enter to go back to the Menu...";
        clearInput();
        cin.get(); 
    }
};
 
int main(){
    Inventory inventory;
    string choice_str;
    int choice;

    do {
    cout << "\n================== Inventory Management System ==================\n";
    cout << "\n1 - Add Item\n2 - Update Item\n3 - Remove Item\n4 - Display Items by Category\n5 - Display All Items\n6 - Search Item\n7 - Sort Items\n8 - Display Low Stock Items\n9 - Exit\n";
    cout << "\nEnter your choice: ";
    cin >> choice_str;

    if (!isValidInteger(choice_str)) {
            cout << "Invalid input! Please enter a valid number between 1 and 9." << endl;
            continue;
        }

    // Convert string to integer after validation
        choice = stoi(choice_str);

        switch(choice){
            case 1:
                inventory.addItem();
                break;
            case 2:
                inventory.updateItem();
                break;
            case 3:
                inventory.removeItem();
                break;
            case 4:
                inventory.displayItemsByCategory();
                break;
            case 5:
                inventory.displayAllItems();
                break;
            case 6:
                inventory.searchItem();
                break;
            case 7:
                inventory.sortItems();
                break;
            case 8:
                inventory.displayLowStockItems();
                break;
            case 9:
                cout << "\nThank you for using Inventory Management System!\nExiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid choice! Please enter a valid option." << endl;
                break;
        }
    } while (true && choice != 9);

    return 0;
}