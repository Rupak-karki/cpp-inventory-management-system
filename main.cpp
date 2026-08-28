#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <sstream> // For convenient numerical type conversions
#include <ctime>  // for date and time handling

using namespace std;

void addProduct();
void viewInventory();
void searchProduct();
void updateProduct();
void deleteProduct();
void sellProduct(); // New selling function declaration

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
        cout << "\n\t6. Sell Product"; // Added to menu UI
        cout << "\n\t7. Exit";
        cout << "\n\n\tChoose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\n\tInvalid input! Please enter a number 1-7.\n";
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
                sellProduct();   // Directs to the checkout selling and billing panel
                break;

            case 7:
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

    cout << "\tEnter price: ";
    cin >> price;

    cout << "\tEnter quantity: ";
    cin >> qty;

    cout << "\tExpiry Date (yyyymmdd): ";
    cin >> expiry;

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
    ofstream temp("temp.txt");     // Create a temporary file to stage our updated data

    if (!file || !temp) {
        cout << "\n\tUnable to open inventory files.";
        cout << "\n\tPress any key to return to the menu.";
        getch();
        return;
    }

    string searchID;
    string newBatch, newPrice, newQty, newExpiry;
    bool found = false;

    cout << "\n\t==================== Update Product ====================\n";
    cout << "\n\tEnter Product ID to update: ";
    cin >> searchID;

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        if (productID == searchID) {
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
        } else {
            temp << name << " " << productID << " " << batch << " "
                 << price << " " << qty << " " << expiry << endl;
        }
    }

    file.close();
    temp.close();
    
    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (found) {
        cout << "\n\tProduct updated successfully.";
    } else {
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
