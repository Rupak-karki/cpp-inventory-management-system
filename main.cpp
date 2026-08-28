#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstdio>

using namespace std;

void addProduct();
void viewInventory();
void searchProduct();
void updateProduct(); // New update function declaration

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
        cout << "\n\t4. Update Product"; // Added to menu UI
        cout << "\n\t5. Exit";
        cout << "\n\n\tChoose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\n\tInvalid input! Please enter a number 1-5.\n";
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
                updateProduct(); // Directs to update logic
                break;

            case 5:
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
    
    // Swap out the files to make changes permanent
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
