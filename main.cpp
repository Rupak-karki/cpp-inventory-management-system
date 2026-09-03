#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <sstream> 
#include <ctime>  
#include <cctype> // to classify and transform individual narrow characters.

using namespace std;

void addProduct();
void viewInventory();
void searchProduct();
void updateProduct();
void deleteProduct();
void sellProduct();
void checkExpiredProducts(); 
bool isValidNumber(const string& value, bool allowDecimal); 
bool isValidExpiry(const string& value); 
bool productIdExists(const string& id); //to check unique id
void showAlerts(); // to show inventory alerts
int daysUntilExpiry(const string& value);


string name, productID, batch, price, qty, expiry;

int main() {
    while (true) {
        int choice;

        system("cls");

        cout << "\n\n\tInventory Management System\n";
        cout << "\t===========================\n";
        cout << "\n\t1. Add Product";
        cout << "\n\t2. View Inventory";
        cout << "\n\t3. Search Product";
        cout << "\n\t4. Update Product";
        cout << "\n\t5. Delete Product";
        cout << "\n\t6. Sell Product"; 
        cout << "\n\t7. Check & Remove Expired Products";
        cout << "\n\t8. View Inventory Alerts";
        cout << "\n\t9. Exit";
        cout << "\n\n\tChoose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\n\tInvalid input! Please enter a number 1-9.\n";
            cout << "\n\tPress any key to return to the menu...";
            getch();
            continue;
        }

        switch (choice) {
            case 1:
                addProduct();
                break;

            case 2:
                viewInventory();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                updateProduct();
                break;

            case 5:
                deleteProduct();
                break;

            case 6:
                sellProduct();  
                break;
            case 7:
                checkExpiredProducts();
                break;
            case 8:
                showAlerts();
                break;

            case 9:
                cout << "\n\tExiting program...\n";
                return 0;

            default:
                cout << "\n\tInvalid choice.";
                cout << "\n\tPress any key to return to the menu...";
                getch();
        }
    }
}

void addProduct() {
    system("cls");

    ofstream file("inventory.txt", ios::app);

    if (!file) {
        cout << "\n\tUnable to open inventory file.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    cout << "\n\tEnter product details\n\n";
    cout << "\n\tEnter product name: ";
    cin >> name;

    // Validate Unique Product ID using the helper function
    while (true) {
        cout << "\tProduct ID: ";
        cin >> productID;
        if (!productIdExists(productID)) {
            break; // Exit loop if the ID is unique and safe to use
        }
        cout << "\t  Error: Product ID '" << productID << "' already exists! Try another.\n";
    }

    cout << "\tEnter batch number: ";
    cin >> batch;
    
    // 1. Validate Price Loop (Allows Decimals)
    while (true) {
        cout << "\tEnter price: ";
        cin >> price;
        if (isValidNumber(price, true)) {
            break;
        }
        cout << "\t  Invalid price format! Use digits only (e.g., 12.50 or 99).\n";
    }

    // 2. Validate Quantity Loop (Whole Numbers Only)
    while (true) {
        cout << "\tEnter quantity: ";
        cin >> qty;
        if (isValidNumber(qty, false)) {
            break;
        }
        cout << "\t  Invalid quantity format! Use whole numbers only.\n";
    }

    // 3. Validate Expiry Date Loop (Exactly 8 Digits)
    while (true) {
        cout << "\tExpiry Date (yyyymmdd): ";
        cin >> expiry;
        
        if (isValidExpiry(expiry)) {
            break; 
        }
        cout << "\t  Invalid expiry date. Use YYYYMMDD format (e.g., 20271231).\n";
    }

    // Write the validated clean fields to file
    file << name << " " << productID << " " << batch << " "
         << price << " " << qty << " " << expiry << endl;

    file.close();

    cout << "\n\tProduct added successfully.";
    cout << "\n\tPress any key to return to the menu.";
    getch();
}


void viewInventory() {
    system("cls");

    ifstream file("inventory.txt");

    if (!file) {
        cout << "\n\tNo inventory file found.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    bool found = false;

    cout << "\n\n\t\tCurrent Inventory\n";
    cout << "\t\t=================\n\n";
    cout << left << setw(15) << "Name"
         << setw(15) << "Product ID"
         << setw(15) << "Batch"
         << setw(12) << "Price"
         << setw(12) << "Quantity"
         << setw(12) << "Expiry" << endl;

    cout << "--------------------------------------------------------------------------\n";

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        found = true;

        cout << left << setw(15) << name
             << setw(15) << productID
             << setw(15) << batch
             << setw(12) << price
             << setw(12) << qty
             << setw(12) << expiry << endl;
    }

    if (!found) {
        cout << "\n\tInventory is empty.";
    }

    file.close();

    cout << "\n\tPress any key to return to the menu.";
    getch();
}

void searchProduct() {
    system("cls");

    ifstream file("inventory.txt");

    if (!file) {
        cout << "\n\tNo inventory file found.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    string searchID;
    bool found = false;

    cout << "\n\tEnter Product ID to search: ";
    cin >> searchID;

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        if (productID == searchID) {
            found = true;

            cout << "\n\n\tProduct Found";
            cout << "\n\t=============\n";
            cout << "\tName        : " << name << endl;
            cout << "\tProduct ID  : " << productID << endl;
            cout << "\tBatch       : " << batch << endl;
            cout << "\tPrice       : " << price << endl;
            cout << "\tQuantity    : " << qty << endl;
            cout << "\tExpiry Date : " << expiry << endl;
            break;
        }
    }

    if (!found) {
        cout << "\n\tProduct not found.";
    }

    file.close();

    cout << "\n\n\tPress any key to return to the menu.";
    getch();
}

void updateProduct() {
    system("cls");

    ifstream file("inventory.txt");

    if (!file) {
        cout << "\n\tNo inventory file found.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    string searchID;
    string newBatch, newPrice, newQty, newExpiry;
    bool found = false;
    bool updated = false;

    cout << "\n\t==================== Update Product ====================\n";
    cout << "\n\tEnter Product ID to update: ";
    cin >> searchID;

    ofstream temp("temp.txt");

    if (!temp) {
        cout << "\n\tUnable to create temporary file.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        if (productID == searchID && !found) {
            found = true;

            cout << "\n\tCurrent product details\n";
            cout << "\tName: " << name << endl;
            cout << "\tID: " << productID << endl;
            cout << "\tBatch: " << batch << endl;
            cout << "\tPrice: " << price << endl;
            cout << "\tQuantity: " << qty << endl;
            cout << "\tExpiry: " << expiry << endl;

            cout << "\n\tEnter new batch number: ";
            cin >> newBatch;

            cout << "\tEnter new price: ";
            cin >> newPrice;

            cout << "\tEnter new quantity: ";
            cin >> newQty;

            cout << "\tEnter new expiry date (yyyymmdd): ";
            cin >> newExpiry;

            temp << name << " " << productID << " " << newBatch << " "
                 << newPrice << " " << newQty << " " << newExpiry << endl;

            updated = true;
        } else {
            temp << name << " " << productID << " " << batch << " "
                 << price << " " << qty << " " << expiry << endl;
        }
    }

    file.close();
    temp.close();

    if (updated) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        cout << "\n\tProduct updated successfully.";
    } else {
        remove("temp.txt");
        cout << "\n\tProduct not found.";
    }

    cout << "\n\tPress any key to return to the menu.";
    getch();
}


void deleteProduct() {
    system("cls");

    ifstream file("inventory.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cout << "\n\tUnable to open inventory files.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    cout << "\n\t==================== Delete Product ====================\n";

    string searchID;
    char confirmation;
    bool found = false;
    bool deleted = false;

    cout << "\n\tEnter Product ID to delete: ";
    cin >> searchID;

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        if (productID == searchID && !found) {
            found = true;

            cout << "\n\tProduct Found\n";
            cout << "\tName: " << name << endl;
            cout << "\tProduct ID: " << productID << endl;
            cout << "\tBatch: " << batch << endl;
            cout << "\tQuantity: " << qty << endl;
            cout << "\tExpiry: " << expiry << endl;

            cout << "\n\tDelete this product? (y/n): ";
            cin >> confirmation;

            if (confirmation == 'y' || confirmation == 'Y') {
                deleted = true;
                cout << "\n\tProduct deleted successfully.";
                continue;
            }
        }

        temp << name << " " << productID << " " << batch << " "
             << price << " " << qty << " " << expiry << endl;
    }

    file.close();
    temp.close();

    if (deleted) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
    } else {
        remove("temp.txt");

        if (!found) {
            cout << "\n\tProduct not found.";
        } else {
            cout << "\n\tProduct was not deleted.";
        }
    }

    cout << "\n\tPress any key to return to the menu.";
    getch();
}


void sellProduct() {
    system("cls");

    ifstream file("inventory.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cout << "\n\tUnable to open inventory files.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    string searchID;
    int sellQty;
    bool found = false;
    bool saleCompleted = false;

    cout << "\n\t==================== Sell Product ====================\n";
    cout << "\n\tEnter Product ID to sell: ";
    cin >> searchID;

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        if (productID == searchID && !found) {
            found = true;

            int availableQty = 0;
            double unitPrice = 0.0;

            stringstream(qty) >> availableQty;
            stringstream(price) >> unitPrice;

            cout << "\n\tProduct Found\n";
            cout << "\tName: " << name << endl;
            cout << "\tProduct ID: " << productID << endl;
            cout << "\tBatch: " << batch << endl;
            cout << "\tPrice: " << price << endl;
            cout << "\tAvailable quantity: " << qty << endl;

            cout << "\n\tEnter quantity to sell: ";

            if (!(cin >> sellQty) || sellQty <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "\n\tEnter a valid quantity greater than zero.";
            } else if (sellQty > availableQty) {
                cout << "\n\tInsufficient stock.";
            } else {
                int remainingQty = availableQty - sellQty;
                double totalPrice = sellQty * unitPrice;

                stringstream updatedQty;
                updatedQty << remainingQty;
                qty = updatedQty.str();

                cout << fixed << setprecision(2);
                cout << "\n\tTotal price: " << totalPrice << endl;
                cout << "\tSale completed successfully.";

                ofstream bill("bill.txt", ios::app);

                if (bill) {
                    time_t now = time(0);
                    tm* currentTime = localtime(&now);
                    char timeText[20];

                    strftime(timeText, sizeof(timeText),
                             "%Y-%m-%d %H:%M:%S", currentTime);

                    bill << fixed << setprecision(2);
                    bill << "\n================ INVOICE ================\n";
                    bill << "Date: " << timeText << endl;
                    bill << "Product Name: " << name << endl;
                    bill << "Product ID: " << productID << endl;
                    bill << "Batch No: " << batch << endl;
                    bill << "Quantity Sold: " << sellQty << endl;
                    bill << "Price per Unit: " << unitPrice << endl;
                    bill << "Total Price: " << totalPrice << endl;
                    bill << "==========================================\n";
                }

                if (remainingQty == 0) {
                    cout << "\n\tThe product is now out of stock.";
                }

                saleCompleted = true;
            }
        }

        // Always retain the record, including products with quantity 0.
        temp << name << " " << productID << " " << batch << " "
             << price << " " << qty << " " << expiry << endl;
    }

    file.close();
    temp.close();

    if (saleCompleted) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
    } else {
        remove("temp.txt");

        if (!found) {
            cout << "\n\tProduct ID not found.";
        }
    }

    cout << "\n\tPress any key to return to the menu.";
    getch();
}

void checkExpiredProducts() {
    system("cls");

    ifstream file("inventory.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cout << "\n\tUnable to open inventory files.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }
    
     // Fetch the system's current live time metrics
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    
     // Format time directly into an 8-character string (YYYYMMDD)
    char currentDate[9];
    strftime(currentDate, sizeof(currentDate), "%Y%m%d", currentTime);

    bool expiredFound = false;

    cout << "\n\tChecking for expired products...\n";

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        if (expiry < currentDate) {
            expiredFound = true;

            cout << "\n\tRemoved expired product: " << name;
            cout << "\n\tProduct ID: " << productID;
            cout << "\n\tExpiry Date: " << expiry << "\n";
            continue;  // Skips writing this specific line to temp.txt, deleting it.
        }

        // Keep unexpired products safe
        temp << name << " " << productID << " " << batch << " "
             << price << " " << qty << " " << expiry << endl;
    }

    file.close();
    temp.close();

    if (expiredFound) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        cout << "\n\t Database cleanup complete. Expired records purged successfully.";

    } else {
        remove("temp.txt");
        cout << "\n\tScan complete. No expired products found.";
    }

    cout << "\n\tPress any key to return to the menu.";
    getch();
}

bool isValidNumber(const string& value, bool allowDecimal) {
    if (value.empty()) {
        return false;
    }

    bool hasDecimal = false;
    bool hasDigit = false;

    for (char character : value) {
        if (isdigit(static_cast<unsigned char>(character))) {
            hasDigit = true;
        } else if (allowDecimal && character == '.' && !hasDecimal) {
            hasDecimal = true;
        } else {
            return false;
        }
    }

    return hasDigit;
}

bool isValidExpiry(const string& value) {
    return value.length() == 8 && isValidNumber(value, false);
}

bool productIdExists(const string& id) {
    ifstream file("inventory.txt");
    if (!file) {
        return false; // If file doesn't exist yet, the ID cannot exist
    }

    // Temporary local variables to safely read the file line by line
    string sName, sID, sBatch, sPrice, sQty, sExpiry;

    while (file >> sName >> sID >> sBatch >> sPrice >> sQty >> sExpiry) {
        if (sID == id) {
            file.close(); // Close the file stream immediately on match
            return true;  // ID found!
        }
    }

    file.close(); // Close the file stream if no match is found
    return false; // ID is completely unique
}


void showAlerts() {
    system("cls");

    ifstream file("inventory.txt");

    if (!file) {
        cout << "\n\tNo inventory file found.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    const int lowStockLimit = 5;
    const int soonExpiryLimit = 30;
    int lowStockCount = 0;
    int soonExpiryCount = 0;
    int expiredCount = 0;
    int invalidDateCount = 0;

    cout << "\n\n\t+=========================================================+\n";
    cout << "\t|                 INVENTORY ALERT CENTER                  |\n";
    cout << "\t+=========================================================+\n";
    cout << "\t| Low stock: 5 or fewer units                             |\n";
    cout << "\t| Expiring soon: within the next 30 days                  |\n";
    cout << "\t+=========================================================+\n";

    cout << "\n\t[LOW STOCK PRODUCTS]\n";
    cout << "\t----------------------------------------------------------\n";
    cout << left << "\t" << setw(16) << "Product ID"
         << setw(18) << "Name"
         << setw(12) << "Quantity"
         << "Batch" << endl;
    cout << "\t----------------------------------------------------------\n";

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        int availableQty = 0;
        stringstream(qty) >> availableQty;

        if (availableQty <= lowStockLimit) {
            lowStockCount++;
            cout << left << "\t" << setw(16) << productID
                 << setw(18) << name
                 << setw(12) << availableQty
                 << batch << endl;
        }
    }

    if (lowStockCount == 0) {
        cout << "\tNo low-stock products found.\n";
    }

    file.clear();
    file.seekg(0, ios::beg);

    cout << "\n\t[PRODUCTS EXPIRING SOON]\n";
    cout << "\t----------------------------------------------------------\n";
    cout << left << "\t" << setw(16) << "Product ID"
         << setw(18) << "Name"
         << setw(14) << "Expiry Date"
         << "Days Left" << endl;
    cout << "\t----------------------------------------------------------\n";

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        int daysLeft = daysUntilExpiry(expiry);

        if (daysLeft >= 0 && daysLeft <= soonExpiryLimit) {
            soonExpiryCount++;
            cout << left << "\t" << setw(16) << productID
                 << setw(18) << name
                 << setw(14) << expiry
                 << daysLeft << endl;
        }
    }

    if (soonExpiryCount == 0) {
        cout << "\tNo products are expiring within 30 days.\n";
    }

    file.clear();
    file.seekg(0, ios::beg);

    cout << "\n\t[EXPIRED PRODUCTS]\n";
    cout << "\t----------------------------------------------------------\n";
    cout << left << "\t" << setw(16) << "Product ID"
         << setw(18) << "Name"
         << setw(14) << "Expiry Date"
         << "Batch" << endl;
    cout << "\t----------------------------------------------------------\n";

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        int daysLeft = daysUntilExpiry(expiry);

        if (daysLeft == -99999) {
            invalidDateCount++;
        } else if (daysLeft < 0) {
            expiredCount++;
            cout << left << "\t" << setw(16) << productID
                 << setw(18) << name
                 << setw(14) << expiry
                 << batch << endl;
        }
    }

    if (expiredCount == 0) {
        cout << "\tNo expired products found.\n";
    }

    file.close();

    cout << "\n\t[ALERT SUMMARY]\n";
    cout << "\t----------------------------------------------------------\n";
    cout << "\tLow-stock products       : " << lowStockCount << endl;
    cout << "\tExpiring within 30 days  : " << soonExpiryCount << endl;
    cout << "\tExpired products         : " << expiredCount << endl;

    if (invalidDateCount > 0) {
        cout << "\tInvalid expiry entries   : " << invalidDateCount << endl;
    }

    if (lowStockCount == 0 && soonExpiryCount == 0 && expiredCount == 0) {
        cout << "\n\tInventory status: All clear.\n";
    } else {
        cout << "\n\tInventory status: Attention required.\n";
    }

    cout << "\n\tPress any key to return to the menu.";
    getch();
}

int daysUntilExpiry(const string& value) {
    if (!isValidExpiry(value)) {
        return -99999;
    }

    int year = atoi(value.substr(0, 4).c_str());
    int month = atoi(value.substr(4, 2).c_str());
    int day = atoi(value.substr(6, 2).c_str());

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return -99999;
    }

    tm expiryTime = tm();
    expiryTime.tm_year = year - 1900;
    expiryTime.tm_mon = month - 1;
    expiryTime.tm_mday = day;
    expiryTime.tm_hour = 12;

    time_t expiryValue = mktime(&expiryTime);

    if (expiryValue == -1) {
        return -99999;
    }

    time_t now = time(0);
    tm* currentTime = localtime(&now);
    currentTime->tm_hour = 12;
    currentTime->tm_min = 0;
    currentTime->tm_sec = 0;
    time_t currentValue = mktime(currentTime);

    return static_cast<int>(difftime(expiryValue, currentValue) / (60 * 60 * 24));
}
