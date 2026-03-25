#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    char password[30];
    float balance;
};

void registerUser();
int loginUser(int *index);
void bankingMenu(int index);
void deposit(int index);
void withdraw(int index);
void transfer(int index);
void changePassword(int index);

struct Account acc[100];
int total = 0;



void loadAccounts() {
    FILE *fp = fopen("bank.dat", "rb");
    if (fp == NULL) return;

    fread(&total, sizeof(int), 1, fp);
    fread(acc, sizeof(struct Account), total, fp);
    fclose(fp);
}

void saveAccounts() {
    FILE *fp = fopen("bank.dat", "wb");
    fwrite(&total, sizeof(int), 1, fp);
    fwrite(acc, sizeof(struct Account), total, fp);
    fclose(fp);
}


void registerUser() {
    printf("\nRegistration \n");

    acc[total].accNo = 1000 + total + 1;

    printf("Enter name: ");
    scanf("%s", acc[total].name);

    printf("Create password: ");
    scanf("%s", acc[total].password);

    acc[total].balance = 0;

    printf("Account created successfully!\n");
    printf("Your Account Number: %d\n", acc[total].accNo);

    total++;
    saveAccounts();
}



int loginUser(int *index) {
    int no;
    char pass[30];

    printf("\n--- Login ---\n");
    printf("Account Number: ");
    scanf("%d", &no);

    printf("Password: ");
    scanf("%s", pass);

    for (int i = 0; i < total; i++) {
        if (acc[i].accNo == no && strcmp(acc[i].password, pass) == 0) {
            *index = i;
            return 1;
        }
    }

    return 0;
}



void deposit(int index) {
    float amt;
    printf("Enter amount to deposit: ");
    scanf("%f", &amt);

    if (amt > 0) {
        acc[index].balance += amt;
        saveAccounts();
        printf("Deposit successful!\n");
    } else {
        printf("Invalid amount\n");
    }
}



void withdraw(int index) {
    float amt;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amt);

    if (amt <= acc[index].balance && amt > 0) {
        acc[index].balance -= amt;
        saveAccounts();
        printf("Withdrawal successful!\n");
    } else {
        printf("Insufficient balance!\n");
    }
}

/* ================= TRANSFER ================= */

void transfer(int index) {
    int target;
    float amt;

    printf("Enter target account number: ");
    scanf("%d", &target);

    printf("Enter amount: ");
    scanf("%f", &amt);

    for (int i = 0; i < total; i++) {
        if (acc[i].accNo == target) {
            if (amt <= acc[index].balance && amt > 0) {
                acc[index].balance -= amt;
                acc[i].balance += amt;
                saveAccounts();
                printf("Transfer successful!\n");
                return;
            } else {
                printf("Not enough balance\n");
                return;
            }
        }
    }

    printf("Target account not found\n");
}

/* ================= CHANGE PASSWORD ================= */

void changePassword(int index) {
    char newpass[30];
    printf("Enter new password: ");
    scanf("%s", newpass);

    strcpy(acc[index].password, newpass);
    saveAccounts();
    printf("Password changed successfully!\n");
}

/* ================= MENU ================= */

void bankingMenu(int index) {
    int ch;

    do {
        printf("\n--- Banking Menu ---\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Transfer Money\n");
        printf("4. Change Password\n");
        printf("5. Check Balance\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1: deposit(index); break;
        case 2: withdraw(index); break;
        case 3: transfer(index); break;
        case 4: changePassword(index); break;
        case 5:
            printf("Balance: %.2f\n", acc[index].balance);
            break;
        case 0:
            printf("Logged out\n");
            break;
        default:
            printf("Invalid choice\n");
        }

    } while (ch != 0);
}

/* ================= MAIN ================= */

int main() {
    int choice, idx;

    loadAccounts();

    do {
        printf("\n==== ONLINE BANKING SYSTEM ====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            registerUser();
            break;

        case 2:
            if (loginUser(&idx)) {
                printf("Login successful!\n");
                bankingMenu(idx);
            } else {
                printf("Invalid login details\n");
            }
            break;

        case 0:
            printf("Goodbye\n");
            break;

        default:
            printf("Invalid choice\n");
        }

    } while (choice != 0);

    return 0;
}
