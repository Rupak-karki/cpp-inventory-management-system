# Inventory Management System

A console-based inventory management system written in procedural C++11. The application stores product records in text files and provides common inventory operations through a simple menu-driven interface.

## Features

The system supports adding products, viewing inventory, searching by Product ID, updating product details, deleting products by Product ID, selling products by Product ID, generating invoices, removing expired products, and displaying organized inventory alerts.

The alert screen separates low-stock products, products expiring within the next 30 days, expired products, invalid expiry entries, and a final inventory-status summary. Product entry also validates numeric values, expiry-date format, and duplicate Product IDs.

## Requirements

- Windows operating system
- A C++11-compatible compiler
- Dev-C++ with TDM-GCC 4.9.2, or another MinGW/GCC installation
- Visual Studio Code, if you want to edit the project and use the terminal
- Git, if you want to view the commit history or publish the project to GitHub

The current implementation uses `conio.h` and the Windows `cls` command. Therefore, it is intended primarily for Windows environments.

## Choose your workflow

You can use **Dev-C++** to open, compile, and run the program through its IDE. You can use **Visual Studio Code** to edit the source, compile it from the integrated terminal, run it, and manage the Git history. The two workflows use the same `main.cpp` source file and the same C++11 compiler family.

You do not need to use both applications. Choose the workflow that best suits your purpose:

| Purpose | Recommended application |
|---|---|
| Simple editing, compiling, and running | Dev-C++ |
| Git commits, GitHub publishing, and terminal-based development | Visual Studio Code |
| Independent verification | Compile in one application and run the result in the other |

## Option A: Set up and run with Dev-C++

### Open the project

Open Dev-C++ and select **File > Open Project or File**. Open the repository folder and choose `main.cpp`.

If you prefer to keep a Dev-C++ project file, create or open a project in the repository folder and add `main.cpp` to it. The important source file is `main.cpp`; the generated executable and runtime text files do not belong in Git.

### Configure C++11

In Dev-C++, open **Tools > Compiler Options**. Select the compiler profile that contains TDM-GCC, then open the **Settings** tab. In the compiler command section, make sure the following option is present:

```text
-std=c++11
```

The screenshot used during development showed the TDM-GCC 4.9.2 profile with this option enabled. This setting allows the compiler to build the program using the C++11 language standard.

### Compile and run

Use **Compile & Run** in Dev-C++. The program should open a console window and display this menu:

```text
1. Add Product
2. View Inventory
3. Search Product
4. Update Product
5. Delete Product
6. Sell Product
7. Check & Remove Expired Products
8. View Inventory Alerts
9. Exit
```

The program creates its runtime files in the working directory. If Dev-C++ launches the executable from a different directory, look in the directory configured as the program’s working directory when checking `inventory.txt` or `bill.txt`.

## Option B: Set up and run with Visual Studio Code

### Open the repository

Install Visual Studio Code and the Microsoft **C/C++** extension if they are not already installed. In VS Code, select **File > Open Folder** and open the repository folder containing `main.cpp`.

Open **Terminal > New Terminal**. The commands below assume that the Dev-C++ compiler is installed at:

```text
C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe
```

If your compiler is installed elsewhere, replace the path with the location of your own `g++.exe`.

### Verify the compiler

In the VS Code PowerShell terminal, run:

```powershell
& 'C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe' --version
```

You should see the installed GCC/TDM-GCC version. Using the complete compiler path is reliable even when `g++` has not been added to the Windows PATH.

### Compile and run from the terminal

From the repository folder, run:

```powershell
& 'C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe' -std=c++11 -Wall -Wextra main.cpp -o inventory.exe
.\inventory.exe
```

The `-std=c++11` option selects C++11, while `-Wall -Wextra` enables useful compiler warnings. The program should display the same nine-option menu shown in the Dev-C++ instructions.

If `g++` has been added to your system PATH, you can use the shorter commands:

```powershell
g++ -std=c++11 -Wall -Wextra main.cpp -o inventory.exe
.\inventory.exe
```

### Do not rely on Code Runner by default

The VS Code **Run Code** button belongs to the Code Runner extension and may use a different shell or compiler path. If it reports that `g++` is not recognized, compile from the integrated PowerShell terminal using the complete compiler path shown above. This approach also makes the exact compiler command visible and reproducible.

## Git and GitHub workflow in VS Code

Use VS Code for Git operations if you want to preserve the project’s staged development history. After testing a feature, inspect the changes, commit only the intended source or documentation file, and push the commit:

```powershell
git status
git diff --stat
git add main.cpp
git commit -m "describe the completed feature"
git push
```

For a documentation-only change, replace `main.cpp` with `README.md`. Before publishing or sharing the repository, verify the history and working tree:

```powershell
git status
git log --oneline --decorate --all
```

The expected final state is a clean working tree and a local `main` branch synchronized with `origin/main`.

## Menu options

| Option | Operation |
|---:|---|
| 1 | Add a product after validating its details and Product ID uniqueness. |
| 2 | Display all saved inventory records. |
| 3 | Search for a product by Product ID. |
| 4 | Update a product by Product ID. |
| 5 | Delete a product by Product ID after confirmation. |
| 6 | Sell stock by Product ID and generate an invoice. |
| 7 | Check and remove products whose expiry date has passed. |
| 8 | View low-stock, soon-to-expire, expired, and summary alerts. |
| 9 | Exit the application. |

## Data files

The application uses simple whitespace-separated text files in the project directory. Each inventory record has this structure:

```text
productName productID batchNumber price quantity expiryDate
```

For example:

```text
Rice P001 B001 120.00 25 20271231
```

The application creates or updates `inventory.txt`, `temp.txt`, and `bill.txt` during normal operation. These generated files are excluded from Git through `.gitignore`, so personal runtime data, temporary files, invoices, and compiled executables are not published accidentally.

## Development history

This project was developed incrementally through small, tested commits. The repository history shows the application growing from a menu skeleton into a functional inventory system:

| Development area | Progress represented in the history |
|---|---|
| Foundation | Menu loop, input handling, and procedural function structure. |
| Product storage | Product entry and saving records to `inventory.txt`. |
| Inventory operations | Viewing, searching by name and Product ID, updating, and deleting products. |
| Sales | Selling stock by Product ID, updating quantity, and generating invoices. |
| Date management | Expiry input validation and expired-product cleanup. |
| Reliability | Duplicate-ID prevention, numeric validation, preservation after failed updates, and compiler-warning cleanup. |
| Alerts | Initial alert support, 30-day expiry warnings, and the final organized alert display. |

The history reflects genuine development and refinement. Some early commit messages were written while learning Git, but the code progression remains visible and the later commits document the feature improvements clearly.

## Limitations and possible improvements

The current version is intentionally a procedural learning project. Product names cannot contain spaces because records are stored as whitespace-separated fields. The application is designed for one local user and does not use a database or authentication. Future improvements could include a structured data format, stronger calendar validation, cross-platform screen handling, and a more modular design.

## License

This project is intended for educational and portfolio use. Add a formal license if you plan to distribute or reuse it publicly.
