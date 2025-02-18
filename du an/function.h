#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

//Cac ham quan li sinh vien
void loadStudents();
void saveStudents();
void displayStudentMenu();
void displayStudents();
void addStudent();
void editStudent();
void deleteStudent();
void searchStudent();
void sortStudents();
int isValidStudent(Student s);
int findStudentIndexById(char *id);
void menu();

//Cac ham quan li giao vien
void loadTeachers();
void saveTeachers();
void displayTeacherMenu();
void displayTeachers();
void addTeacher();
void editTeacher();
void deleteTeacher();
int findTeacherIndexById(char *id);

//Ham tro lai menu: chon quay lai or thoat chuong trinh
void backAndExit();

#endif // FUNCTION_H

