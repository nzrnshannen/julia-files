/*==============================================================================
Name: Shannen T. Nazareno
Date: 01/05/2024
Program: Making a simple student records program using ADT LIST Array v4 imp.

Functions to be added:
* filter 
    -> by sex /
    -> by course /
    -> by year /
    -> by AccStat /
==============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_STUD 2 //for testing purposes

typedef char * SEX;
typedef char * MONTH;
typedef char * COURSE;
typedef char * ACCSTAT;

typedef enum {M, F} Sex;
typedef enum{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
}Month;

typedef enum{
    BSIS = 1,
    BSCS,
    BSIT
}Course;

typedef enum {INACTIVE, ACTIVE} AccountStat;

typedef struct{
    Month m;
    int day;
    int year;
}DateOfBirth;

typedef struct{
    char email[30];
    char password[30];
    AccountStat accStat;
}Account;

typedef struct{
    int id;
    char FN[30], LN[30], MI;
    int year;
    int age;
    Sex sx;
    DateOfBirth dob;
    Course studCourse;
    Account acc;
}studType, *Student;

typedef struct{
    Student Stud;
    int studCount;
}deptType, *Department;

void populate(Department *Dpt);
void initList(Department *Dpt);

void addStudent(Department *Dpt, Student stud);
void deleteStudent(Department *Dpt, int stud_id);

bool isEmpty(Department Dpt);
bool isFull(Department Dpt);
bool checkExistingStud(Department Dpt, int stud_id);

int searchStud(Department Dpt, int stud_id);
void emptyListMsg();
// void fullListMsg();
void shrinkStudCap(Department *Dpt, int init_cap);
void printStudents(Department Dpt);
void printStudDetail(Student stud);
SEX printSex(Sex sx);
MONTH printMonth(Month m);
COURSE printCourse(Course course);
ACCSTAT printAccStat(AccountStat accStat);



void clearList(Department *Dpt);

//filter functions
void filterBySex(Department Dpt, Sex sx);
void filterByCourse(Department Dpt, Course c);
void filterByYear(Department Dpt, int year);
void filterByAccStat(Department Dpt, AccountStat accStat);

SEX printSex(Sex sx)
{
    switch(sx)
    {
        case M: return "Male"; break;
        case F: return "Female"; break;
        default: return "XXXXX"; break;
    }
}

MONTH printMonth(Month m)
{
    switch(m)
    {
        case JANUARY: return "January"; break;
        case FEBRUARY: return "February"; break;
        case MARCH: return "March"; break;
        case APRIL: return "April"; break;
        case JUNE: return "June"; break;
        case JULY: return "July"; break;
        case AUGUST: return "August"; break;
        case SEPTEMBER: return "September"; break;
        case OCTOBER: return "October"; break;
        case NOVEMBER: return "November"; break;
        case DECEMBER: return "December"; break;
        default: return "XXXXX"; break;
    }
}

COURSE printCourse(Course course)
{
    switch(course)
    {
        case BSIS: return "BS Information Systems"; break;
        case BSIT: return "BS Information Technology"; break;
        case BSCS: return "BS Computer Science"; break;
        default: return "XXXXX"; break;
    }
}

ACCSTAT printAccStat(AccountStat accStat)
{
    switch(accStat)
    {
        case INACTIVE: return "Inactive"; break;
        case ACTIVE: return "Active"; break;
        default: return "XXXXX"; break;
    }
}

void initList(Department *Dpt)
{
    (*Dpt)->studCount = 0;
    (*Dpt)->Stud = (Student)malloc(sizeof(studType) * MAX_STUD);
    if((*Dpt)->Stud==NULL)
    {
        printf("\nMemory allocation failure\n");
        exit(1);
    }
}

void addStudent(Department *Dpt, Student stud)
{
    if(checkExistingStud(*Dpt, stud->id))
    {
        printf("\n\tStudent %d already exists!", stud->id);
        printStudDetail(stud);
    }
    else
    {
        if(((*Dpt)->studCount)==MAX_STUD)
        {
            printf("\nStudent capacity full! Reallocating...\n");
            int init_cap;
            init_cap = (*Dpt)->studCount;
            (*Dpt)->Stud = (Student)realloc((*Dpt)->Stud, sizeof(studType) * (init_cap + 1));
            if((*Dpt)->Stud==NULL)
            {
                printf("\nMemory allocation failure");
                exit(1);
            }
        }

        (*Dpt)->Stud[(*Dpt)->studCount++] = *stud;
        printf("\n**************\nSuccessfully added student %d.\n\n", stud->id);
    }
}

void printStudDetail(Student stud)
{
    printf("\n\t=======================\n");
    printf("\tID: %d\n", stud->id);
    printf("\tYear: %d\n", stud->year);
    printf("\tName: %s %c. %s\n", stud->FN, stud->MI, stud->LN);
    printf("\tDate of Birth: %s %d, %d\n", printMonth(stud->dob.m), stud->dob.day, stud->dob.year);
    printf("\tAge: %d\n", stud->age);
    printf("\tSex: %s\n", printSex(stud->sx));
    printf("\tCourse: %s\n", printCourse(stud->studCourse));
    printf("\t******************************\n\tACCOUNT DETAILS\n");
    printf("\tEmail: %s\n", stud->acc.email);
    printf("\tPassword: %s\n", stud->acc.password);
    printf("\tAccount Status: %s\n\n", printAccStat(stud->acc.accStat));
}

void printStudents(Department Dpt)
{
    if(isEmpty(Dpt))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n=======================================================================================================\n");
        printf("%-10s %-10s %-10s %-5s %-10s %-5s %-15s %-15s", "ID", "LASTNAME", "FIRSTNAME", "M.I.", "SEX", "YEAR", "AGE", "COURSE");
        printf("\n-------------------------------------------------------------------------------------------------------\n");
        int x;
        for(x=0; x<Dpt->studCount; x++)
        {
            printf("%-10d %-10s %-10s %-5c %-10s %-5d %-5d %-15s\n", Dpt->Stud[x].id, Dpt->Stud[x].LN, Dpt->Stud[x].FN, Dpt->Stud[x].MI, printSex(Dpt->Stud[x].sx), Dpt->Stud[x].year, Dpt->Stud[x].age, printCourse(Dpt->Stud[x].studCourse));
        }
        printf("==========================================================================================================\n\n");
    }
}

void shrinkStudCap(Department *Dpt, int init_cap)
{
    if(init_cap > MAX_STUD && init_cap > (*Dpt)->studCount)
    {
        printf("\n -- Shrinking the size... --\n");
        (*Dpt)->Stud = (Student)realloc((*Dpt)->Stud, sizeof(studType) * (*Dpt)->studCount);
        if((*Dpt)->Stud==NULL)
        {
            printf("\nMemory allocation failure\n");
            exit(1);
        }
    }
}

void deleteStudent(Department *Dpt, int stud_id)
{
    int retval = searchStud(*Dpt, stud_id);
    if(retval!=-1)
    {
        int x;
        int init_cap = (*Dpt)->studCount;
        for(x=retval; x<(*Dpt)->studCount-1; x++)
        {
            (*Dpt)->Stud[x] = (*Dpt)->Stud[x+1];
        }
        (*Dpt)->studCount--;
        shrinkStudCap(Dpt, init_cap);
    }
    else
    {
        printf("\nCannot find student with an ID of %d.\n\n", stud_id);
    }
}

int searchStud(Department Dpt, int stud_id)
{
    int x;
    for(x=0; x<Dpt->studCount && Dpt->Stud[x].id!=stud_id; x++){}

    return (Dpt->Stud[x].id==stud_id) ? x : -1;
}

bool checkExistingStud(Department Dpt, int stud_id)
{
    int x;
    for(x=0; x<Dpt->studCount && Dpt->Stud[x].id!=stud_id; x++){}

    return (Dpt->Stud[x].id==stud_id) ? true : false;
}

bool isEmpty(Department Dpt)
{
    return (Dpt->studCount==0) ? true : false;
}

bool isFull(Department Dpt)
{
    return (Dpt->studCount==MAX_STUD) ? true : false;
}

void emptyListMsg()
{
    printf("\n\n\t >> Student Records is Emtpy! <<");
}

void filterBySex(Department Dpt, Sex sx)
{
    if(isEmpty(Dpt))
    {
        emptyListMsg();
    }
    else
    {
        bool isFound = false;
        int x;
        printf("\n**********************\nFilter by Sex: %s\n", printSex(sx));
        printf("\n=============================================================================================\n");
        printf("%-10s %-10s %-10s %-5s %-10s %-5s %-15s %-15s", "ID", "LASTNAME", "FIRSTNAME", "M.I.", "SEX", "YEAR", "AGE", "COURSE");
        printf("\n---------------------------------------------------------------------------------------------\n");
        for(x=0; x<Dpt->studCount; x++)
        {
            if(Dpt->Stud[x].sx==sx)
            {
                isFound = true;
                printf("%-10d %-10s %-10s %-5c %-10s %-5d %-5d %-15s\n", Dpt->Stud[x].id, Dpt->Stud[x].LN, Dpt->Stud[x].FN, Dpt->Stud[x].MI, printSex(Dpt->Stud[x].sx), Dpt->Stud[x].year, Dpt->Stud[x].age, printCourse(Dpt->Stud[x].studCourse));
            }
        }
        printf("===============================================================================================\n\n");

        if(!isFound)
        {
            printf("\n\t>> No records found! <<\n\n");
        }
    }
}

void filterByYear(Department Dpt, int year)
{
    if(isEmpty(Dpt))
    {
        emptyListMsg();
    }
    else
    {
        bool isFound = false;
        int x;
        printf("\n*************************************\nFilter by Year: %d\n", year);
        printf("\n========================================================================================\n");
        printf("%-10s %-10s %-10s %-5s %-10s %-5s %-15s %-15s", "ID", "LASTNAME", "FIRSTNAME", "M.I.", "SEX", "YEAR", "AGE", "COURSE");
        printf("\n---------------------------------------------------------------------------------------\n");
        for(x=0; x<Dpt->studCount; x++)
        {
            if(Dpt->Stud[x].year==year)
            {
                isFound = true;
                printf("%-10d %-10s %-10s %-5c %-10s %-5d %-5d %-15s\n", Dpt->Stud[x].id, Dpt->Stud[x].LN, Dpt->Stud[x].FN, Dpt->Stud[x].MI, printSex(Dpt->Stud[x].sx), Dpt->Stud[x].year, Dpt->Stud[x].age, printCourse(Dpt->Stud[x].studCourse));
            }
        }
        printf("==========================================================================================\n\n");
        
        if(!isFound)
        {
            printf("\n\t>> No records found! <<\n\n");
        }
    }
}

void filterByAccStat(Department Dpt, AccountStat accStat)
{
    if(isEmpty(Dpt))
    {
        emptyListMsg();
    }
    else
    {
        bool isFound = false;
        int x;
        printf("\n**********************************************\nFilter by Account Status: %s\n", printAccStat(accStat));
        printf("\n=======================================================================================================================================\n");
        printf("%-10s %-10s %-10s %-5s %-10s %-5s %-15s %-25s %-25s %-15s", "ID", "LASTNAME", "FIRSTNAME", "M.I.", "SEX", "YEAR", "AGE", "COURSE", "EMAIL", "STATUS");
        printf("\n---------------------------------------------------------------------------------------------------------------------------------------\n");
        for(x=0; x<Dpt->studCount; x++)
        {
            if(Dpt->Stud[x].acc.accStat == accStat)
            {
                isFound = true;
                printf("%-10d %-10s %-10s %-5c %-10s %-5d %-5d %-30s %-30s %-15s\n", Dpt->Stud[x].id, Dpt->Stud[x].LN, Dpt->Stud[x].FN, Dpt->Stud[x].MI, printSex(Dpt->Stud[x].sx), Dpt->Stud[x].year, Dpt->Stud[x].age, printCourse(Dpt->Stud[x].studCourse), Dpt->Stud[x].acc.email, printAccStat(Dpt->Stud[x].acc.accStat));
            }
        }
        printf("==========================================================================================================================================\n\n");

        if(!isFound)
        {
            printf("\n\t>> No records found! <<\n\n");
        }
    }
}

void filterByCourse(Department Dpt, Course c)
{
    if(isEmpty(Dpt))
    {
        emptyListMsg();
    }
    else
    {
        bool isFound = false;
        printf("\n*******************************************\nFilter by Course: %s\n", printCourse(c));
        printf("\n===============================================================================================\n");
        printf("%-10s %-10s %-10s %-5s %-5s %-15s %-15s", "NAME", "LASTNAME", "FIRSTNAME", "M.I.", "YEAR", "AGE", "COURSE");
        printf("\n-----------------------------------------------------------------------------------------------\n");
        int x;
        for(x=0; x<Dpt->studCount; x++)
        {
            if(c == Dpt->Stud[x].studCourse)
            {
                isFound = true;
                printf("%-10d %-10s %-10s %-5c %-5d %-5d %-15s\n", Dpt->Stud[x].id, Dpt->Stud[x].LN, Dpt->Stud[x].FN, Dpt->Stud[x].MI, Dpt->Stud[x].year, Dpt->Stud[x].age, printCourse(Dpt->Stud[x].studCourse));
            }
        }
        printf("==============================================================================================\n\n");

        if(!isFound)
        {
            printf("\n\t>> No records found! <<\n\n");
        }
    }
}

void populate(Department *Dpt)
{
    studType stud1 = {19103991, "Shannen", "Nazareno", 'T', 3, 21, F, {SEPTEMBER, 26, 2002}, BSIS, {"nzrnshannen@gmail.com", "shannenPass", ACTIVE}};
    studType stud2 = {123456789, "Butter", "Cup", 'N', 1, 2, F, {JANUARY, 5, 2022}, BSIT, {"buttercup@gmail.com", "testButter", INACTIVE}};
    studType stud3 = {1010110, "Yollie", "Cups", 'N', 1, 1, F, {MARCH, 20, 2023}, BSCS, {"yollie@gmail.com", "testYol", ACTIVE}};
    addStudent(Dpt, &stud1);
    addStudent(Dpt, &stud2);
    addStudent(Dpt, &stud3);
    addStudent(Dpt, &stud1);
    
}

void clearList(Department *Dpt)
{
    free((*Dpt)->Stud);
    (*Dpt)->Stud = NULL;
}

int main()
{
    deptType DCISM;
    Department sas = &DCISM;
    initList(&sas);

    populate(&sas);
    // deleteStudent(&sas, 19103991);
    // deleteStudent(&sas, 123456789);
    printStudents(sas);
    //deleteStudent(&sas, 19103991);
    printStudents(sas);

    filterByAccStat(sas, ACTIVE);
    filterByCourse(sas, BSIT);
    filterBySex(sas, F);
    filterByYear(sas, 4);
    clearList(&sas);
    return 0;
}