#include<stdio.h>
typedef struct {
    int roLLn;
    float marks;
    char name[100];

}Student;

void inputStudents(Student students[], int n);
void writeToBinaryFile(Student students[], int n, const char *filename);
int readFromBinaryFile(Student students[], const char *filename);
void printStudents(Student students[], int n);
int main(){
    return 0;
}
void inputStudents(Student students[], int n){
    for(int i=0; i<n; i++){
        printf("enter the Name ofstudent %d :", i+1);
        scanf("%s", &students[i].name);
        
        printf("enter the ID of student ");
        scanf("%d", &students[i].roLLn);
        
        printf("enter the marks :");
        scanf("%d", &students[i].marks);
    }

}
void writeToBinaryFile(Student students[], int n, const char *filename){
    FILE *file = fopen(filename, "wb");
    if(file == NULL){
        perror("Error openiing the file for writing");
        return;
    }
    fwrite(students, sizeof(Student), n, file);
    fclose(file);
    printf("\n File succesfully written ");
}
int readFromBinaryFile(Student students[], const char *filename){
    FILE *file = fopen(filename, "rb");
    if(file ==NULL){
        perror("Error opening the file ");
        return 0;
    }
    fseek(file, 0,  SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    int n = (int)(fileSize/sizeof(Student));
}
void printStudents(Student students[], int n){

}
