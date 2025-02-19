#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// dinh nghia cac bien cho quan li sinh vien va giao vien
Student students[MAX_STUDENTS];
Teacher teachers[MAX_TEACHERS];
int studentCount = 0;
int teacherCount = 0;
const char *studentFile = "students.bin";
const char *teacherFile = "teachers.bin";

/*======================= Ham tro ve menu =======================*/
void backAndExit(){
    int backExit;
    do{
        printf("\nGo Back(0) or Exit The Program(10)?: ");
        scanf("%d", &backExit);
        system("cls");
        if(backExit != 0 && backExit != 10){
            printf("\n*Error, Please Try Again*\n");
        }
    } while(backExit != 0 && backExit != 10);
    if(backExit == 10){
        printf("\n======Thank You======\n");
        printf("==== See You Soon ====\n");
        exit(0);
    }
}
/*======================= Ham ktr trung lap sinh vien =======================*/
int isStudentDuplicate(char *id, char *email, char *phone) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0 || strcmp(students[i].email, email) == 0 || strcmp(students[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;	
}


/*======================= QUAN LI SINH VIEN =======================*/
// Ham loadStudents dung de doc danh sach sinh vien tu file nhi phan 'students.bin' vao mang students.
void loadStudents() {
    FILE *file = fopen("students.bin", "rb");
    if (!file) {
        perror("Error opening file 'students.bin' for reading"); // Neu khong mo duoc file, bao loi.
        return;
    }
    size_t readCount = fread(students, sizeof(Student), MAX_STUDENTS, file); // Doc du lieu vao mang students.
    if (ferror(file)) {
        printf("Error reading file 'students.bin'.\n"); // Neu co loi khi doc.
        clearerr(file); // Xoa loi file.
    } else {
        studentCount = readCount; // Cap nhat so luong sinh vien da doc.
        printf("Successfully read %d students from the binary file.\n", studentCount); // Hien thi thong bao thanh cong.
    }
    fclose(file); // Dong file sau khi xong.
}

// Ham saveStudents dung de ghi danh sach sinh vien vao file nhi phan 'students.bin'.
void saveStudents() {
    FILE *file = fopen("students.bin", "wb");
    if (!file) {
        perror("Error opening file 'students.bin' for writing"); // Neu khong mo duoc file, bao loi.
        return;
    }
    size_t writtenCount = fwrite(students, sizeof(Student), studentCount, file); // Ghi du lieu vao file.
    if (writtenCount != studentCount) {
        printf("Error writing to file 'students.bin'.\n"); // Neu co loi khi ghi.
    } else {
        printf("Successfully saved %d students to the binary file.\n", studentCount); // Hien thi thong bao thanh cong.
    }
    fclose(file); // Dong file sau khi xong.
}

// Ham displayStudents dung de hien thi danh sach sinh vien hien tai.
void displayStudents() {
	system("cls");
    printf("************************** STUDENT LIST ***********************************\n");
    printf("+-----------+---------------------+--------------------------+------------+\n");
    printf("|%-10s |%-20s |%-25s |%-15s\n", "ID", "Name", "Email", "Phone"); // In tieu de cot.
    printf("+-----------+---------------------+--------------------------+------------+\n");
    for (int i = 0; i < studentCount; i++) {
        // In thong tin cua tung sinh vien.
        printf("|%-10s |%-20s |%-25s |%-15s\n", 
               students[i].id, 
               students[i].name, 
               students[i].email, 
               students[i].phone);
            printf("+-----------+---------------------+--------------------------+------------+\n");   
    }
}

// Ham addStudent dung de them sinh vien moi vao danh sach.
void addStudent() {
	system("cls");
    if (studentCount >= MAX_STUDENTS) {
        printf("The list is full.\n"); // Neu danh sach da day, thong bao.
        return;
    }
    Student s;

    // Nhap thong tin sinh vien.
    printf("Enter ID: ");
    scanf(" %[^\n]", s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Email: ");
    scanf(" %[^\n]", s.email);
    printf("Enter Phone: ");
    scanf(" %[^\n]", s.phone);

    // Kiem tra du lieu nhap vao (co the in ra de debug).
    printf("Entered: ID = %s, Name = %s, Email = %s, Phone = %s\n", s.id, s.name, s.email, s.phone);
 if (isStudentDuplicate(s.id, s.email, s.phone)) {
        printf("\nError: ID, email or phone number already exists!\n");
        return;
    }
    // Them sinh vien vao danh sach.
    students[studentCount++] = s;
    printf("Student added successfully. Current studentCount = %d\n", studentCount);
    saveStudents(); // Luu du lieu sau khi them.
}

// Ham editStudent dung de chinh sua thong tin cua sinh vien.
void editStudent() {
	system("cls");
    char id[MAX_LENGTH];
    printf("Enter student ID to edit: ");
    scanf("%s", id);  getchar(); // Xoa ky tu '\n' thua trong bo nho dem
     // Tim sinnh vien trong danh sach theo ID
    int index = findStudentIndexById(id); // Tim sinh vien theo ID.
    if (index == -1) {
        printf("Student not found.\n"); // Neu khong tim thay sinh vien.
        return;
    }
    int choice;
    do {
        // Hien thi menu chinh sua thong tin giao vien
        printf("\n===== EDIT STUDENT INFORMATION =====\n");
        printf("[1]. Edit Name\n");
        printf("[2]. Edit Email\n");
        printf("[3]. Edit Phone\n");
        printf("[0]. Save and exit\n");
        printf("Enter your choice ");
         // Nhan lua chon tu nguoi dung
        scanf("%d", &choice);
        getchar(); // Xoa ky tu '\n' thua trong bo nho dem
        switch (choice) {
    // Nhap lai thong tin can sua.
     case 1:
                printf("Enter new name ");
    scanf(" %[^\n]", students[index].name);
    break;
	 case 2:
    printf("Enter new email: ");
    scanf(" %[^\n]", students[index].email);
    break;
    case 3:
    printf("Enter new phone: ");
    scanf(" %[^\n]", students[index].phone);
	break;
    case 0:
                // Khi chon 0, luu thay doi va thoat
                saveStudents();
                printf("Updated successfully\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);
}


// Ham deleteStudent dung de xoa mot sinh vien khoi danh sach.
void deleteStudent() {
    char id[MAX_LENGTH];
    printf("Enter student ID to delete: ");
    scanf("%s", id);
    int index = findStudentIndexById(id); // Tim sinh vien theo ID.
    if (index == -1) {
        printf("Student not found.\n"); // Neu khong tim thay sinh vien.
        return;
    }
    // Di chuyen cac sinh vien phia sau len vi tri hien tai de xoa.
    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--; // Giam so luong sinh vien.
    printf("Deleted successfully.\n");
    saveStudents(); // Luu lai sau khi xoa.
}

// Ham findStudentIndexById dung de tim vi tri cua sinh vien theo ID.
int findStudentIndexById(char *id) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0) // So sanh ID de tim sinh vien.
            return i;
    }
    return -1; // Khong tim thay sinh vien.
}

// Ham searchStudent dung de tim kiem sinh vien theo ten.
void searchStudent() {
	system("cls");
    char keyword[MAX_LENGTH];
    printf("Enter student name to search: ");
    scanf("%s", keyword);
    int found = 0;
    printf("\nSearch Results:\n");
    printf("%-10s %-20s %-25s %-15s\n", "ID", "Name", "Email", "Phone"); // In tieu de cot.
    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, keyword) != NULL) { // Kiem tra ten sinh vien co chua tu khoa hay khong.
            printf("%-10s %-20s %-25s %-15s\n", 
                   students[i].id, 
                   students[i].name, 
                   students[i].email, 
                   students[i].phone);
            found = 1; // Da tim thay sinh vien.
        }
    }
    if (!found) {
        printf("No student found.\n"); // Neu khong tim thay sinh vien.
    }
}

// Ham sortStudents dung de sap xep danh sach sinh vien theo ten.
void sortStudents() {
    system("cls");
    int order;
    printf("Choose sorting order: 1. Ascending, 2. Descending: ");
    scanf("%d", &order);

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) { // Sua loi o day
            int cmp = strcmp(students[i].name, students[j].name); // So sanh ten sinh vien
            if ((order == 1 && cmp > 0) || (order == 2 && cmp < 0)) {
                // Hoan doi neu can thiet
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Sorting completed.\n");
    saveStudents(); // Luu y danh sach da sap xep
}


// Ham isValidStudent dung de kiem tra tinh hop le cua mot sinh vien.
int isValidStudent(Student s) {
	system("cls");
    // Kiem tra neu bat ky truong nao cua sinh vien la rong hoac co du lieu trung lap.
    if (strlen(s.id) == 0 || strlen(s.name) == 0 || strlen(s.email) == 0 || strlen(s.phone) == 0)
        return 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, s.id) == 0 ||
            strcmp(students[i].email, s.email) == 0 ||
            strcmp(students[i].phone, s.phone) == 0)
            return 0; // Neu trung ID, email hoac so dien thoai, tra ve false.
    }
    return 1; // Neu hop le, tra ve true.
}

// Ham displayStudentMenu dung de hien thi menu quan ly sinh vien.
void displayStudentMenu() {
    int choice;
    do {
        printf("\n===== STUDENT MANAGEMENT =====\n");
        printf("[1]. Display student list\n");
        printf("[2]. Add student\n");
        printf("[3]. Edit student information\n");
        printf("[4]. Delete student\n");
        printf("[5]. Search student\n");
        printf("[6]. Sort student list\n");
        printf("[0]. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Doc ki tu thua.
        switch (choice) {
            case 1: displayStudents(); break;
            case 2: addStudent(); break;
            case 3: editStudent(); break;
            case 4: deleteStudent(); break;
            case 5: searchStudent(); break;
            case 6: sortStudents(); break;
            case 0: break;
            default: printf("Invalid choice.\n");
        }
        backAndExit();  // Goi ham de hoi nguoi dung quay lai hoac thoat.
    } while (choice != 0);
}


/*======================= Ham ktr trung lap giao vien =======================*/
int isTeacherDuplicate(char *id, char *email, char *phone) {
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].id, id) == 0 || strcmp(teachers[i].email, email) == 0 || strcmp(teachers[i].phone, phone) == 0) {
            return 1;
        }
    }
    return 0;
}    

/*======================= QUAN LI GIAO VIEN =======================*/

void loadTeachers() {
    // Mo file teachers.bin o che do doc nhi phan
    FILE *file = fopen("teachers.bin", "rb");
    if (!file) {
        printf("Error opening teachers.bin file for reading\n");
        return;
    }

    // Doc du lieu tu file vao mang teachers
    size_t readCount = fread(teachers, sizeof(Teacher), MAX_TEACHERS, file);
    
    // Kiem tra loi trong qua trinh doc file
    if (ferror(file)) {
        printf("Error reading teachers.bin file\n");
        clearerr(file);
    } else {
        teacherCount = readCount; // Cap nhat so luong giao vien da doc
        printf("Successfully read %d teachers from the binary file\n", teacherCount);
    }

    // Dong file
    fclose(file);
}

void saveTeachers() {
    // Mo file teachers.bin o che do ghi nhi phan
    FILE *file = fopen("teachers.bin", "wb");
    if (!file) {
        printf("Error opening teachers.bin file for writing\n");
        return;
    }

    // Ghi du lieu tu mang teachers vao file
    size_t writtenCount = fwrite(teachers, sizeof(Teacher), teacherCount, file);
    
    // Kiem tra loi trong qua trinh ghi file
    if (writtenCount != teacherCount) {
        printf("Error writing to teachers.bin file\n");
    } else {
        printf("Successfully saved %d teachers to the binary file\n", teacherCount);
    }

    // Dong file
    fclose(file);
}

void displayTeacherMenu() {
	
    int choice;
    do {
        // Hien thi menu quan ly giao vien
        printf("\n===== TEACHER MANAGEMENT =====\n");
        printf("[1]. Display teacher list\n");
        printf("[2]. Add teacher\n");
        printf("[3]. Edit teacher information\n");
        printf("[4]. Delete teacher\n");
        printf("[0]. Go back\n");
        printf("Enter your choice ");
        
        // Nhap lua chon tu nguoi dung
        scanf("%d", &choice);
        getchar(); // Xoa ky tu '\n' thua trong bo nho dem

        // Xu ly lua chon cua nguoi dung
        switch (choice) {
            case 1: displayTeachers(); break;
            case 2: addTeacher(); break;
            case 3: editTeacher(); break;
            case 4: deleteTeacher(); break;
            case 0: break;
            default: printf("Invalid choice\n");
        }

        // Sau moi thao tac, cho phep nguoi dung quay lai menu hoac thoat
        backAndExit();
    } while (choice != 0);
}

void displayTeachers() {
	system("cls");
    // Hien thi tieu de danh sach giao vien
    printf("\n**************************** Teacher Lists ********************************\n");
    printf("+-----------+---------------------+--------------------------+------------+\n");
    printf("|%-10s |%-20s |%-25s |%-15s\n", "ID", "Name", "Email", "Phone");
  printf("+-----------+---------------------+--------------------------+------------+\n");
    // Duyet qua danh sach giao vien va hien thi thong tin
    for (int i = 0; i < teacherCount; i++) {
        printf("|%-10s |%-20s |%-25s |%-15s\n", 
               teachers[i].id, 
               teachers[i].name, 
               teachers[i].email, 
               teachers[i].phone);
    }
      printf("+-----------+---------------------+--------------------------+------------+\n");
}

void addTeacher() {
	system("cls");
    // Kiem tra neu danh sach da day
    if (teacherCount >= MAX_TEACHERS) {
        printf("Teacher list is full\n");
        return;
    }

    // Nhap thong tin giao vien moi
    Teacher t;
    printf("Enter ID: ");
    scanf(" %[^\n]", t.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", t.name);
    printf("Enter Email: ");
    scanf(" %[^\n]", t.email);
    printf("Enter Phone: ");
    scanf(" %[^\n]", t.phone);
    // Kiem tra trung lap thong tin
 if (isTeacherDuplicate(t.id, t.email, t.phone)) {
        printf("Error: ID, email or phone number already exists!\n");
        return;
    }
    // Luu vao mang teachers va tang so luong giao vien
   teachers[teacherCount++] = t;
    printf("Teacher added successfully\n");

    // Luu du lieu vao file
    saveTeachers();
}

void editTeacher() {
	system("cls");
    char id[MAX_LENGTH];
    printf("Enter the ID of the teacher to edit ");
    scanf("%s", id);
    getchar(); // Xoa ky tu '\n' thua trong bo nho dem

    // Tim giao vien trong danh sach theo ID
    int index = findTeacherIndexById(id);
    if (index == -1) {
        printf("Teacher not found\n");
        return;
    }

    int choice;
    do {
        // Hien thi menu chinh sua thong tin giao vien
        printf("\n===== EDIT TEACHER INFORMATION =====\n");
        printf("[1]. Edit Name\n");
        printf("[2]. Edit Email\n");
        printf("[3]. Edit Phone\n");
        printf("[0]. Save and exit\n");
        printf("Enter your choice ");
        
        // Nhan lua chon tu nguoi dung
        scanf("%d", &choice);
        getchar(); // Xoa ky tu '\n' thua trong bo nho dem

        // Xu ly lua chon chinh sua
        switch (choice) {
            case 1:
                printf("Enter new name ");
                scanf(" %[^\n]", teachers[index].name);
                break;
            case 2:
                printf("Enter new email ");
                scanf(" %[^\n]", teachers[index].email);
                break;
            case 3:
                printf("Enter new phone ");
                scanf(" %[^\n]", teachers[index].phone);
                break;
            case 0:
                // Khi chon 0, luu thay doi va thoat
                saveTeachers();
                printf("Updated successfully\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);
}

void deleteTeacher() {
    char id[MAX_LENGTH];
    printf("Enter the ID of the teacher to delete ");
    scanf("%s", id);

    // Tim giao vien can xoa theo ID
    int index = findTeacherIndexById(id);
    if (index == -1) {
        printf("Teacher not found\n");
        return;
    }

    // Dich chuyen cac phan tu sau vi tri index len truoc de xoa giao vien
    for (int i = index; i < teacherCount - 1; i++) {
        teachers[i] = teachers[i + 1];
    }

    // Giam so luong giao vien
    teacherCount--;
    printf("Deleted successfully\n");

    // Luu danh sach moi vao file
    saveTeachers();
}

int findTeacherIndexById(char *id) {
    // Duyet danh sach de tim ID giao vien
    for (int i = 0; i < teacherCount; i++) {
        if (strcmp(teachers[i].id, id) == 0)
            return i; // Tra ve vi tri cua giao vien trong danh sach
    }
    return -1; // Khong tim thay giao vien
}

