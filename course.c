#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "transactions.txt"

// Structure to hold transaction data
struct Transaction {
    char date[15];
    char description[100];
    float amount;
};

// Function to add a new transaction to the file
void addTransaction() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Transaction newTransaction;

    printf("\nEnter transaction details:\n");
    printf("Date (DD-MM-YYYY): ");
    scanf("%s", newTransaction.date);
    printf("Description: ");
    scanf(" %[^\n]", newTransaction.description);
    printf("Amount: ");
    scanf("%f", &newTransaction.amount);

    fprintf(file, "%s,%s,%.2f\n", newTransaction.date, newTransaction.description, newTransaction.amount);
    fclose(file);
    printf("Transaction added successfully!\n");
}

// Function to view all transactions from the file
void viewTransactions() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No transactions recorded yet.\n");
        return;
    }

    struct Transaction currentTransaction;
    char line[200];
    printf("\n--- All Transactions ---\n");

    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, ",");
        strcpy(currentTransaction.date, token);

        token = strtok(NULL, ",");
        strcpy(currentTransaction.description, token);

        token = strtok(NULL, ",");
        currentTransaction.amount = atof(token);

        printf("Date: %s, Description: %s, Amount: %.2f\n", currentTransaction.date, currentTransaction.description, currentTransaction.amount);
    }
    fclose(file);
}

// Function to calculate and display the current balance
void checkBalance() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No transactions to calculate balance.\n");
        return;
    }

    float balance = 0.0;
    char line[200];

    while (fgets(line, sizeof(line), file)) {
        char *token;
        strtok(line, ","); // Skip date
        strtok(NULL, ","); // Skip description
        token = strtok(NULL, ",");
        balance += atof(token);
    }
    fclose(file);

    printf("\n--- Current Balance ---\n");
    printf("Total Balance: %.2f\n", balance);
}

int main() {
    int choice;
    do {
        printf("\n\n--- Personal Finance Tracker Menu ---\n");
        printf("1. Add Transaction\n");
        printf("2. View All Transactions\n");
        printf("3. Check Balance\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTransaction();
                break;
            case 2:
                viewTransactions();
                break;
            case 3:
                checkBalance();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
