#include "header.h"
#include <string.h>

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  r->name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct Record *r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r->id,
	    r->userId,
	    r->name,
            r->accountNbr,
            r->deposit.month,
            r->deposit.day,
            r->deposit.year,
            r->country,
            r->phone,
            r->amount,
            r->accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    int count = 0;
    char c;

    system("clear");
noAccount:
    FILE *pf = fopen(RECORDS, "a+");
    printf("\t\t\t===== New record =====\n");

    while (getAccountFromFile(pf, &cr))
    {
        if (cr.id > count)
        {
            count = cr.id;
        }
    }
    rewind(pf);
    printf("%d", count);
    r.id = count + 1;
    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, &cr))
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            fclose(pf);
            goto noAccount;
        }
    }
    rewind(pf);
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
    r.userId = u.id;
    strcpy(r.name ,u.name);

    saveAccountToFile(pf, &r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, &r))
    {
        if (strcmp(r.name, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void updateInfo(struct User u)
{
    struct Record cr;
    int account;
    int checker = 0;
    int phone = 0;
    char country[100];
    int number;
    FILE *curr, *temp;
    

    system("clear");
noAccount:
    curr = fopen(RECORDS, "r");
    printf("\t\t What is the account number you want to change ?\n");
    scanf("%d",&account);
    
    while (getAccountFromFile(curr, &cr))
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == account)
        {
            checker = 1;
            break;
        }
    }
    
    rewind(curr);
    if (checker == 0)
    {
    printf("✖ There is no account of this record\n\n");
    fclose(curr);
            goto noAccount;

    }

    temp = fopen("./data/temp.txt", "w");
    printf("\tWhich information do you want?\n ");
    printf("\t 1-> phone number\n");
    printf("\t 2-> country\n");
    scanf("%d", &number);

    switch (number)
    {
    case 1:
        printf("Enter your new phone number: ");
        scanf("%d", &phone);
        break;
    case 2:
        printf("Enter your new country: ");
        scanf("%s", country);
        break;
    default:
        printf("choose either 1 or 2");
        break;
    }

    while (getAccountFromFile(curr, &cr))
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == account)
        {
            if(phone == 0) {
                strcpy(cr.country, country);
            } else {
                cr.phone = phone;
            }
        }
        saveAccountToFile(temp, &cr);
    }
       
    fclose(curr);
    fclose(temp);
    remove(RECORDS);
    rename("./data/temp.txt", RECORDS);

    success(u);
}

void removeAccount(struct User u) 
{
    struct Record cr;
    FILE *curr, *temp;
    int checker = 0;
    int account; 
    system("clear");
noAccount:
    curr = fopen(RECORDS, "r");
    printf("\t Enter the account you want to delete :");
    scanf("%d", &account);

    while (getAccountFromFile(curr, &cr))
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == account)
        {
            checker = 1;
            break;
        }
    }
    
    rewind(curr);
    if (checker == 0)
    {
    printf("✖ There is no account of this record\n\n");
        fclose(curr);
        goto noAccount;

    }
    
    temp = fopen("./data/temp.txt", "w");
    checker = 0;
    while (getAccountFromFile(curr, &cr))
    {
        if (checker == 1)
        {
            cr.id = cr.id - 1;
        }
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == account)
        {
            checker = 1;
            continue;
        }
        saveAccountToFile(temp, &cr);
    }
       
    fclose(curr);
    fclose(temp);
    remove(RECORDS);
    rename("./data/temp.txt", RECORDS);
    success(u);
}