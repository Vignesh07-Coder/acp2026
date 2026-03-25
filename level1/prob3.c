#include<stdio.h>
typedef struct {
    	float length;
    	float width;
    	float area;
    	float costPerUnit;
    	float totalCost;
} Floor;
void inputDetails(int n, Floor floors[n]);
void calculateCosts(int n, Floor floors[n]);
int highestCostFloor(int n, Floor floors[n]);
void displayHighestCost(int index, Floor floors[]);	
int main(){
    int n;
    printf("Enter the number of floors :");
    while(1){
        if((scanf("%d", &n) ==1) && n>0){
            break;
        }
    }
    Floor floors[n];
    inputDetails(n, floors);
    calculateCosts(n, floors);
    displayHighestCost(highestCostFloor(n, floors), floors);

    return 0;
}

void inputDetails(int n, Floor floors[n]){
    for(int i=0; i<n;i++){
        printf("Enter the length of floor %d", i+1);
        scanf("%f", &floors[i].length);
        printf("Enter the width of floor");
        scanf("%f", &floors[i].width);
        printf("Enter the per unit cost of the floor %d", i+1);
        scanf("%f", &floors[i].costPerUnit);
        
    }
}
void calculateCosts(int n, Floor floors[n]){
    for(int i=0; i<n;i++){
        floors[i].area = floors[i].length * floors[i].width;
        floors[i].totalCost = floors[i].area * floors[i].costPerUnit;
    }
}
int highestCostFloor(int n, Floor floors[n]){
    int max=0;
    for(int i=0; i<n;i++){
        if(floors[i].area > floors[max].area){
            max = i;
        }

    }
    return max;
}
void displayHighestCost(int index, Floor floors[]){
    printf("\n--- Floor with the Highest Tiling Cost ---\n");
    printf("Floor Index: %d\n", index + 1);
    printf("Area: %.2f\n", floors[index].area);
    printf("Total Cost: %.2f\n", floors[index].totalCost);
}
