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
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ %s!!\n", mes);
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





