/*===========================================================================

Name: Shannen T. Nazareno
Date: 01/09/2024
Program: Creating Student Records with Cursor-Based Implementation (ADT LIST)

Functions to be created:
* filter functions:
    - by sex /
    - by year/
    - by course/
* printStudentDetails /
    
===========================================================================*/


#include<stdio.h>
#include<stdbool.h>
#define SIZE 5

typedef char* SEX;
typedef char* MONTH;
typedef char* COURSE;

typedef enum{
    BSIS = 1,
    BSIT,
    BSCS
}Course;

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

typedef struct{
    Month m;
    int day;
    int year;
}Date;

typedef struct{
    int id;
    int year;
    char FN[30], LN[30];
    char MI;
    Sex sx;
    Date dob;
    Course course;
    Date enrollDate;
}stud;

typedef struct{
    stud studInfo;
    int link;
}studType;

typedef struct{
    studType Student[SIZE];
    int avail;
}VirtualHeap;

typedef int CLIST;

void initCList(CLIST *C);
void initVirtualHeap(VirtualHeap *VH);
void addStudent(CLIST *C, VirtualHeap *VH, stud studInfo);
void deleteStudent(CLIST *C, VirtualHeap *VH, int id);

int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int ndx);

void displayStudentList(CLIST C, VirtualHeap VH);
void printStudentDetails(stud Student);

bool checkIfEnrolled(CLIST *C, VirtualHeap *VH, int id);

SEX printSex(Sex sx);
COURSE printCourse(Course c);
MONTH printMonth(Month m);

void populate(CLIST *C, VirtualHeap *VH);

//filter functions
void filterBySex(CLIST C, VirtualHeap VH, Sex sx);
void filterByYear(CLIST C, VirtualHeap VH, int year);
void filterByCourse(CLIST C, VirtualHeap VH, Course course);


int searchStudent(CLIST *C, VirtualHeap *VH, int id)
{
    int x;
    for(x=*C; x!=-1 && VH->Student[x].studInfo.id!=id; x=VH->Student[x].link){}

    return x;
}

void initVirtualHeap(VirtualHeap *VH)
{
    VH->avail = SIZE-1;
    int x;
    for(x=VH->avail; x>=0; x--)
    {
        VH->Student[x].link = x-1;
    }
}

void initCList(CLIST *C)
{
    *C = -1;
}

int allocSpace(VirtualHeap *VH)
{
    int retval = VH->avail;

    if(retval!=-1)
    {
        VH->avail = VH->Student[retval].link;
    }

    printf("\nprinting retval = %d\n", retval);
    return retval;
}

SEX printSex(Sex sx)
{
    switch(sx)
    {
        case F: return "Female"; break;
        case M: return "Male"; break;
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
        case MAY: return "May"; break;
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

COURSE printCourse(Course c)
{
    switch(c)
    {
        case BSIS: return "BS Information Systems"; break;
        case BSCS: return "BS Computer Science"; break;
        case BSIT: return "BS Information Technology"; break;
        default: return "XXXXX"; break;
    }
}

bool checkIfEnrolled(CLIST *C, VirtualHeap *VH, int id)
{
    int x;
    for(x=*C; x!=-1 && VH->Student[x].studInfo.id!=id; x=VH->Student[x].link){}
    //x!=-1 instead of x!=VH->Avail
    //considering that we don't have a node yet with (*C is -1) as list is empty,
    //meaning x = -1 here
        //doing x!=VH->Avail will satisfy the condition and we'll reach the 2nd test case:
        //VH->Student[x].studIn fo.id!=id ===> VH->Student[-1].studInfo.id!=id will results into an error
    return (x!=-1 && VH->Student[x].studInfo.id==id)? true : false;
}

void addStudent(CLIST *C, VirtualHeap *VH, stud studInfo)
{
    if(checkIfEnrolled(C, VH, studInfo.id))
    {
        printf("\n\tStudent %d already enrolled!\n\n", studInfo.id);
        int ndx = searchStudent(C, VH, studInfo.id);
        printStudentDetails(VH->Student[ndx].studInfo);
    }
    else
    {
        int ndx = allocSpace(VH);
        if(ndx!=-1)
        {
            VH->Student[ndx].studInfo = studInfo;
            VH->Student[ndx].link = -1;

            if(*C==-1)
            {
                *C = ndx;
            }
            else
            {
                int x;
                for(x=*C; VH->Student[x].link!=-1; x=VH->Student[x].link){}
                VH->Student[x].link = ndx;
            }
        }
        else
        {
            printf("\n\tStudent list already full!\n\n");
        }
    }
}

void deallocSpace(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx < SIZE)
    {
        VH->Student[ndx].link = VH->avail;
        VH->avail = ndx;
    }
}

void deleteStudent(CLIST *C, VirtualHeap *VH, int id)
{
    if(*C==-1)
    {
        printf("\n\tStudent list is empty!\n\n");
    }
    else 
    {
        int ndx = searchStudent(C, VH, id);
        if(ndx!=-1) 
        {
            if(ndx==*C)
            {
                *C = VH->Student[ndx].link;
            }
            else
            {
                int x;
                for(x=*C; VH->Student[x].link!=ndx; x=VH->Student[x].link){}

                VH->Student[x].link = VH->Student[ndx].link;
            }

            deallocSpace(VH, ndx);
            printf("\n\tStudent %d deleted.\n\n", id);
        }   
        else
        {
            printf("\n\tStudent %d does not exists!\n\n", id);
        }
    }
}


void displayStudentList(CLIST C, VirtualHeap VH)
{
    if(C==-1)
    {
        printf("\nList is empty!\n");
    }
    else
    {
        int x;
        printf("\n==============================================================================================================================\n");
        printf("%-15s %-15s %-15s %-15s %-15s %-15s %-30s\n", "ID | ", "LASTNAME | ", "FIRSTNAME | ", "M.I | ", "SEX | ", "YEAR | ", "COURSE");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        for(x=C; x!=-1; x=VH.Student[x].link)
        {
            printf("%-15d %-15s %-15s %-15c %-15s %-15d %-30s\n", VH.Student[x].studInfo.id, VH.Student[x].studInfo.LN, VH.Student[x].studInfo.FN, VH.Student[x].studInfo.MI, printSex(VH.Student[x].studInfo.sx), VH.Student[x].studInfo.year, printCourse(VH.Student[x].studInfo.course));
        }
    }
}

void filterBySex(CLIST C, VirtualHeap VH, Sex sx)
{
    if(C==-1)
    {
        printf("\n\tStudent list is empty!\n\n");
    }
    else
    {
        bool isFound = false;
        int x;
        printf("\n********************************************\nFilter by sex: %s\n\n", printSex(sx));
        printf("%-15s %-15s %-15s %-15s %-15s %-15s %-30s\n", "ID | ", "LASTNAME | ", "FIRSTNAME | ", "M.I | ", "SEX | ", "YEAR | ", "COURSE");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");
        for(x=C; x!=-1; x=VH.Student[x].link)
        {
            if(VH.Student[x].studInfo.sx==F)
            {
                isFound = true;
                printf("%-15d %-15s %-15s %-15c %-15s %-15d %-30s\n", VH.Student[x].studInfo.id, VH.Student[x].studInfo.LN, VH.Student[x].studInfo.FN, VH.Student[x].studInfo.MI, printSex(VH.Student[x].studInfo.sx), VH.Student[x].studInfo.year, printCourse(VH.Student[x].studInfo.course));
            }
        }

        if(!isFound)
        {
            printf("\n\t\tNo records found!\n\n");
        }
    }
}

void filterByYear(CLIST C, VirtualHeap VH, int year)
{
    if(C==-1)
    {
        printf("\n\tStudent list is empty!\n\n");
    }
    else
    {
        bool isFound = false;
        int x;
        printf("\n*********************************\nFilter by Year: %d\n\n", year);
        printf("%-15s %-15s %-15s %-15s %-15s %-15s %-30s\n", "ID | ", "LASTNAME | ", "FIRSTNAME | ", "M.I | ", "SEX | ", "YEAR | ", "COURSE");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");

        for(x=C; x!=-1; x=VH.Student[x].link)
        {
            if(VH.Student[x].studInfo.year==year)
            {
                isFound = true;
                printf("%-15d %-15s %-15s %-15c %-15s %-15d %-30s\n", VH.Student[x].studInfo.id, VH.Student[x].studInfo.LN, VH.Student[x].studInfo.FN, VH.Student[x].studInfo.MI, printSex(VH.Student[x].studInfo.sx), VH.Student[x].studInfo.year, printCourse(VH.Student[x].studInfo.course));
            }
        }
        
        if(!isFound)
        {
            printf("\n\t\tNo records found!\n\n");
        }
    }
}

void filterByCourse(CLIST C, VirtualHeap VH, Course course)
{
    if(C==-1)
    {
        printf("\n\tStudent list is empty!\n\n");
    }
    else
    {
        bool isFound = false;
        int x;
        printf("\n************************************\nFilter by course: %s\n\n", printCourse(course));
        printf("%-15s %-15s %-15s %-15s %-15s %-15s %-30s\n", "ID | ", "LASTNAME | ", "FIRSTNAME | ", "M.I | ", "SEX | ", "YEAR | ", "COURSE");
        printf("------------------------------------------------------------------------------------------------------------------------------\n");

        for(x=C; x!=-1; x=VH.Student[x].link)
        {
            if(VH.Student[x].studInfo.course==course)
            {
                isFound=true;
                printf("%-15d %-15s %-15s %-15c %-15s %-15d %-30s\n", VH.Student[x].studInfo.id, VH.Student[x].studInfo.LN, VH.Student[x].studInfo.FN, VH.Student[x].studInfo.MI, printSex(VH.Student[x].studInfo.sx), VH.Student[x].studInfo.year, printCourse(VH.Student[x].studInfo.course));
            }
        }

        if(!isFound)
        {
            printf("\n\t\tNo records found!\n\n");
        }
    }
}

void printStudentDetails(stud Student)
{
    printf("\n\t==================================================================\n");
    printf("\tID: %d\n", Student.id);
    printf("\tYear: %d\n", Student.year);
    printf("\tCourse: %s\n", printCourse(Student.course));
    printf("\tDate enrolled: %s %d, %d\n", printMonth(Student.enrollDate.m), Student.enrollDate.day, Student.enrollDate.year);
    printf("\tName: %s %c. %s\n", Student.FN, Student.MI, Student.LN);
    printf("\tSex: %s\n", printSex(Student.sx));
    printf("\tBirthday: %s %d, %d\n\n", printMonth(Student.dob.m), Student.dob.day, Student.dob.year);
}

void populate(CLIST *C, VirtualHeap *VH)
{
    stud s1 = {19103991, 3, "Shannen", "Nazareno", 'T', F, {SEPTEMBER, 26, 2002}, BSIS, {JANUARY, 5, 2024}};
    stud s2 = {11500160, 3, "Clint", "Englis", 'C', M, {JANUARY, 25, 2002}, BSIS, {JANUARY, 6, 2024}};
    stud s3 = {1910421, 2, "Shannen", "Nazareno", 'T', F, {SEPTEMBER, 26, 2002}, BSIS, {JANUARY, 5, 2024}};
    addStudent(C, VH, s1);
    addStudent(C, VH, s2);
    addStudent(C, VH, s3);
    addStudent(C, VH, s1);
}

int main()
{
    VirtualHeap VHeap;
    CLIST DCISM;

    initCList(&DCISM);
    initVirtualHeap(&VHeap);


    populate(&DCISM, &VHeap);

    displayStudentList(DCISM, VHeap);
    deleteStudent(&DCISM, &VHeap, 11500160);
    displayStudentList(DCISM, VHeap);
    filterByYear(DCISM, VHeap, 3);
    filterByCourse(DCISM, VHeap, BSIS);
    return 0;
}