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
bool isValidNumber(const string& value, bool allowDecimal); // for checking number validation
bool isValidExpiry(const string& value); //to check correct format of expiry


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
        cout << "\n\t8. Exit";
        cout << "\n\n\tChoose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\n\tInvalid input! Please enter a number 1-8.\n";
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

    cout << "\n\tProduct ID: ";
    cin >> productID;

    cout << "\tEnter batch number: ";
    cin >> batch;
    
    // 1. Validate Price (Allows Decimals)
    while (true) {
        cout << "\tEnter price: ";
        cin >> price;
        if (isValidNumber(price, true)) {
            break;
        }
        cout << "\t Invalid price format! Use digits only (e.g., 12.50 or 99).\n";
    }

    // 2. Validate Quantity (Whole Numbers Only)
    while (true) {
        cout << "\tEnter quantity: ";
        cin >> qty;
        if (isValidNumber(qty, false)) {
            break;
        }
        cout << "\t Invalid quantity format! Use whole numbers only.\n";
    }

 // Validate Expiry Date 
    while (true) {
        cout << "\tExpiry Date (yyyymmdd): ";
        cin >> expiry;
        
        if (isValidExpiry(expiry)) {
            break; 
        }
        
        // Friendly inline error warning instead of returning to menu
        cout << "\t Invalid expiry date. Use YYYYMMDD format (e.g., 20271231).\n";
    }



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
