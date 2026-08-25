#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip> // Needed for clean columns in viewInventory() 
#include <cstdlib>

using namespace std;

void addProduct();
void viewInventory();

string name, productID, batch, price, qty, expiry;

int main() {
    while (true) {
        int choice;

        system("cls");

        cout << "\n\n\tInventory Management System\n";
        cout << "\t===========================\n";
        cout << "\n\t1. Add Product";
        cout << "\n\t2. View Inventory";
        cout << "\n\t3. Exit";
        cout << "\n\n\tChoose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\n\tInvalid input! Please enter a number 1-3.\n";
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
    
    // Print headers formatted into neat columns
    cout << left << setw(15) << "Name"
         << setw(15) << "Product ID"
         << setw(15) << "Batch"
         << setw(12) << "Price"
         << setw(12) << "Quantity"
         << setw(12) << "Expiry" << endl;

    cout << "--------------------------------------------------------------------------\n";
    
    // Read the file line by line matching  data layout
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

    cout << "\n\n\tPress any key to return to the menu.";
    getch();
}
