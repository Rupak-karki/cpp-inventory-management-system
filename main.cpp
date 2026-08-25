#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstdlib>

using namespace std;

void addProduct();
void viewInventory();

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
            // Fixes infinite loop bug if users type text instead of numbers
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
    
    
    cout << "\n\tPress any key to return to the menu.";
    getch();
}

void viewInventory() {
    system("cls");
    

    cout << "\n\tPress any key to return to the menu.";
    getch();
}