#include "header.h"

void mainMenu(struct User u)
{
begin:
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);
    getchar();

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateInfo(u);
        break;
    case 3:
        checkDetails(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        makeTransaction(u);
        break;
    case 6:
        removeAccount(u);
        break;
    case 7:
        transferOwner(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        goto begin;
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    char initial[100];
    int r = 0;
    int option;
    system("clear");
entry:
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {

        fgets(initial,100,stdin);
        checkBuffer(initial);
        if (checkValidType(initial, "int") != 0)
        {
            printf("\n\t\t✖ Please!! Enter a valid option\n");
            goto entry;
        }
        sscanf(initial, "%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nPassword Match!");
                u->id = getId(*u);
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            registerUser(u->name, u->password);
            if (strcmp(u->name, getUserName(*u)) == 0)
            {
                printf("\n\nUser name already taken\n");
                exit(1);
            }
            u->id = setId();
            saveUser(u);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
};

int main()
{
    struct User u;

    initMenu(&u);
    mainMenu(u);
    return 0;
}
