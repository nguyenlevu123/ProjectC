#ifndef DATATYPE_H
#define DATATYPE_H

#define MAX_STUDENTS 100
#define MAX_TEACHERS 100
#define MAX_LENGTH 50

// dinh nghia kieu du lieu cho sinh vien
typedef struct {
    char id[MAX_LENGTH];
    char name[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phone[MAX_LENGTH];
} Student;

// dinh nghia kieu du lieu cho giao vien
typedef struct {
    char id[MAX_LENGTH];
    char name[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phone[MAX_LENGTH];
} Teacher;

#endif // DATATYPE_H

