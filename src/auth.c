#include <termios.h>
#include "header.h"
#include <string.h>

char *USERS = "./data/users.txt";

void loginMenu(char a[100], char pass[100])
{
    struct termios oflags, nflags;
    char buffer[100];

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    fgets(buffer,100,stdin);
    checkBuffer(buffer);
    sscanf(buffer,"%s",a);

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
    fgets(buffer,100,stdin);
    checkBuffer(buffer);
    sscanf(buffer,"%s",pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

void registerUser(char a[100], char pass[100]) 
{
    char buffer[100];
    system("clear");
name:
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t UserName:");
    fgets(buffer,100,stdin);
    checkBuffer(buffer);
    int len = strlen(buffer);
    if (len == 0) {
        printf("\n\t Please don't enter empty values\n\n");
        goto name;
    }
    sscanf(buffer,"%s",a);

pass:
    printf("\n\n\n\n\n\t\t\t\tEnter your password:");
    fgets(buffer,100,stdin);
    checkBuffer(buffer);
    len = strlen(buffer);
    if (len == 0) {
        printf("\n\t Please don't enter empty values\n\n");
        goto pass;
    }
    sscanf(buffer,"%s",pass);


}

const char *getUserName(struct User u)
{
    FILE *fp;
    char data[256];

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening the file");
        exit(1);
    }

    while (fgets(data, sizeof(data), fp) != NULL)
    {
        char* piece = strtok(data, " ");
        piece = strtok(NULL, " ");
        if (strcmp(piece, u.name)==0) {
            fclose(fp);
            return piece;
        }
    }
    fclose(fp);
    return "no user found";
}

const char *getPassword(struct User u)
{
    FILE *fp;
    char data[256];

    if ((fp = fopen(USERS, "r")) == NULL)
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

const int setId()
{
    FILE *fp;
    char data[256];
    int count = 0;

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fgets(data,sizeof(data), fp ) != NULL)
    {
        count++; 
    }
    fclose(fp);
    return  count;   
}

const int getId(struct User u)
{
    FILE *fp;
    char data[256];
    char *initial;
    int id;

    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fgets(data,sizeof(data), fp ) != NULL)
    {
        char *piece = strtok(data, " ");
        initial = piece;
        piece = strtok(NULL, " ");
        if (strcmp(u.name, piece) == 0)
        {
            id = atoi(initial);
        }


    }
    fclose(fp);
    return id;
}

void saveUser(struct User *u)
{
    FILE *fp;
    if ((fp = fopen(USERS, "a")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    fprintf(fp, "%d %s %s\n", 
    u->id,
    u->name,
    u->password
    );

    fclose(fp);
}

