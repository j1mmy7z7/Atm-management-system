#include "header.h"
#include <string.h>
#include <time.h>
#include <ctype.h>

const char *RECORDS = "./data/records.txt";

void toLowerCase(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        str[i] = tolower(str[i]);
    }
}

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
    toLowerCase(r.accountType);

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
    system("clear");
    printf("\t\t====== Deleted account ======\n\n");
    printf("\tAccount number:%d\n", cr.accountNbr);
    printf("\tCountry:%s\n", cr.country);
    printf("\tPhone number:%d\n", cr.phone);
    printf("\tAmount deposited:%f\n", cr.amount);
    printf("\tType Of Account:%s\n\n", cr.accountType);
    
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

void checkDetails(struct User u) 
{
    struct Record cr;
    FILE *fp;
    int account;
    int checker = 0;

    system("clear");
retry:
    fp = fopen(RECORDS, "r");
    printf("\tEnter the account number: ");
    scanf("%d", &account);

    while(getAccountFromFile(fp, &cr))
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == account)
        {
            checker = 1;
            break;
        }
    }
    rewind(fp);
    if (checker == 0) 
    {
        printf("The record does not exits");
        fclose(fp);
        goto retry;
    }

    system("clear");
    printf("\n\tAccount number:%d\n", cr.accountNbr);
    printf("\tDeposit Date:%d/%d/%d\n", cr.deposit.day,cr.deposit.month,cr.deposit.year);
    printf("\tCountry:%s\n", cr.country);
    printf("\tPhone number:%d\n",cr.phone);
    printf("\tAmount deposited:%.2f\n", cr.amount);
    printf("\tType Of Account:%s\n\n", cr.accountType);

    float value;
    if (strcmp(cr.accountType, "saving") == 0)
    {
        value = (cr.amount * 0.07) / 12;
        printf("\tYou will get $%.2f as interest on day %d of every month", value, cr.deposit.day);
    } else if (strcmp(cr.accountType, "current") == 0)
    {
        printf("\tYou will not get interests because the account is of type current");
    } else if (strcmp(cr.accountType, "fixed01") == 0)
    {
        value = cr.amount * 0.04;
        printf("\tYou will get $%.2f as interest on  %d/%d/%d", value, cr.deposit.day,cr.deposit.month,cr.deposit.year + 1);
    } else if (strcmp(cr.accountType, "fixed02") == 0) 
    {
        value = (cr.amount * 0.05) * 2;
        printf("\tYou will get $%.2f as interest on  %d/%d/%d", value, cr.deposit.day,cr.deposit.month,cr.deposit.year + 2);
    } else if (strcmp(cr.accountType, "fixed03") == 0) 
    {
        value = (cr.amount * 0.08) * 3;
        printf("\tYou will get $%.2f as interest on  %d/%d/%d", value, cr.deposit.day,cr.deposit.month,cr.deposit.year + 3);
    } else 
    {
        printf("\tYour account %s is not known and will be treated as current\n", cr.accountType);
    }
    success(u);
}

void makeTransaction(struct User u)
{
    struct Record cr;
    FILE *fp, *temp;
    int option;
    int account;
    float amount;
    int checker = 0;

    system("clear");
retry:
    printf("\tEnter your account number:");
    scanf("%d", &account);

    fp = fopen(RECORDS, "r");
    while(getAccountFromFile(fp, &cr))
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == account)
        {
            checker = 1;
            break;
        } 
    }
    rewind(fp);
    if (checker == 0) {
        printf("No account with that account number\n");
        fclose(fp);
        goto retry;
    }

    printf("\tDo you want to\n\t\t1-> Deposit\n\t\t2-> Withdraw\n");
    scanf("%d",&option);
    printf("\tEnter the amount: $");
    scanf("%f", &amount);
    
    if (option != 1 || option != 2)
    {
        //pick a valid option
        //redo the option
    }else if (option == 2 && amount > cr.amount){
        //retrun to menu with a message
    }

    temp = fopen("./data/temp.txt", "w");
    while(getAccountFromFile(fp, &cr)) 
    {
        if (strcmp(cr.name, u.name) == 0 && cr.accountNbr == account) {
            if (option == 1) {
                cr.amount = cr.amount + amount;
            } else if (option == 2) {
                cr.amount = cr.amount - amount;
            }
        }
        saveAccountToFile(temp, &cr);
    }
    fclose(fp);
    fclose(temp);
    remove(RECORDS);
    rename("./data/temp.txt", RECORDS);   

    success(u);

}