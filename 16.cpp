#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 50
#define MAX_NAME_LENGTH 50							
#define FILENAME "employees.dat"

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
} Employee;

void addEmployee(FILE *file) {
    Employee emp;
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf("%s", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);
    
    fseek(file, (emp.id - 1) * sizeof(Employee), SEEK_SET);
    fwrite(&emp, sizeof(Employee), 1, file);
    printf("Employee added successfully!\n");
}

void displayEmployee(FILE *file, int id) {
    Employee emp;
    fseek(file, (id - 1) * sizeof(Employee), SEEK_SET);
    fread(&emp, sizeof(Employee), 1, file);
    printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
}

int main() {
    FILE *file = fopen(FILENAME, "r+");
    if (file == NULL) {
        file = fopen(FILENAME, "w+");
        if (file == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
    }

    int choice;
    do {
        printf("\n1. Add Employee\n2. Display Employee\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(file);
                break;
            case 2:
                printf("Enter employee ID to display: ");
                int id;
                scanf("%d", &id);
                displayEmployee(file, id);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    fclose(file);
    return 0;
}

