#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LENGTH 100
typedef struct
{
    unsigned month;
    unsigned year;
} date;
typedef struct
{
    char accountNumber[50];
    char firstName[100];
    char secondName[20];
    char email[40];
    float balance;
    char mobile[12];
    date d;
} client;
typedef struct
{
    char userName[15];
    char passWord[15];
} log;
void looper(client d[])
{
    char a;
    printf("press 1 to return to the menu or 0 to exit: ");
    scanf(" %c",&a);
    switch(a)
    {
    case '0':
    {
        quit();
        break;
    }
    case '1':
    {
        printf("\n");
        menu(d);
        break;
    }
    default:
    {
        printf("invalid entery.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {};
        looper(d);
        break;
    }
    }
}
int isAccountExist(client arr[],char acc[],int account_number)
{
    int i=0,flag=0;
    if(strcmp(acc, "z") == 0)looper(arr);
    for(i=0; i<account_number; i++)
    {
        if(strcmp(acc,arr[i].accountNumber)==0)
        {
            printf("Account found!\n");
            return 1;
        }

    }
    return 0;
}
char*tr(unsigned i)
{
    switch(i)
    {
    case 1:
        return "january";
    case 2:
        return "february";
    case 3:
        return "march";
    case 4:
        return "april";
    case 5:
        return "may";
    case 6:
        return "june";
    case 7:
        return "july";
    case 8:
        return "august";
    case 9:
        return "september";
    case 10:
        return "october";
    case 11:
        return "november";
    case 12:
        return "december";
    }
}
void auto_date(int *day,int *month, int *year,int *hour,int *minute)
{
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    *day = localTime->tm_mday;
    *month = localTime->tm_mon + 1;
    *year = localTime->tm_year + 1900;
    *hour = localTime->tm_hour;
    *minute = localTime->tm_min;
}
int find_account(client *x,int numofaccounts,char *accountnumber)
{
    int acc_Index;
    for(acc_Index=0; acc_Index<numofaccounts; acc_Index++)
    {
        if(strcmp(x[acc_Index].accountNumber,accountnumber)==0)
        {
            return acc_Index;
        }
    }
    return -1;
}
int check_number(client *d,char phone_number[])
{
    if(strcmp(phone_number, "z") == 0)looper(d);
    if (strlen(phone_number) != 11)
    {
        return 0;
    }
    for (int i = 0; i < strlen(phone_number); i++)
    {
        if (phone_number[i] < '0' || phone_number[i] > '9')
        {
            return 0;
        }
    }
    return 1;
}
int check_account(client *d,char account_number[])
{
    if(strcmp(account_number, "z") == 0)looper(d);
    if (strlen(account_number) != 10)
    {
        printf("The account number must be exactly 10 numbers.\n");
        return 0;
    }
    for (int i = 0; i < 10; i++)
    {
        if (account_number[i] < '0' || account_number[i] > '9')
        {
            printf("The account number must contain only numbers.\n");
            return 0;
        }
    }
    return 1;
}
int check_email(char email[])
{
    int flag1=0,flag2=0;
    for(int i=0; i<strlen(email); i++)
    {
        if(email[i] == '@')flag1=1;
        else if(email[i] == '.')flag2=1;
    }
    if(flag1 && flag2)return 1;
    else printf("Invalid email, ");
    return 0;
}
void sortbyname(client *x,int numberofaccounts)
{

    for(int i=0; i<numberofaccounts; i++)
    {
        for(int j=i+1; j<numberofaccounts; j++)
        {
            if(strcmp(x[j].firstName,x[i].firstName)<0)
            {
                client temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
            if(strcmp(x[j].firstName,x[i].firstName)==0)
            {
                if(strcmp(x[j].secondName,x[i].secondName)<0)
                {
                    client temp = x[i];
                    x[i] = x[j];
                    x[j] = temp;
                }
            }
        }
    }
}
void sortbybalance(client *x,int numberofaccounts)
{
    for(int i=0; i<numberofaccounts; i++)
    {
        for(int j=i+1; j<numberofaccounts; j++)
        {
            if(x[j].balance > x[i].balance)
            {
                client temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
}
void sortbydate(client *x,int numberofaccounts)
{
    for(int i=0; i<numberofaccounts; i++)
    {
        for(int j=i+1; j<numberofaccounts; j++)
        {
            if(x[j].d.year < x[i].d.year)
            {
                client temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
            else if(x[j].d.year == x[i].d.year)
            {
                if(x[j].d.month < x[i].d.month)
                {
                    client temp = x[i];
                    x[i] = x[j];
                    x[j] = temp;
                }
            }
        }
    }
}
void update_wd(char x[20], int type, float amount)
{
    char arr[100][50];
    int i = 0;
    FILE *t = fopen(x, "r+");

    if (t == NULL)
    {
        t = fopen(x, "w");
        fclose(t);
    }
    else
    {
        while (fscanf(t, "%[^\n]\n", arr[i]) == 1)
        {
            i++;
        }
        fclose(t);
    }

    t = fopen(x, "w");
    if (i < 5)
    {
        for (int j = 0; j < i; j++)
        {
            fprintf(t, "%s\n", arr[j]);
        }
    }
    else
    {
        for (int j = 1; j < i; j++)
        {
            fprintf(t, "%s\n", arr[j]);
        }
    }

    if (type)
    {
        fprintf(t, "withdrawn,%.2f\n", amount);
    }
    else
    {
        fprintf(t, "deposited,%.2f\n", amount);
    }
    fclose(t);
}

void update_t(char x[30], char z[30], float amount)
{
    char arr1[5][50];
    char arr2[5][50];
    int i = 0;
    FILE *t = fopen(x, "r+");
    FILE *q = fopen(z, "r+");

    if (t == NULL)
    {
        t = fopen(x, "w");
        fclose(t);
    }
    else
    {
        while (fscanf(t, "%[^\n]\n", arr1[i]) == 1)
        {
            i++;
        }
        fclose(t);
    }

    t = fopen(x, "w");
    if (i < 5)
    {
        for (int j = 0; j < i; j++)
        {
            fprintf(t, "%s\n", arr1[j]);
        }
    }
    else
    {
        for (int j = 1; j < i; j++)
        {
            fprintf(t, "%s\n", arr1[j]);
        }
    }
    fprintf(t, "sent,%.2f\n", amount);
    fclose(t);

    i = 0;
    if (q == NULL)
    {
        q = fopen(z, "w");
        fclose(q);
    }
    else
    {
        while (fscanf(q, "%[^\n]\n", arr2[i]) == 1)
        {
            i++;
        }
        fclose(q);
    }

    q = fopen(z, "w");
    if (i < 5)
    {
        for (int j = 0; j < i; j++)
        {
            fprintf(q, "%s\n", arr2[j]);
        }
    }
    else
    {
        for (int j = 1; j < i; j++)
        {
            fprintf(q, "%s\n", arr2[j]);
        }
    }
    fprintf(q, "received,%.2f\n", amount);
    fclose(q);
}


int load(client d[])
{
    FILE *f = fopen("accounts.txt", "r");
    if (f == NULL)
    {
        printf("Error in opening file\n");
        return 0;
    }
    int i=0;
    while (i < 100 && !feof(f))
    {
        fscanf(f, "%[^,], %[^ ] %[^,], %[^,], %f, %[^,], %u-%u\n",
               d[i].accountNumber, d[i].firstName, d[i].secondName, d[i].email,
               &d[i].balance, d[i].mobile, &d[i].d.month, &d[i].d.year);
        i++;
    }
    return i;
}
int load_Login(log d[])
{
    FILE *f1 = fopen("users.txt", "r");
    if (f1 == NULL)
    {
        printf("Error in opening file\n");
        return 0;
    }

    int i = 0;
    while (i < 15)
    {
        fscanf(f1, "%s %s", d[i].userName, d[i].passWord);
        i++;
    }
    fclose(f1);
    return i;
}

int login(log d[])
{
    int i,j,flag=0,day,month,year,hour,minute;
    char user[50];
    char password[50];

    printf("Welcome To the SSP Bank Managment system !\n");
    auto_date(&day,&month,&year,&hour,&minute);
    printf("today's date is %d-%d-%d\n",day,month,year);
    printf("local time is %d:%d\n\n",hour,minute);

    for (j = 0; j < 3; j++)
    {
        printf("Enter the username:");
        scanf("%s", user);
        printf("Enter the password:");
        scanf("%s", password);
        for (i = 0; i < load_Login(d); i++)
        {
            if (strcmp(password, d[i].passWord) == 0 && strcmp(user, d[i].userName) == 0)
            {
                printf("login success.\n");
                printf("Welcome %s!\n\n",user);
                return 1;
            }
        }
        if (j < 2)
        {
            printf("Incorrect Username or Password\nyou have %d trials\n",2-j);
        }
        else if (j == 2)
        {
            printf("Login failed. Exiting...\n");
            exit(1);
        }
    }

    printf("Login failed. Trials exceeded.\n");
    return 0;
}
void menu(client d[])
{
    char a[10];
    printf("1. ADD\n2. Delete\n3. Modify\n4. Search\n5. Advanced Search\n6. Withdraw\n7. Deposit\n8. Transfer\n9. Report\n10. Print\n11. quit\n\nPlease Choose A Service: ");
    scanf(" %9s", a);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (strcmp(a, "1") == 0)
    {
        add(d);
    }
    else if (strcmp(a, "2") == 0)
    {
        deleteAccount(d, load(d));
    }
    else if (strcmp(a, "3") == 0)
    {
        modifyAccount(d, load(d));
        load(d);
    }
    else if (strcmp(a, "4") == 0)
    {
        search(d, load(d));
    }
    else if (strcmp(a, "5") == 0)
    {
        advancedSearch(d, load(d));
    }
    else if (strcmp(a, "6") == 0)
    {
        withdraw(d, load(d));
    }
    else if (strcmp(a, "7") == 0)
    {
        deposit(d, load(d));
    }
    else if (strcmp(a, "8") == 0)
    {
        transfer(d, load(d));
    }
    else if (strcmp(a, "9") == 0)
    {
        report(d);
    }
    else if (strcmp(a, "10") == 0)
    {
        print(d, load(d));
        load(d);
    }
    else if (strcmp(a, "11") == 0)
    {
        quit();
    }
    else
    {
        printf("Invalid choice.\n");
        looper(d);
    }
}
void add(client d[])
{
    char first_name[50], second_name[50], email[50], acc[50], num[50];
    int month, year,minute,hour,day;
    float balance;

    auto_date(&day,&month, &year,&hour,&minute);


    while (1)
    {
        printf("enter account number (z to quit): ");
        gets(acc);
        if (isAccountExist(d,acc,load(d)))
        {
            printf("Acount number is already in use\n");
        }
        else if (!check_account(d,acc))
        {
            printf("Enter a valid account number (10 digits)\n");
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        printf("enter phone number of the user : ");
        gets(num);
        if (!check_number(d,num))
        {
            printf("Enter a valid phone number (11 digits)\n");
        }
        else
        {
            break;
        }
    }

    printf("enter the first name of the user : ");
    gets(first_name);
    printf("enter the last name of the user : ");
    gets(second_name);
    do
    {
        printf("enter the email of the user (example@eg.com): ");
        gets(email);
    }
    while(!check_email(email));
    printf("enter the balance of the user : ");
    scanf("%f", &balance);
    int f = load(d);
    strcpy(d[f].accountNumber, acc);
    strcpy(d[f].firstName, first_name);
    strcpy(d[f].secondName, second_name);
    strcpy(d[f].email, email);
    d[f].balance = balance;
    strcpy(d[f].mobile, num);
    d[f].d.month = month;
    d[f].d.year = year;
    if(save(d,f+1))
    {
        strcat(acc,".txt");
        FILE *z = fopen(acc,"w");
        fclose(z);
    }
    looper(d);
}
void deleteAccount(client d[],int c)
{
    char se[11];

    do
    {
        printf("enter account number that you want to delete (z to quit): ");
        scanf("%s",se);
    }
    while(!check_account(d,se) ||!isAccountExist(d,se,c));
    int i;
    for (int i=0; i<c; i++)
        if (strcmp(d[i].accountNumber,se)==0)
        {
            if(d[i].balance==0)
            {
                for(i; i<c; i++)
                    d[i]=d[i+1];
                c--;
            }
            else
            {
                printf("Can't delete an account with balance greater than zero.\n");
                looper(d);
            }
        }

    if(save(d,c))
    {
        strcat(se,".txt");
        remove(se);
        printf("Account deleted successfully.\n");
    }
    else printf("account not deleted.\n");
    looper(d);
}
void modifyAccount(client d[],int z)
{
    char accToModify[MAX_LENGTH];
    int choice,i;
    char newFName[MAX_LENGTH];
    char newLName[MAX_LENGTH];
    char newEmail[MAX_LENGTH];
    char newPhone[MAX_LENGTH];
    char line[265];
    do
    {
        printf("Enter the account number to be modified (z to quit): ");
        scanf("%s", accToModify);
    }
    while(!check_account(d,accToModify) || !isAccountExist(d,accToModify,z));
    printf("Select data to modify:\n1. Name\n2. Email\n3. Phone Number\nEnter choice: ");
    scanf("%d", &choice);
    for (i = 0; i < z; i++)
    {
        if (strcmp(d[i].accountNumber, accToModify) == 0)
        {
            switch (choice)
            {
            case 1:
                printf("Enter new first name: ");
                scanf("%s", newFName);
                printf("Enter new last name: ");
                scanf("%s", newLName);
                strcpy(d[i].firstName, newFName);
                strcpy(d[i].secondName, newLName);
                break;
            case 2:
                do
                {
                    printf("Enter new email (example@eg.com): ");
                    scanf("%s", newEmail);
                }
                while(!check_email(newEmail));
                strcpy(d[i].email, newEmail);
                break;
            case 3:
                printf("Enter new phone number: ");
                scanf("%s", newPhone);
                strcpy(d[i].mobile, newPhone);
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            break;
        }
    }
    if(save(d,z));
    looper(d);
}
void search(client d[],int c)
{
    char se[20];
    printf("Enter the account number that you want to search (z to quit): ");
    scanf("%s",se);
    if (!check_account(d,se))
    {
        search(d, c);
        return;
    }

    if (!isAccountExist(d, se, c))
    {
        printf("There is no account with this number.\n");
        search(d, c);
        return;
    }
    for (int i=0; i<c; i++)
        if (strcmp(d[i].accountNumber,se)==0)
        {
            printf("Account number: %s\n",d[i].accountNumber);
            printf("Name: %s %s\n",d[i].firstName,d[i].secondName);
            printf("Email: %s\n",d[i].email);
            printf("Balance: %.2f$\n",d[i].balance);
            printf("Mobile: %s\n",d[i].mobile);
            printf("Date: %s %u\n",tr(d[i].d.month),d[i].d.year);
            printf("\n");
        }
    looper(d);
}
void advancedSearch(client d[], int c)
{
    char ad[20];
    int found=0;
    printf("Enter the name that you want to search (z to quit): ");
    scanf("%s",ad);
    if(strcmp(ad,"z")==0)looper(d);
    for (int i = 0; i < c; i++)
    {
        if (strcasecmp(d[i].firstName, ad) == 0 || strcasecmp(d[i].secondName, ad) == 0)
        {
            found = 1;
            printf("Account number: %s\n", d[i].accountNumber);
            printf("Name: %s %s\n", d[i].firstName, d[i].secondName);
            printf("Email: %s\n", d[i].email);
            printf("Balance: %.2f$\n", d[i].balance);
            printf("Mobile: %s\n", d[i].mobile);
            printf("Date: %s %u\n", tr(d[i].d.month), d[i].d.year);
            printf("\n");
        }

    }
    if(!found)
    {
        printf("There is no account containing this name.");
        advancedSearch(d,c);
    }
    looper(d);
}
void withdraw(client *x,int numofaccounts)
{
    char account_number[100];
    float amount;
    char amount_str[100];
    do
    {
        printf("Enter the account number (z to quit): ");
        scanf("%s",account_number);
    }
    while(!check_account(x,account_number));

    int accIndex=find_account(x,numofaccounts,account_number);
    if(accIndex!=-1)
    {
        printf("Please enter the amount to be withdrawn: ");
        scanf("%s",amount_str);
        while(sscanf(amount_str,"%f",&amount)!=1||amount<=0||amount>10000)
        {
            if(amount <= 0)
                printf("Invalid amount.\nplease enter a valid amount that is bigger than 0$: ");
            else if(amount>10000)
                printf("Invalid amount.\nIf you want to withdraw a larger amount, you can withdraw the amount in batches.\nPlease enter a valid amount that don't exceed 10000$: ");
            else
            {
                printf("error scanning amount please try again later..");
                looper(x);
            }
            scanf("%s", amount_str);
        }
        if(x[accIndex].balance<amount)
        {
            printf("Insufficient funds.\n");
            printf("Please re-enter the account number from the beginning and enter amount that is available on your account to withdraw.\n");
            withdraw(x,numofaccounts);
        }
        else
        {
            x[accIndex].balance-=amount;
            printf("Transaction is done successfully.\nThe new balance is %.2f.\n",x[accIndex].balance);
            if(!save(x,numofaccounts))x[accIndex].balance+=amount;
            else
            {
                strcat(account_number,".txt");
                update_wd(account_number,1,amount);
            }
        }
    }
    else
    {
        printf("Account number is not found on the system.\n");
    }
    looper(x);
}
void deposit(client *x,int numofaccounts)
{
    char account_number[100];
    float amount;
    char amount_str[100];
    do
    {
        printf("Enter the account number (z to quit):");
        scanf("%s",account_number);
    }
    while(!check_account(x,account_number));
    int accIndex=find_account(x,numofaccounts,account_number);
    if(accIndex!=-1)
    {
        printf("Please enter the amount to be deposited:");
        scanf("%s",amount_str);
        while(sscanf(amount_str,"%f",&amount)!=1||amount<=0||amount>10000)
        {
            printf("Invalid amount.\nIf you want to deposit a larger amount, you can deposit the amount in batches.\nPlease enter a valid amount that don't exceed 10000$: ");
            scanf("%s", amount_str);
        }

        x[accIndex].balance+=amount;
        printf("Transaction is done successfully.\nThe new balance is %.2f.\n",x[accIndex].balance);
        if(!save(x,numofaccounts)) x[accIndex].balance-=amount;
        else
        {
            strcat(account_number,".txt");
            update_wd(account_number,0,amount);
        }
    }
    else
    {
        printf("Account number is not found on the system.\n");

    }
    looper(x);
}
void transfer(client *x,int numofaccounts)
{
    char sender[20];
    char reciver[20];
    float amount;
    int found_send=0,found_rec=0;
    do
    {
        printf("Enter valid sender account number (z to quit): ");
        scanf("%s",sender);
    }
    while(!check_account(x,sender));
    do
    {
        printf("Enter reciver account number (z to quit): ");
        scanf("%s",reciver);
    }
    while(!check_account(x,reciver));
    int counter1,counter2;
    for(counter1=0; counter1<100; counter1++)
    {
        if(stricmp(sender,x[counter1].accountNumber)==0)
        {
            found_send=1;
            for(counter2=0; counter2<100; counter2++)
            {
                if(stricmp(reciver,x[counter2].accountNumber)==0)
                {
                    found_rec=1;
                    break;
                }
            }
            break;
        }
    }
    if(!found_send)printf("Sender not found\n");
    if(!found_rec)printf("reciver not found");
    if(found_send && found_rec)
    {
        printf("Sender found\n");
        printf("reciver found\n");
        printf("Enter amount of money: ");
        scanf("%f",&amount);
        if(x[counter1].balance>=amount)
        {

            printf("sender's old balance= %.2f , reciver's old balance = %.2f\n",x[counter1].balance,x[counter2].balance);
            x[counter1].balance -= amount;
            x[counter2].balance += amount;
            printf("sender's new balance= %.2f , reciver's new balance = %.2f\n",x[counter1].balance,x[counter2].balance);
            char s[20];
            char r[20];
            if(save(x,numofaccounts))
            {
                strcpy(s,x[counter1].accountNumber);
                strcpy(r,x[counter2].accountNumber);
                strcat(s,".txt");
                strcat(r,".txt");
                update_t(s,r,amount);
            }
            else
            {
                x[counter1].balance += amount;
                x[counter2].balance -= amount;
            }
        }
        else
        {
            printf("not enough balance in senders account");
        }
    }
    looper(x);
}
void report(client *x)
{

    char transaction[20];
    char accn[10];
    float amount;
    do
    {
        printf("please enter account number (z to quit): ");
        scanf("%s",accn);
    }
    while(!check_account(x,accn));
    strcat(accn,".txt");
    FILE *f = fopen(accn,"r");
    if(f == NULL)
    {
        printf("No transactions have been made before in this account.\n");
        looper(x);
    }
    int i=1;
    if(fscanf(f,"%[^,],%f\n",transaction,&amount)==EOF)printf("No transactions have been made before in this account.\n");
    else
    {
        rewind(f);
        while(!feof(f) && i<6)
        {
            fscanf(f,"%[^,],%f\n",transaction,&amount);
            printf("Transaction #%d : The account %s an amount = %.2f$\n",i,transaction,amount);
            i++;
        }
    }
    looper(x);
}
void print(client *x,int numberofaccounts)
{
    int way;
    printf("please enter the sorting way: \n");
    printf("1)Name.\n2)balance.\n3)date.\n0) to quit: ");
    scanf("%d",&way);
    printf("\n");
    switch(way)
    {
    case 0:
        looper(x);
    case 1:
    {
        sortbyname(x,numberofaccounts);
        for(int i=0; i<numberofaccounts; i++)
        {
            printf("Account number: %s\n",x[i].accountNumber);
            printf("Name: %s %s\n",x[i].firstName,x[i].secondName);
            printf("Email: %s\n",x[i].email);
            printf("Mobile: %s\n",x[i].mobile);
            printf("Balance: %.2f$\n",x[i].balance);
            printf("Date: %u-%u\n",x[i].d.month,x[i].d.year);
            printf("\n");
        }
        break;
    }
    case 2:
    {
        sortbybalance(x,numberofaccounts);
        for(int i=0; i<numberofaccounts; i++)
        {
            printf("Account number: %s\n",x[i].accountNumber);
            printf("Name: %s %s\n",x[i].firstName,x[i].secondName);
            printf("Email: %s\n",x[i].email);
            printf("Mobile: %s\n",x[i].mobile);
            printf("Balance: %.2f$\n",x[i].balance);
            printf("Date: %u-%u\n",x[i].d.month,x[i].d.year);
            printf("\n");
        }
        break;
    }
    case 3:
    {
        sortbydate(x,numberofaccounts);
        for(int i=0; i<numberofaccounts; i++)
        {
            printf("Account number: %s\n",x[i].accountNumber);
            printf("Name: %s %s\n",x[i].firstName,x[i].secondName);
            printf("Email: %s\n",x[i].email);
            printf("Mobile: %s\n",x[i].mobile);
            printf("Balance: %.2f$\n",x[i].balance);
            printf("Date: %u-%u\n",x[i].d.month,x[i].d.year);
            printf("\n");
        }
        break;
    }


    }
    looper(x);

}
int save(client *x,int numofaccounts)
{
    int valid;
    printf("If you want to save your changes please enter 1 and if you don't please enter 0:\t");
    scanf("%d",&valid);
    if(valid)
    {
        FILE *f=fopen("accounts.txt", "w");
        if (f==NULL)
        {
            printf("Error in opening the file.\n");
            return 0;
        }
        for (int i=0; i<numofaccounts; i++)
        {
            fprintf(f,"%s,%s %s,%s,%.2f,%s,%d-%d\n", x[i].accountNumber,x[i].firstName,x[i].secondName,x[i].email,x[i].balance,x[i].mobile,x[i].d.month,x[i].d.year);
        }
        printf("The changes you have been save successfully.\n");
        fclose(f);
        return 1;
    }
    else
    {
        printf("The changes you made haven't been saved.\n");
        return 0;
    }
}
void quit()
{
    printf("Have a wonderful day !");
    exit(1);
}
int main()
{
    client d[100];
    load(d);
    log x[5];
    load_Login(x);
    login(x);
    if(login)
        menu(d);
    return 0;
}
