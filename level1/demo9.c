#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int id;
    float marks;
} Student;

void inputStudents(Student students[], int n);
void writeToTextFile(Student students[], int n, const char *filename);
int readFromTextFile(Student students[], const char *filename);
void printStudents(Student students[], int n);

int main() {
    int n;
    const char *filename = "students.txt";

    printf("Enter the no of students: ");
    scanf("%d", &n);
    if(n<=0 || n >100){
        printf("Enter a valid numeber brooo!");
        return 1;
    }

    Student students1[100];   // fixed typo
    Student students2[100];   // fixed typo

    inputStudents(students1, n);
    writeToTextFile(students1, n, filename);

    printf("\nData from the readback operation of file :\n");
    printStudents(students2, readFromTextFile(students2, filename));

    return 0;
}

void inputStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter the id of the student: ");
        scanf("%d", &students[i].id);
        printf("Enter the name of the student: ");
        scanf("%99s", students[i].name);   // no &; bounds‑safe
        printf("Enter the marks of the student: ");
        scanf("%f", &students[i].marks);
    }
}

void writeToTextFile(Student students[], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error in opening the file!!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %s %.2f\n", students[i].id, students[i].name, students[i].marks);
    }
    fclose(file);
}

int readFromTextFile(Student students[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error in opening the file !!\n");
        return 0;
    }
    int i = 0;
    while (i < 100 && fscanf(file, "%d %99s %f", &students[i].id, students[i].name, &students[i].marks) == 3) {
        i++;
    }
    fclose(file);
    return i;
}

void printStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Student %d: ID=%d, Name=%s, Marks=%.2f\n",
               i + 1, students[i].id, students[i].name, students[i].marks);
    }
}

