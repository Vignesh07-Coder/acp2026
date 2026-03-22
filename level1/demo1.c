#include <stdio.h>

/* Function Prototypes */
void input(int n, float arr[n]);
int find_max_index(int n, float arr[n]);
void output(float arr[], int max_index);

int main() {

    printf("Enter the number of elements: \n");
    int n;
    
    scanf("%d", &n);
    
    if (n<=0) {
        printf("Invalid number of elements.");
        return 0;
    }
    float arr[n];
    printf("Enter the array elements:\n");
    input(n, arr);
    output(arr, find_max_index(n, arr));
    return 0;
}

void input(int n, float arr[n]) {
    for(int i=0; i<n;i++){
        scanf("%f",&arr[i]);
    }
    // Write code here to read n float values into the array
}

int find_max_index(int n, float arr[n]) {
    int maxI = 0;
    for(int i=0; i<n;i++){
        if(arr[i]>arr[maxI]){
            maxI = i;
        }
    }
    return maxI;
}

void output(float arr[], int maxI) {
    printf("Maximum element is %.2f\n", arr[maxI] );
    printf("Index of maximum element is %d\n",maxI );
}