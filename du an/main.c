#include <stdio.h>
#include "function.h"

int main() {
    loadStudents();
    loadTeachers();
    int choice;
    do {
        printf("\n===== SYSTEM MANAGEMENT =====\n");
        printf("[1]. Student management\n");
        printf("[2]. Teacher management\n");
        printf("[0]. exit\n");
        printf("enter selection: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: displayStudentMenu(); break;
            case 2: displayTeacherMenu(); break;
            case 0: 
                saveStudents(); 
                saveTeachers(); 
                printf("exit program.\n"); 
                break;
            default: 
                printf("Invalid selection.\n");
        }
    } while (choice != 0);
    return 0;
}

