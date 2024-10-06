#include <cs50.h>
#include <stdio.h>

#define MAX_STUDENTS 100
#define SUBJECTS 4

// Function to calculate the average and assign grades
void calculateAverageAndGrade(float marks[], float *average, char *grade) {
    float total = 0;

    for (int i = 0; i < SUBJECTS; i++) {
        total += marks[i];
    }

    *average = total / SUBJECTS;

    // Assign grade
    if (*average >= 90) *grade = 'A';
    else if (*average >= 75) *grade = 'B';
    else if (*average >= 60) *grade = 'C';
    else if (*average >= 50) *grade = 'D';
    else *grade = 'F';
}

int main() {
    int numStudents = get_int("Enter the number of students: ");
    float marks[MAX_STUDENTS][SUBJECTS];
    float averages[MAX_STUDENTS];
    char grades[MAX_STUDENTS];
    string names[MAX_STUDENTS]; // Using `string` from CS50 for student names

    for (int i = 0; i < numStudents; i++) {
        // Prompt for student name
        names[i] = get_string("Enter name for student %d: ", i + 1);

        // Input marks for each subject
        printf("Enter marks for %s:\n", names[i]);
        const char *subjectNames[] = {"Mathematics", "Physics", "Chemistry", "English"};
        for (int j = 0; j < SUBJECTS; j++) {
            marks[i][j] = get_float("%s: ", subjectNames[j]);
        }

        // Calculate average and grade
        calculateAverageAndGrade(marks[i], &averages[i], &grades[i]);
    }

    // Display results
    printf("\nStudent Results:\n");
    printf("--------------------------------------------------\n");
    printf("Student Name\t\tAverage Marks\tGrade\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%-20s\t%.2f\t\t%c\n", names[i], averages[i], grades[i]);
    }
    printf("--------------------------------------------------\n");

    return 0;
}
