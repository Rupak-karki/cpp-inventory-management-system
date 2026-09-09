Inventory Management System

A console-based inventory management system written in procedural C++11. The application stores product records in a text file and provides common inventory operations through a simple menu-driven interface.

Features

The system currently supports adding products, viewing inventory, searching by Product ID, updating product details, deleting products by Product ID, selling products by Product ID, generating invoices, removing expired products, and displaying organized inventory alerts.

The alert screen separates low-stock products, products expiring within the next 30 days, expired products, invalid expiry entries, and a final inventory-status summary. Product entry also validates numeric values, expiry-date format, and duplicate Product IDs.

Requirements

•
Windows operating system

•
Dev-C++ TDM-GCC 4.9.2 or another compiler with C++11 support

•
Visual Studio Code is recommended for editing and Git operations

•
Git for version control

The current implementation uses conio.h and the Windows cls command, so the program is intended primarily for Windows environments.

Compile and run

From the project directory, compile with TDM-GCC:

Plain Text


& 'C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe' -std=c++11 -Wall -Wextra main.cpp -o inventory.exe
.\inventory.exe



If g++ has been added to your system PATH, the shorter form is:

Plain Text


g++ -std=c++11 -Wall -Wextra main.cpp -o inventory.exe
.\inventory.exe



Menu options

Option
Operation
1
Add a product after validating its details and Product ID uniqueness.
2
Display all saved inventory records.
3
Search for a product by Product ID.
4
Update a product by Product ID.
5
Delete a product by Product ID after confirmation.
6
Sell stock by Product ID and generate an invoice.
7
Check and remove products whose expiry date has passed.
8
View low-stock, soon-to-expire, expired, and summary alerts.
9
Exit the application.




Data files

The application uses simple whitespace-separated text files in the project directory. Each inventory record has this structure:

Plain Text


productName productID batchNumber price quantity expiryDate



For example:

Plain Text


Rice P001 B001 120.00 25 20271231



The application creates or updates inventory.txt, temp.txt, and bill.txt during normal operation. These generated files are excluded from Git through .gitignore so personal runtime data and generated invoices are not published accidentally.

Development history

This project was developed incrementally through small, tested commits. The repository history shows the application growing from a menu skeleton into a functional inventory system:

Development area
Progress represented in the history
Foundation
Menu loop, input handling, and procedural function structure.
Product storage
Product entry and saving records to inventory.txt.
Inventory operations
Viewing, searching by name and Product ID, updating, and deleting products.
Sales
Selling stock by Product ID, updating quantity, and generating invoices.
Date management
Expiry input validation and expired-product cleanup.
Reliability
Duplicate-ID prevention, numeric validation, preservation after failed updates, and compiler-warning cleanup.
Alerts
Initial alert support, 30-day expiry warnings, and the final organized alert display.




The history reflects genuine development and refinement. Some early commit messages were written while learning Git, but the code progression remains visible and the later commits document the feature improvements clearly.

Limitations and possible improvements

The current version is intentionally a procedural learning project. Product names cannot contain spaces because records are stored as whitespace-separated fields. The application is designed for one local user and does not use a database or authentication. Future improvements could include a structured data format, stronger calendar validation, cross-platform screen handling, and a more modular design.

License

This project is intended for educational and portfolio use. Add a formal license if you plan to distribute or reuse it publicly.

