#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

void toLowerCase(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        str[i] = tolower(str[i]);
    }
}

void clearStdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
} 

int leapyear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return 0;
    } else {
        return 1;
    }
}

void checkBuffer(char initial[100]) 
{
    int len = strlen(initial);
    if (initial[len - 1] != '\n')
    {
        clearStdin();
    }else {
        initial[strcspn(initial, "\n")] = 0;
    }
}

int checkValidType(char a[100], char type[4])
{
    if (strlen(a) == 0) 
    {
        return 1;
    }
    if (strcmp(type, "str") == 0) 
    {
        int len = strlen(a);
        for (int i = 0; i < len; i++) 
        {
            if (!isalpha(a[i])) {
                return 1;
            }
        }
        return 0;
    } else if (strcmp(type, "flt") == 0) {
        int len = strlen(a);
        int dotCount = 0;
        for (int i = 0; i < len; i++) {
            if (!isdigit(a[i])) {
                if (a[i] == '.') {
                    dotCount++;
                } else {
                    return 1; // Found an invalid character
                }
            }
        }
        // Valid float should have at most one dot
        if (dotCount > 1) {
            return 1;
        }
        return 0; 
    } else if (strcmp(type, "int") == 0) {
        int len  = strlen(a);
        for (int i = 0; i < len; i++)
        {
            if (!isdigit(a[i]))
            {
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

int checkValidAccount(char a[100])
{
    char *accounts[5] = {"saving", "current", "fixed01","fixed02","fixed03"};
    for (int i = 0; i < 5; i++){
        if (strcmp(a, accounts[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int checkValidDate(struct Date *deposit)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (deposit->month > 12 || deposit->month < 0) {
        return 1;
    } else if (deposit ->day > 31) {
        return 1;
    } else if (leapyear(deposit ->year) == 0 && deposit->month == 2) {
        if (deposit ->day > 29) {
            return 1;
        }
    } else if (leapyear(deposit ->year) == 1 && deposit ->month == 2) {
        if (deposit -> day > 28) {
            return 1;
        }
    } else {
        if (deposit -> day < 1 || deposit->day > daysInMonth[deposit->month - 1])
            return 1;
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

void stayOrReturn(int notGood, char *mes, void f(struct User u), struct User u)
{
    char buffer[100];
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ %s!!\n", mes);
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        fgets(buffer,100,stdin);
        checkBuffer(buffer);

        if(checkValidType(buffer, "int")!= 0) 
        {
            printf("\t\nPlease enter a valid option\n\n");
            goto invalid;
        }
        sscanf(buffer,"%d", &option);
    
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
        fgets(buffer,100,stdin);
        checkBuffer(buffer);

        if(checkValidType(buffer, "int")!= 0) 
        {
            printf("\t\nPlease enter a valid option\n\n");
            goto invalid;
        }
        sscanf(buffer,"%d", &option);
    
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
    char buffer[100];
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    fgets(buffer,100,stdin);
    checkBuffer(buffer);

    if(checkValidType(buffer, "int")!= 0)     
    {
        printf("\t\nPlease enter a valid option\n\n");
        goto invalid;
    }
    sscanf(buffer,"%d", &option);
    
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





