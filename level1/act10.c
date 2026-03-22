#include<stdio.h>
#include<stdlib.h>
#define maxFlights 100
typedef struct{
    int flightNo;
    char destiantion[100];
    float ticketPrice;

}Flight;
void inputFlights(Flight f[], int n);
void saveToBinary(Flight f[], int n, const char *filename);
Flight findMostExpensive(const char *filename);
void displayTopFlight(Flight f);
int main(){
    int n;
    printf("Enter the number of flights ");
    scanf("%d", &n);
    if(n<=0){
    while (1)
        {
         printf("\nEnter a vaild positive number : ");
         if(scanf("%d", &n) ==1){
            break;
         }   /* code */
        }
    }
    if (n>maxFlights) n = maxFlights;
    Flight *flights = (Flight *)malloc(n * sizeof(Flight));
    inputFlights(flights,n);
    const char *filename = "flights.bin";
    saveToBinary(flights, n, filename);
    displayTopFlight(findMostExpensive(filename));
    free(flights);
    return 0;
}
void inputFlights(Flight f[], int n){
    for(int i=0;i<n;i++){
        printf("\nEnter the Flight number of flight  %d", i+1);
        scanf("%d", &f[i].flightNo);
        printf("\nEnter the Destination : ");
        scanf("%s", &f[i].destiantion);
        printf("\nEnter the ticket price : ");
        scanf("%f", &f[i].ticketPrice);
    }
}
void saveToBinary(Flight f[], int n, const char *filename){
    FILE *file = fopen(filename, "wb");
    if(file==NULL){
        perror("\nMemory allocation failed !!");
        return;
    }
    fwrite(f, sizeof(Flight), n, file);
    fclose(file);
    printf("\nData sucessfully written to the binary file!");

}
Flight findMostExpensive(const char *filename){
    FILE *fp = fopen(filename, "rb");
    Flight current, expensive = {0, "", -1.0};
    if(!fp){

        perror("File opening failed!!");
        return expensive;
    }
    while(fread(&current, sizeof(Flight), 1, fp)){
        if(current.ticketPrice > expensive.ticketPrice){
            expensive = current;
        }
    }
    fclose(fp);
    return expensive;
}
void displayTopFlight(Flight f){
    if(f.ticketPrice == -1.0){
        printf("\n No flight record found");
    }
    else{
        printf("\n------MOST EXPENSIVE FLIGHT------");
        printf("\nNumber : %d\n", f.flightNo);
        printf("Destination: %s \n", f.destiantion);
        printf("Price : %.2f\n", f.ticketPrice);
    }
}