#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for medicine data
typedef struct {
    int id;
    char name[50];
    int exp_year;
} Medicine_t;

// Function prototypes
Medicine_t* allocate_inventory(int n);
void read_inventory(Medicine_t *m, int n);
void display_inventory(Medicine_t *m, int n);
void delete_inventory(Medicine_t **m);

int main() {
    int n;
    Medicine_t *inventory = NULL;

    printf("Enter the number of medicines: ");
    scanf("%d", &n);

    // 1. Allocate Memory
    inventory = allocate_inventory(n);

    // 2. Input Data
    read_inventory(inventory, n);

    // 3. Display Data
    display_inventory(inventory, n);

    // 4. Deallocate Memory
    delete_inventory(&inventory);

    return 0;
}

// Dynamically allocate an array of Medicine_t structures
Medicine_t* allocate_inventory(int n) {
    Medicine_t *m = (Medicine_t*)malloc(n * sizeof(Medicine_t));
    if (m == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return m;
}

// Input data for each medicine
void read_inventory(Medicine_t *m, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Medicine %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &m[i].id);
        printf("Name: ");
        scanf("%s", m[i].name);
        printf("Expiration Year: ");
        scanf("%d", &m[i].exp_year);
    }
}

// Display the complete inventory list
void display_inventory(Medicine_t *m, int n) {
    printf("\n--- Pharmacy Inventory ---\n");
    printf("%-10s %-20s %-15s\n", "ID", "Name", "Exp. Year");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-15d\n", m[i].id, m[i].name, m[i].exp_year);
    }
}

// Safely free memory and set pointer to NULL
void delete_inventory(Medicine_t **m) {
    if (m != NULL && *m != NULL) {
        free(*m);
        *m = NULL;
        printf("\nInventory memory deallocated successfully.\n");
    }
}
