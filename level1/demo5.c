#include <stdio.h>

void read_array(int n, int arr[]);
void print_array(int n, int arr[]);
void swap_array(int n, int a[n], int b[n]);

int main() {
    int n;
    printf("Enter the no of elements: ");
    
    // Corrected validation: removed the double scanf calls
    while (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Enter a positive integer: ");
        while(getchar() != '\n'); // Clear the input buffer
    }

    int arr1[n], arr2[n];

    printf("\nEnter %d elements for Array 1:\n", n);
    read_array(n, arr1);

    printf("\nEnter %d elements for Array 2:\n", n);
    read_array(n, arr2);

    printf("\nArray 1 before swap: ");
    print_array(n, arr1);
    printf("\nArray 2 before swap: ");
    print_array(n, arr2);

    swap_array(n, arr1, arr2);

    printf("\n\nArray 1 after swap: ");
    print_array(n, arr1);
    printf("\nArray 2 after swap: ");
    print_array(n, arr2);
    printf("\n");

    return 0;
}

void read_array(int n, int arr[]) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

void print_array(int n, int arr[]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void swap_array(int n, int a[n], int b[n]) {
    for (int i = 0; i < n; i++) {
        
        int temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
