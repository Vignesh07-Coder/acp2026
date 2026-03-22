#include<stdio.h>
#include<math.h>
#define maxCars 10 
typedef struct{
    int car_id;
    char model_name[100];
    int manufacture_year;
    float price;

}Car_t;
void readCars(int n, Car_t c[]);
void displayModernCars(int n, Car_t c[]);
int main(){
    int n;
    printf("Enter the number of cars :");
    scanf("%d", &n);
    if(n<=0 ||scanf("%d", &n) !=1){
    while (1)
        {
         printf("\nEnter a vaild positive number : ");
         if(scanf("%d", &n) ==1 && n>0){
            break;
         }   /* code */
        }
    }
    if(n>maxCars) n = maxCars;
    Car_t cars[maxCars];
    readCars(n, cars);
    displayModernCars(n, cars);
    return 0;
}
void readCars(int n, Car_t c[]){
    for (int i = 0; i < n; i++){
        printf("\nEnter the Model name of the car %d", i+1);
        scanf("%99s", c[i].model_name);
        printf("Enter the ID of the car : ");
        scanf("%d", &c[i].car_id);
        printf("Enter the manufactured  year of the car : ");
        scanf("%d", &c[i].manufacture_year);
        printf("Enter the price of the car : ");
        while(scanf("%f", &c[i].price) != 1 || c[i].price<0){
            printf("Tryy again broo!");
            while (getchar() != '\n');
        }
    }
    
}
void displayModernCars(int n, Car_t c[]){
    int found =0;
    for (int i = 0; i < n; i++){
        if(c[i].manufacture_year>2022){
            printf("%s\n", c[i].model_name);
            found = 1;
        }

    }
    if(!found){
        printf("There exists no car manufactured after 2022!");
    }
}