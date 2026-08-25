#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

void addProduct();
void viewInventory();
void searchProduct(); // New search function declaration

string name, productID, batch, price, qty, expiry;

int main() {
    while (true) {
        int choice;

        system("cls");

        cout << "\n\n\tInventory Management System\n";
        cout << "\t===========================\n";
        cout << "\n\t1. Add Product";
        cout << "\n\t2. View Inventory";
        cout << "\n\t3. Search Product";  // Added to menu UI
        cout << "\n\t4. Exit";
        cout << "\n\n\tChoose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\n\tInvalid input! Please enter a number 1-4.\n";
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
                searchProduct(); // Directs to the search engine 
                break;

            case 4:
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
    cout << "\n\t==================== Search Engine ====================\n"
    string searchName;
    bool found = false;

    cout << "\n\tEnter product name to search: ";
    cin >> searchName;

    while (file >> name >> productID >> batch >> price >> qty >> expiry) {
        if (name == searchName) {
            cout << "\n\tProduct Found\n";
            cout << "\t=============\n";
            cout << "\tName: " << name << endl;
            cout << "\tProduct ID: " << productID << endl;
            cout << "\tBatch No: " << batch << endl;
            cout << "\tPrice: " << price << endl;
            cout << "\tQuantity: " << qty << endl;
            cout << "\tExpiry: " << expiry << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n\tProduct not found.";
    }

    file.close();

    cout << "\n\tPress any key to return to the menu.";
    getch();
}
