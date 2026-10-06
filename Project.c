#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

// 1. Define a student record
typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

// Utility function to swap two student records
void swapStudents(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// Utility function to display the list of students
void displayStudents(Student arr[], int n) {
    printf("%-10s %-20s %s\n", "Roll No", "Name", "Marks");
    printf("------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %.2f\n", arr[i].roll, arr[i].name, arr[i].marks);
    }
    printf("\n");
}

// 4. Selection Sort (Sorts by Marks Descending)
void selectionSort(Student arr[], int n, int* comps, int* swaps) {
    *comps = 0;
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            (*comps)++;
            if (arr[j].marks > arr[max_idx].marks) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swapStudents(&arr[i], &arr[max_idx]);
            (*swaps)++;
        }
    }
}

// 4. Insertion Sort (Sorts by Marks Descending)
void insertionSort(Student arr[], int n, int* comps, int* shifts) {
    *comps = 0;
    *shifts = 0;
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            (*comps)++; // Counting comparison
            if (arr[j].marks < key.marks) {
                arr[j + 1] = arr[j];
                (*shifts)++; // Counting shift
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        if (j + 1 != i) (*shifts)++; // Count the final placement as a shift
    }
}

// Utility to sort by Roll Number (Ascending) for Binary Search
void sortByRollNumber(Student arr[], int n) {
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].roll > key.roll) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 5. Binary Search by Roll Number
void binarySearch(Student arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    int found = 0;
    int steps = 0;

    while (left <= right) {
        steps++;
        int mid = left + (right - left) / 2;

        if (arr[mid].roll == target) {
            printf("\nStudent Found! (in %d steps)\n", steps);
            printf("Roll: %d | Name: %s | Marks: %.2f\n",
arr[mid].roll, arr[mid].name, arr[mid].marks);
            found = 1;
            break;
        }
        if (arr[mid].roll < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        printf("\nRecord 'Not Found' for Roll Number %d.\n", target);
    }
}

// 2. Build Menu Options
int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n=== Smart Student Ranking & Search System ===\n");
        printf("1. Add Students\n");
        printf("2. Display All Students\n");
        printf("3. Generate Rank List & Compare Algorithms\n");
        printf("4. Search Student by Roll No\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int n;
            printf("How many students to add? ");
            scanf("%d", &n);

            if (count + n > MAX_STUDENTS) {
                printf("Cannot add %d students. Maximum limit is
%d.\n", n, MAX_STUDENTS);
                continue;
            }

            for (int i = 0; i < n; i++) {
                printf("\nStudent %d details:\n", count + 1);
                printf("Roll No: ");
                scanf("%d", &students[count].roll);

                // Clear the newline character left by scanf
                while(getchar() != '\n');

                printf("Name: ");
                fgets(students[count].name,
sizeof(students[count].name), stdin);
                // Remove trailing newline from fgets
                students[count].name[strcspn(students[count].name, "\n")] = 0;

                printf("Marks: ");
                scanf("%f", &students[count].marks);

                count++;
            }
        }
        else if (choice == 2) {
            if (count == 0) { printf("No records found!\n"); continue; }
            printf("\n--- Current Student Records ---\n");
            displayStudents(students, count);
        }
        else if (choice == 3) {
            if (count == 0) { printf("No records found!\n"); continue; }

            // 3. Make separate copies of the same data
            Student selData[MAX_STUDENTS];
            Student insData[MAX_STUDENTS];
            memcpy(selData, students, count * sizeof(Student));
            memcpy(insData, students, count * sizeof(Student));

            int selComps = 0, selSwaps = 0;
            int insComps = 0, insShifts = 0;

            // Run algorithms
            selectionSort(selData, count, &selComps, &selSwaps);
            insertionSort(insData, count, &insComps, &insShifts);

            printf("\n--- Rank List (Descending by Marks) ---\n");
            displayStudents(selData, count);

            printf("--- Topper Details ---\n");
            printf("Name: %s | Marks: %.2f\n\n", selData[0].name,
selData[0].marks);

            // 6. Display operation counts
            printf("--- Algorithm Performance Analysis ---\n");
            printf("Selection Sort : %d comparisons, %d swaps.\n",
selComps, selSwaps);
            printf("Insertion Sort : %d comparisons, %d shifts.\n",
insComps, insShifts);
        }
        else if (choice == 4) {
            if (count == 0) { printf("No records found!\n"); continue; }

            int targetRoll;
            printf("Enter Roll Number to search: ");
            scanf("%d", &targetRoll);

            // Sort by roll number first to enable Binary Search
            sortByRollNumber(students, count);

            printf("\nRecords have been sorted by Roll Number for
Binary Search.\n");
            binarySearch(students, count, targetRoll);
        }
        else if (choice == 5) {
            printf("Exiting system. Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
