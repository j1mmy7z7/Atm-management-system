### ATM Management System

## Overview

This project is an ATM management system implemented in C. Users can register, log in, create accounts, check account details, update account information, remove accounts, make transactions, and transfer ownership of accounts. The application emphasizes programming logic and adaptability to new languages.
File Structure

```
.
├── data
│   ├── records.txt
│   └── users.txt
├── Makefile
└── src
    ├── auth.c
    ├── header.h
    ├── main.c
    |── utils.c
    └── system.c

    data/: Contains files that store user and account information.
        users.txt: Stores user information (id, name, password).
        records.txt: Stores account details (id, user_id, user name, account id, date of creation, country, phone number, balance, type of account).
    src/: Contains source code files for the application.
        auth.c: Handles user authentication (login/register).
        system.c: Contains functionalities for account management.
        main.c: Entry point for the application.
        header.h: Header file for function declarations and constants.
        utils.c: Additional functions to check for error checks and buffer overflows
```

## Features
1. User Registration

    Users can register by providing a unique name and password. Duplicates are not allowed.
    User data is saved to users.txt.

2. Account Management

    Update Information: Users can update their country or phone number for existing accounts.
        Users must specify the account ID and the field they wish to change.
    Check Account Details: Users can view details of a specific account by providing the account ID.
        Interest calculation is displayed based on the account type:
            Savings: Interest rate 7%
            Fixed Accounts: 4% (fixed01), 5% (fixed02), 8% (fixed03)
            Current Accounts: No interest

3. Transactions

    Users can deposit or withdraw funds from their accounts.
    Fixed accounts cannot process transactions.

4. Account Removal

    Users can delete their accounts, which will update the relevant files.

5. Transfer Ownership

    Users can transfer account ownership to another user by specifying the account and the new owner's ID.

## Compilation and Running

To compile the project, navigate to the project directory in your terminal and run:
```
bash

make
```

To run the application:

```
bash

./atm
```

To remove the dependencies(So you can add or remove features)
```
bash 

make clean
```

## Usage

    Register: Create a new user account.
    Login: Authenticate using your credentials.
    Account Management: Create, view, update, remove, and transfer accounts as needed.
    Transactions: Make deposits or withdrawals from your accounts.

## Conclusion

This ATM management system provides a comprehensive solution for managing user accounts and transactions while demonstrating the implementation of essential programming concepts in C. Feel free to explore and enhance the code further!