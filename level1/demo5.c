#include <stdio.h>
#include <stdlib.h>

int* create_array(int n);
void initialize_array(int *arr, int n);
void print_array(int *arr, int n);
void delete_array(int **arr);

int main() {
    printf("Enter number of elements: ");
    int n;
    scanf("%d", &n);

    if(n <= 0){
        printf("Invalid array size!");
        return 0;
    }
    int arr;
    arr = create_array(n);

    if(arr == NULL){
        printf("Memory allocation failed!");
        return 0;
    }

    printf("Enter %d integers:\n", n);
    initialize_array(arr, n);

    printf("Array elements are:\n");
    print_array(arr, n);

    delete_array(&arr);

    if(arr == NULL)
        printf("\nMemory successfully freed and pointer set to NULL.");

    return 0;
}

int* create_array(int n) {
    // Allocate memory dynamically for n integers
    int *arr= (int *)malloc(n * sizeof(int));
    if(arr == NULL){
        return NULL;
    }
    for(int i=0; i<n; i++){
        arr[i] = 0;
    }
    return arr;
    // Return the pointer to the allocated memory
    
}

void initialize_array(int *arr, int n) {
    // Write code here to read n integers into the array
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
}

void print_array(int *arr, int n) {
    // Write code here to print array elements separated by space
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
}

void delete_array(int **arr) {
    // Write code here to free the memory
    if(arr != NULL && *arr != NULL){
        free(*arr);
        *arr = NULL;
    }
    // Set the pointer to NULL to avoid dangling pointer
}