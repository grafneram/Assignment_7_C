// Ashley Grafner
// 10/22/2024

//Assignment 7, Question 1:
//Will update the balance of the account in CUSTOMER.DAT file. If cannot, then print an error message.
//Will display the FINAL balance after all transactions are processed to console as well.

// If trans_type = 'D', Updates CUSTOMER.DAT file with adding amount to balance
// If trans_type = 'W', subtract amount from balance and cannot be overdrawn
// At least 100$ should remain in the account

#include <stdio.h>

struct customer { // Define a structure to represent a customer
    int accno;          // Account number
    char name[30];     // Customer's name
    float balance;     // Customer's balance
};

struct trans { // Define a structure to represent a transaction
    int accno;          // Account number associated with the transaction
    char trans_type;    // Transaction type ('D' for deposit, 'W' for withdrawal)
    float amount;      // Amount of money involved in the transaction
};

// Function to create and write customer records to a binary file
void create_customers_file() {
    struct customer customers[] = { // Array of customers to be written to the file
        {35007, "Tim Cook", 500},
        {35008, "Daniel Brown", 1600},
        {35009, "CeCe Gilroy", 220},
        {35010, "Johny Mat", 317},
        {35011, "Drew Filmore", 321},
        {35012, "Natalie Day", 190},
        {35013, "Olivia Cobb", 543},
        {35014, "Mat Fullerton", 270},
        {35015, "Noel Ken", 289},
        {35016, "Chris Gill", 965}
    };

    // Open file for writing in binary mode
    FILE *file = fopen("CUSTOMER.DAT", "wb");
    if (file == NULL) {
        perror("Error creating CUSTOMER.DAT");
        return;  // Exit the function if file cannot be created
    }
    // Write customers to the file
    fwrite(customers, sizeof(struct customer), 10, file);
    fclose(file);  // Close the file

    printf("CUSTOMER.DAT created successfully.\n");
}

// Function to create and write transaction records to a binary file
void create_transactions_file() {
    struct trans transactions[] = {  // Array of transactions to be written to the file
        {35007, 'D', 20}, {35008, 'W', 13}, {35009, 'D', 25},
        {35010, 'D', 79}, {35011, 'W', 43}, {35012, 'D', 63},
        {35013, 'W', 22}, {35014, 'W', 231}, {35015, 'W', 56},
        {35016, 'D', 12}, {35007, 'D', 33}, {35008, 'W', 43},
        {35009, 'D', 32}, {35010, 'W', 12}, {35011, 'W', 12},
        {35012, 'W', 43}, {35013, 'D', 76}, {35014, 'D', 78},
        {35015, 'W', 9}, {35016, 'D', 76}, {35007, 'W', 77},
        {35008, 'W', 78}, {35009, 'W', 79}, {35010, 'D', 80},
        {35011, 'D', 81}, {35012, 'W', 82}, {35013, 'D', 83},
        {35014, 'W', 84}, {35015, 'W', 85}, {35016, 'W', 86}
    };

    // Open file for writing in binary mode
    FILE *file = fopen("TRANSACTIONS.DAT", "wb");
    if (file == NULL) {
        perror("Error creating TRANSACTIONS.DAT");
        return;  // Exit the function if file cannot be created
    }
    // Write transactions to the file
    fwrite(transactions, sizeof(struct trans), 30, file);
    fclose(file);  // Close the file

    printf("TRANSACTIONS.DAT created successfully.\n");
}

// Function to update a customer's balance based on the transaction
void update_balance(struct customer *cust, struct trans *transaction) {
    if ((*transaction).trans_type == 'D') {
        // If the transaction is a deposit, increase the customer's balance
        (*cust).balance += (*transaction).amount;
    } else if ((*transaction).trans_type == 'W') {
        // If the transaction is a withdrawal, check if the balance will be >= 100
        if ((*cust).balance - (*transaction).amount < 100) {
            // If insufficient funds, print an error message
            printf("\nError: Insufficient funds for account %d. Minimum balance of $100 must remain in account.\n", (*cust).accno);
        } else { // If sufficient funds, decrease the customer's balance
            (*cust).balance -= (*transaction).amount;
        }
    }
}

// Function to print the final balances of all customers
void print_final_balances(struct customer *custs, int cust_count) {
    printf("\nFinal Balances:\n");
    printf("Account#  Name                Balance in USD\n");
    for (int i = 0; i < cust_count; i++) {
        // Print each customer's account number, name, and balance
        printf("%-10d %-20s %.2f\n", custs[i].accno, custs[i].name, custs[i].balance);
    }
}

int main() {
    create_customers_file();  // Create the CUSTOMER.DAT file
    create_transactions_file(); //Create the TRANSACTIONS.DAT file

    FILE *cust_file, *trans_file; // File pointers for customer and transaction files
    struct customer customers[10]; // Array to hold customer records
    struct trans transaction;       // Variable to hold a single transaction
    int cust_count = 0;            // Counter for the number of customers

    // Open CUSTOMER.DAT file for reading
    cust_file = fopen("CUSTOMER.DAT", "rb");
    if (cust_file == NULL) {
       printf("Error opening CUSTOMER.DAT");
        return 1;  // Exit if the file cannot be opened
    }

    // Read customer records from the file
    while (fread(&customers[cust_count], sizeof(struct customer), 1, cust_file) == 1) {
        cust_count++;  // Increment the customer count
    }
    fclose(cust_file);  // Close the customer file

    // Open TRANSACTIONS.DAT file for reading
    trans_file = fopen("TRANSACTIONS.DAT", "rb");
    if (trans_file == NULL) {
        printf("Error opening TRANSACTIONS.DAT");
        return 1;  // Exit if the file cannot be opened
    }

    // Process each transaction
    while (fread(&transaction, sizeof(struct trans), 1, trans_file) == 1) {
        // Find the corresponding customer for the transaction
        for (int i = 0; i < cust_count; i++) {
            if (customers[i].accno == transaction.accno) {
                // Update the balance for the matching customer
                update_balance(&customers[i], &transaction);
                break;  // Exit the loop once the customer is found
            }
        }
    }
    fclose(trans_file);  // Close the transaction file
    printf("\nProcessing transactions...\n");
    print_final_balances(customers, cust_count); // Print final balances after all transactions are processed

    return 0;  // Indicate successful program termination
}