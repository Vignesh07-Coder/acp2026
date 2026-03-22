#include<stdio.h>
#include<math.h>
typedef struct{
    int id;
    char name[100];
    float price;
}Product;
void inputProducts(Product p[], int n);
void saveToBinaryFile(Product p[], int n, const char *file);
float calculateTotalValue(const char *file);
void displayTotalValue(float total);
int main(){
    
}
