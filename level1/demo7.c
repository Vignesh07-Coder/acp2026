#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

// Structure to hold student details
typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

// Function prototypes
void inputStudents(Student students[], int n);
void writeToTextFile(Student students[], int n, const char *filename);
int readFromTextFile(Student students[], const char *filename);
void printStudents(Student students[], int n);

int main() {
    Student students1[MAX_STUDENTS];
    Student students2[MAX_STUDENTS];
    int n1, n2;
    const char *filename = "students.txt";
    
    printf("Enter number of students: ");
    scanf("%d", &n1);
    
    // Task i: Read student details into first array
    inputStudents(students1, n1);
    
    // Task ii: Write first array to text file
    writeToTextFile(students1, n1, filename);
    printf("\nData written to %s successfully.\n", filename);
    
    // Task iii: Read data back into second array
    n2 = readFromTextFile(students2, filename);
    
    // Task iv: Display both arrays
    printf("\nOriginal array:\n");
    printStudents(students1, n1);
    
    printf("\nData read from file (array 2):\n");
    printStudents(students2, n2);
    
    return 0;
}

// Function to input student details
void inputStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &students[i].id);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);  // Read string with spaces
        printf("Marks: ");
        scanf("%f", &students[i].marks);
    }
}

// Function to write array to text file using fprintf()
void writeToTextFile(Student students[], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing!\n", filename);
        return;
    }
    
    // Write number of students first
    fprintf(file, "%d\n", n);
    
    // Write each student record
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %s %.2f\n", 
                students[i].id, students[i].name, students[i].marks);
    }
    
    fclose(file);
}

// Function to read from text file using fscanf()
int readFromTextFile(Student students[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s for reading!\n", filename);
        return 0;
    }
    
    int n;
    // Read number of students
    if (fscanf(file, "%d", &n) != 1) {
        printf("Error reading number of students from file!\n");
        fclose(file);
        return 0;
    }
    
    // Read each student record
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d %[^\n] %f", 
                   &students[i].id, students[i].name, &students[i].marks) != 3) {
            printf("Error reading student %d from file!\n", i + 1);
            fclose(file);
            return i;  // Return number of successfully read students
        }
    }
    
    fclose(file);
    return n;
}

// Function to display student details
void printStudents(Student students[], int n) {
    printf("+----+--------------------+-------+\n");
    printf("| ID | Name              | Marks |\n");
    printf("+----+--------------------+-------+\n");
    
    for (int i = 0; i < n; i++) {
        printf("|%4d|%-18s |%6.2f |\n", 
               students[i].id, students[i].name, students[i].marks);
    }
    printf("+----+--------------------+-------+\n");
}
