// Ashley Grafner
// 10/22/2024

//Assignment 7, Question 2:
//Create a file (source file) with 10 records
// read these records, arrange them in ascending order by join_date
//write them to target.dat file
//Additionally, will write out the sorted records to console

#include <stdio.h>

struct date { // Define a structure for the date
    int d, m, y;  // day, month, year (important for how we sort dates since month isn't first here)
};

// Define a structure for the employee
struct employee {
    int empcode[6];         // Array to store employee code
    char empname[40];       // Array to store employee name (changed from 20 to 40 characters)
    struct date join_date;  // Structure to store the join date
    float salary;           // Variable to store the salary
};

// Function to compare two dates
// Returns a positive number if date1 is later than date2, negative if earlier, and 0 if equal
int compare_dates(struct date date1, struct date date2) {
    if (date1.y != date2.y)
        return date1.y - date2.y;  // Compare years
    if (date1.m != date2.m)
        return date1.m - date2.m;  // Compare months if years are equal
    return date1.d - date2.d;      // Compare days if years and months are equal
}

// Function to sort employees based on their join date
void sort_employees(struct employee employees[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Compare join dates of two employees
            if (compare_dates(employees[j].join_date, employees[j + 1].join_date) > 0) {
                // Swap employees[j] and employees[j + 1] if they are out of order
                struct employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

// Writes the employee records to the specified file in a formatted manner
void write_to_file(const char *filename, struct employee employees[], int n) {
    FILE *file = fopen(filename, "w");  // Open the file for writing
    if (file == NULL) {  // Check if the file opened successfully
        printf("Error opening file for writing.\n");
        return;
    }
    // Loop through each employee and write their details to the file
    for (int i = 0; i < n; i++) {
        fprintf(file, "Emp Code: %d%d%d%d%d%d, Name: %s, Join Date: %02d/%02d/%d, Salary: %.2f\n",
                employees[i].empcode[0], employees[i].empcode[1], employees[i].empcode[2],
                employees[i].empcode[3], employees[i].empcode[4], employees[i].empcode[5],
                employees[i].empname, employees[i].join_date.d, employees[i].join_date.m,
                employees[i].join_date.y, employees[i].salary);
    }
    fclose(file);  // Close the file after writing
}

// Function to display employees on the console
// Prints the sorted employee records in a formatted manner
void display_employees(struct employee employees[], int n) {
    printf("Sorted Employee Records:\n");
    // Loop through each employee and print their details
    for (int i = 0; i < n; i++) {
        printf("Emp Code: %d%d%d%d%d%d, Name: %s, Join Date: %02d/%02d/%d, Salary: %.2f\n",
               employees[i].empcode[0], employees[i].empcode[1], employees[i].empcode[2],
               employees[i].empcode[3], employees[i].empcode[4], employees[i].empcode[5],
               employees[i].empname, employees[i].join_date.d, employees[i].join_date.m,
               employees[i].join_date.y, employees[i].salary);
    }
}

int main() {
    // Define the file name for source data
    const char *source_filename = "source.dat";

    // Initialize an array of 10 employees directly in the code
    struct employee employees[10] = {
        {{1, 2, 3, 4, 5, 6}, "Solaire of Astora", {1, 1, 2001}, 50000.00},
        {{2, 3, 4, 5, 6, 7}, "James Sunderland", {10, 7, 2000}, 60000.00},
        {{3, 4, 5, 6, 7, 8}, "Simon Jarett", {22, 5, 2019}, 55000.00},
        {{4, 5, 6, 7, 8, 9}, "Isaac Clarke", {30, 1, 2018}, 70000.00},
        {{5, 6, 7, 8, 9, 0}, "Leon Kennedy", {12, 4, 2019}, 75000.00},
        {{6, 7, 8, 9, 0, 1}, "Alexander of Brennenburg", {5, 2, 2021}, 45000.00},
        {{7, 8, 9, 0, 1, 2}, "Sekiro", {23, 2, 2020}, 48000.00},
        {{8, 9, 0, 1, 2, 3}, "Geralt of Rivia", {1, 11, 2018}, 52000.00},
        {{9, 0, 1, 2, 3, 4}, "Arya Stark", {18, 12, 2019}, 53000.00},
        {{0, 1, 2, 3, 4, 5}, "Katniss Everdeen", {1, 1, 2000}, 47000.00}
    };

    // Write initial records to source.dat
    write_to_file(source_filename, employees, 10);

    // Sort employees by join date
    sort_employees(employees, 10);

    // Write sorted records to a target file
    write_to_file("target.dat", employees, 10);

    // Display sorted records on the console
    display_employees(employees, 10);

    return 0;  // Indicate that the program ended successfully
}
