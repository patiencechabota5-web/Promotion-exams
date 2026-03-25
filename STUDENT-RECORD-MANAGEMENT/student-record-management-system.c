#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure
struct Student {
    char name[50];
    int studentNo;
    int math, english, computer;
    float average;
    char grade;
};

struct Student students[MAX];
int count = 0;

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void calculateResults();
void saveToFile();

int main() {
    int choice;

    while (1) {
        printf("\n==============================\n");
        printf(" STUDENT MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Calculate Results\n");
        printf("5. Save Results to File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: calculateResults(); break;
            case 5: saveToFile(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

// 1. Add Student
void addStudent() {
    printf("\nEnter Student Name: ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter Student Number: ");
    scanf("%d", &students[count].studentNo);

    printf("Math Marks: ");
    scanf("%d", &students[count].math);

    printf("English Marks: ");
    scanf("%d", &students[count].english);

    printf("Computer Marks: ");
    scanf("%d", &students[count].computer);

    count++;
    printf("Student added successfully!\n");
}

// 2. View Students
void viewStudents() {
    printf("\n-------------------------------------------------------\n");
    printf("Name\t\tNo\tMath\tEng\tComp\n");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%s\t%d\t%d\t%d\t%d\n",
               students[i].name,
               students[i].studentNo,
               students[i].math,
               students[i].english,
               students[i].computer);
    }
}

// 3. Search Student
void searchStudent() {
    int number, found = 0;

    printf("Enter Student Number to search: ");
    scanf("%d", &number);

    for (int i = 0; i < count; i++) {
        if (students[i].studentNo == number) {
            printf("\nStudent Found!\n");
            printf("Name: %s\n", students[i].name);
            printf("Math: %d\n", students[i].math);
            printf("English: %d\n", students[i].english);
            printf("Computer: %d\n", students[i].computer);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }
}

// 4. Calculate Results
void calculateResults() {
    for (int i = 0; i < count; i++) {
        int total = students[i].math + students[i].english + students[i].computer;
        students[i].average = total / 3.0;

        if (students[i].average >= 80)
            students[i].grade = 'A';
        else if (students[i].average >= 70)
            students[i].grade = 'B';
        else if (students[i].average >= 60)
            students[i].grade = 'C';
        else if (students[i].average >= 50)
            students[i].grade = 'D';
        else
            students[i].grade = 'F';

        printf("\n%s -> Avg: %.2f Grade: %c\n",
               students[i].name,
               students[i].average,
               students[i].grade);
    }
}

// 5. Save to File
void saveToFile() {
    FILE *file = fopen("students.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %d %d %d %.2f %c\n",
                students[i].name,
                students[i].studentNo,
                students[i].math,
                students[i].english,
                students[i].computer,
                students[i].average,
                students[i].grade);
    }

    fclose(file);
    printf("Data saved to students.txt successfully!\n");
}
