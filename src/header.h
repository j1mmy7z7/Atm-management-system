#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[100];
    char password[100];
};

// authentication functions
void loginMenu(char a[100], char pass[100]);
const int setId();
const int getId(struct User u);
const char *getPassword(struct User u);
void registerUser(char a[100],  char pass[100]);
const char *getUserName(struct User u);
void saveUser(struct User *u);
int getUser(FILE *ptr, struct User *u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void updateInfo(struct User u);
void removeAccount(struct User u);
void checkDetails(struct User u);
void makeTransaction(struct User u);
void transferOwner(struct User u);

//utility
void toLowerCase(char *str);
void clearStdin();
int checkValidDate(struct Date *deposit);
int checkValidAccount(char a[100]);
void checkBuffer(char initial[100]);
int checkValidType(char a[100], char type[4]);
int leapyear(int year);
int getAccountFromFile(FILE *ptr, struct Record *r);
void saveAccountToFile(FILE *ptr, struct Record *r);
void stayOrReturn(int notGood, char *mes, void f(struct User u), struct User u);
void success(struct User u);

