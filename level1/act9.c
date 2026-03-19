#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMP 50
#define NAME_LEN 50

typedef struct {
    int id;
    char name[NAME_LEN];
    double salary; // Changed to double for higher precision
} Employee;

void inputEmployees(Employee e[], int n);
void writeToTextFile(Employee e[], int n, const char *filename);
double calculateTotalPayroll(const char *filename); // Returns double
void displayExpenditure(double total); // Accepts double

int main() {
    // Clean buffer for fresh run
    setvbuf(stdout, NULL, _IONBF, 0);
    
    int n;
    printf("enter the number of employees :\n");
    if (scanf("%d", &n) != 1) return 1; // Basic validation

    // Edge Case 1: Handle 0 or negative employees
    if (n <= 0) {
        displayExpenditure(0.0);
        return 0;
    }
    
    // Edge Case 3: Cap at MAX_EMP to prevent array overflow
    if (n > MAX_EMP) n = MAX_EMP;

    Employee emp[MAX_EMP];
    const char *filename = "payroll.txt";
    
    inputEmployees(emp, n);
    writeToTextFile(emp, n, filename);
    displayExpenditure(calculateTotalPayroll(filename));
    
    return 0;
}

void inputEmployees(Employee e[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter the details of employee no %d\n", i + 1);
        
        printf("Enter the Employee ID: ");
        scanf("%d", &e[i].id);
        
        printf("Enter the Name: ");
        // Consume the newline left by previous scanf
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 
        
        // Edge Case 4 & 8: Read name with spaces, limit to NAME_LEN-1 chars
        if (fgets(e[i].name, NAME_LEN, stdin) != NULL) {
            // Remove trailing newline if present
            size_t len = strlen(e[i].name);
            if (len > 0 && e[i].name[len - 1] == '\n') {
                e[i].name[len - 1] = '\0';
            }
        }

        printf("Enter the Salary: ");
        // Edge Case 5 & 6: Use double (lf) for precision
        scanf("%lf", &e[i].salary);
    }
}

void writeToTextFile(Employee e[], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("There was some error in opening the file\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        // Use a delimiter (like comma or tab) if names have spaces
        // OR stick to fixed width. Here we use a comma for robust parsing.
        // Format: ID,Salary,Name (Name last to handle spaces easily)
        fprintf(file, "%d,%.15f,%s\n", e[i].id, e[i].salary, e[i].name);
    }
    fclose(file);
}

double calculateTotalPayroll(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        // Edge Case: File missing or read error treated as 0 cost
        return 0.0;
    }
    
    double total = 0.0, salary;
    int id;
    char name[NAME_LEN + 10]; // Extra buffer for safety
    
    // Robust Parsing: Read until newline to handle names with spaces
    // We parse the line manually or use specific format
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // Parse: ID (int), Salary (double), Name (string)
        // Matches the fprintf format: "%d,%.15f,%s\n"
        // strtok is safer here than fscanf for mixed types with spaces
        
        char *token = strtok(line, ",");
        if (!token) continue;
        id = atoi(token);
        
        token = strtok(NULL, ",");
        if (!token) continue;
        salary = atof(token);
        
        token = strtok(NULL, "\n"); // Read rest of line as name
        if (token) strcpy(name, token);
        
        total += salary;
    }
    
    fclose(fp);
    return total;
}

void displayExpenditure(double total) {
    printf("\n====================================\n");
    // Edge Case 5: Print with 2 decimal precision for currency
    printf("TOTAL MONTHLY PAYROLL: $%.2f\n", total);
    printf("====================================\n");
}
