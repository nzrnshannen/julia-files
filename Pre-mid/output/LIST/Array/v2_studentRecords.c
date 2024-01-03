/*=========================================================================================

Name: Shannen T. Nazareno
Date: 01/03/2024
Program: ADT List using Array Implementation version 2 to make students records for a class
Functions to be added: filter()
- by sex
- by account status (active, inactive)
===========================================================================================*/

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX_STUD 5

typedef enum {F = 1 , M} Sex;
typedef enum {INACTIVE, ACTIVE} Status;
typedef enum {
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
} Month;

typedef struct{
    char email[30];
    char password[25];
    Status accStat;
}StudAcc;

typedef struct{
    Month m;
    int date;
    int year;
}DOB;

typedef struct{
    int ID;
    char FN[30], LN[30];
    char MI;
    int age;
    Sex z;
    DOB dateOfBirth;
    StudAcc acc;
}Student;

typedef struct{
    char FN[30], LN[30];
    char MI;
    int age;
    Sex z;
}Adviser;

typedef struct{
    Student stud[MAX_STUD];
    int studCount;
    char section;
    int year;
    Adviser a;
}classType, *Class;

void initializeClassList(Class C);
void addStudent(Class C, Student S);
void removeStudent(Class C, int id);
void displayClassList(Class C);
void populate(Class C);

bool isEmptyClass(Class C);
bool isFullClass(Class C);
bool studentCheck(Class C, int id);

char* printSex(Sex z);
char* printAccStatus(Status accStat);
void populate(Class C);

char* printAccStatus(Status accStat)
{
    return (accStat) ? "ACTIVE" : "INACTIVE";
}

char* printSex(Sex z)
{
    return (z == F) ? "FEMALE" : "MALE";
}



void emptyClassListMsg()
{
    printf("\n\n\t >> Class list is empty. Add a student. <<\n\n");
}

void fullClassListMsg()
{
    printf("\n\n\t>> Class list already full! <<\n\n");
}

bool isEmptyClass(Class C)
{
    return (C->studCount==0) ? true : false;
}

bool isFullClass(Class C)
{
    return (C->studCount==MAX_STUD) ? true : false;
}

bool studentCheck(Class C, int id)
{
    int x;
    for(x=0; x<C->studCount && C->stud[x].ID!=id; x++){}

    return (C->stud[x].ID==id) ? true : false;
}

void initializeClassList(Class C)
{
    C->studCount=0;
}

void displayClassList(Class C)
{
    if(isEmptyClass(C))
    {
        emptyClassListMsg();
    }
    else
    {
        int x;
        printf("\n\n");
        printf("CLASS %c\n", C->section);
        printf("Adviser: %s %c. %s\n\n", C->a.FN, C->a.MI, C->a.LN);
        printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
        printf("%-15s %-12s %-12s %-5s %-7s %-15s %-15s %-25s %-10s %-15s\n\n", "ID", "LASTNAME", "FIRSTNAME", "M.I.", "AGE", "SEX", "DATE OF BIRTH", "EMAIL", "PASSWORD", "STATUS");
        for(x=0; x<C->studCount; x++)
        {
            printf("%-15d %-12s %-12s %-5c %-7d %-15s %d/%d/%-10d %-25s %-10s %-15s\n", C->stud[x].ID, C->stud[x].LN, C->stud[x].FN, C->stud[x].MI, C->stud[x].age, printSex(C->stud[x].z), C->stud[x].dateOfBirth.m, C->stud[x].dateOfBirth.date, C->stud[x].dateOfBirth.year, C->stud[x].acc.email, C->stud[x].acc.password, printAccStatus(C->stud[x].acc.accStat));
        }

        printf("\n\n");
    }
}

void addStudent(Class C, Student S)
{
    if(isFullClass(C))
    {
        fullClassListMsg();
    }
    else
    {
        if(studentCheck(C, S.ID))
        {
            printf("\n\n\t --> Student %d already exists! <--\n\n", S.ID);
        }
        else
        {
            C->stud[C->studCount++] = S;

            printf("\n\n\t --> Successfully added student %d. <--\n\n", S.ID);
        }
    }
}

void removeStudent(Class C, int id)
{
    if(isEmptyClass(C))
    {
        emptyClassListMsg();
    }
    else if(!studentCheck(C, id))
    {
        printf("\n*************************\nStudent %d doesn't exists!\n\n", id);
    }
    else
    {
        int x;
        for(x=0; x<C->studCount && C->stud[x].ID!=id; x++){}

        int y; //we can use x in this since x is still at the position where == id
                //but to avoid confusion, I use variable y

        for(y=x; y<C->studCount-1; y++)
        {
            C->stud[x] = C->stud[x+1];
        }
        C->studCount--;

        printf("\n\n\t----------------------------\n");
        printf("\n\tStudent %d removed from the class.\n\n", id);
        displayClassList(C);
    }
}

void populate(Class C)
{
    Adviser a1 = {"testFNAdv", "testLNAdv", 'C', 30, F};
    C->a = a1;
    C->year = 3;
    C->section = 'B';
    Student s1 = {19103991, "Shannen", "Nazareno", 'T', 21, F, {SEPTEMBER, 26, 2002}, {"nzrnshannen@gmail.com", "testPass", ACTIVE}};
    Student s2 = {11500160, "Clint", "Englis", 'C', 21, M, {JANUARY, 28, 2002}, {"clint@gmail.com", "clint123", INACTIVE}};

    addStudent(C, s1);
    addStudent(C, s2);
}

int main()
{
    classType A;
    initializeClassList(&A);
    populate(&A);
    displayClassList(&A);
    removeStudent(&A, 19103991);

    return 0;
}