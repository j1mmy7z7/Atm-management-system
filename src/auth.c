#include <termios.h>
#include "header.h"
#include <string.h>

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    fgets(a,50,stdin);
    a[strcspn(a, "\n")] = 0;

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    fgets(pass,50,stdin);
    pass[strcspn(pass, "\n")] = 0;

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

void registerUser(char a[50], char pass[50]) 
{
    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t UserName:");
    fgets(a,50,stdin);
    a[strcspn(a, "\n")] = 0;
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    fgets(pass, 50,stdin);
    pass[strcspn(pass, "\n")] = 0;
}

const char *getUserName(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening the file");
        exit(1);
    }

    while (fscanf(fp, "%s", userChecker.name) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0) {
            fclose(fp);
            char *buff = userChecker.name;
            return buff;
        }
    }
    fclose(fp);
    return "no user found";
}

const char *getPassword(struct User u)
{
    FILE *fp;
    char data[256];

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fgets(data,sizeof(data), fp ) != NULL)
    {
        char* piece = strtok(data, " ");
        piece = strtok(NULL, " ");
        if (strcmp(piece, u.name) == 0) 
        {
            fclose(fp);
            piece = strtok(NULL, " ");
            piece[strcspn(piece, "\n")] = 0;
            return piece;
        } 
    }

    fclose(fp);
    return "no user found";
}