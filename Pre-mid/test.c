/*=====================================================================================================
Created by: Shannen T. Nazareno
Date: 12/27/2023

Notes:
1. Will add yr and dept for studRec
2. + functions: filterByYrLvl, filterByDept, sortByYrLvl
3. + : enum for departments (DCISM = 1, etc)
4. + : before adding a student, check if course is present in the department
5. Menu [add, delete(w/ clearStudRec option), search(w/ filter), sort, checkAvailability(isPresent())]


Functions to be implemented:
sort by id, fname, lname
clearStudRec == clear a section (probably or given year lvl)
======================================================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define SIZE 20
#define NULL_VAL -9999999

typedef struct{
    int id;
    char fName[SIZE], lName[SIZE];
    char mid_init;
    char course[SIZE];
}studRec;

typedef struct node{
    studRec Stud;
    struct node *next_rec;
}studType, *LIST;

void initList(LIST* L);
void insertUnique(LIST *L, studRec S);
void printRecords(LIST L);

bool isEmpty(LIST L);
bool isPresent(LIST L, int id);

void emptyListMsg();
void noExistingRecMsg();

studRec searchStud(LIST L, int id);

void filterByFname(LIST L, char *f_name);
void filterByLname(LIST L, char *l_name);
void filterByCourse(LIST L, char *course);
//isPresent /
//searchStud /
//filterByFName /
//filterByLName /
//filterByCourse /
//sortByID
//sortByFName
//sortByLName
//deleteStudent(id) /
//clearStudRec

bool isEmpty(LIST L)
{
    return (L==NULL);
}

bool isPresent(LIST L, int id)
{
    LIST trav;
    for(trav=L; trav!=NULL && trav->Stud.id!=id; trav=trav->next_rec){}

    return (trav!=NULL && trav->Stud.id==id) ? true : false;
}

studRec searchStud(LIST L, int id)
{
    studRec null_stud = {NULL_VAL, "XXXXX", "XXXXX", 'X', "XXXXX"};
    LIST check;
    for(check=L; check!=NULL && check->Stud.id!=id; check=check->next_rec){}

    return (check!=NULL && check->Stud.id==id) ? check->Stud : null_stud;
}

void emptyListMsg()
{
    printf("\n\nNo student records yet!\n\n");
}

void noExistingRecMsg()
{
    printf("\n\n\tStudent doesn't exists!\n\n");
}

void initList(LIST *L)
{
    *L = NULL;
}

void insertUnique(LIST *L, studRec S)
{
    LIST check = *L;
    for(check = *L; check!=NULL&&check->Stud.id!=S.id; check=check->next_rec){}
    
    if(check==NULL)
    {
        LIST newStud = (LIST)malloc(sizeof(studType));
        if(newStud==NULL)
        {
            printf("\nMemory allocation failure!");
            exit(1);
        }

        newStud->Stud = S;
        newStud->next_rec = *L;
        *L = newStud;

        printf("\n\tSuccessfully added student [%d]\n\n", S.id);
    }
    else
    {
        printf("\n\tStudent record already exists!\n\n");
    }
    
}

void printRecords(LIST L)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST trav;
        int ctr = 1;

        printf("\n****************************\n");
        for(trav=L; trav!=NULL; trav=trav->next_rec)
        {
            printf("\tSTUDENT %d\n\n", ctr++);
            printf("ID: %d\n", trav->Stud.id);
            printf("Name: %s %c. %s\n", trav->Stud.fName, trav->Stud.mid_init, trav->Stud.lName);
            printf("Course: %s\n\n", trav->Stud.course);
        }
    }
}

void deleteStudent(LIST *L, int id)
{
    if(isEmpty(*L))
    {
        emptyListMsg();
    }
    else
    {
        LIST *trav;
        for(trav=L; *trav!=NULL && (*trav)->Stud.id!=id; trav=&(*trav)->next_rec){}

        if(*trav!=NULL && (*trav)->Stud.id==id )
        {   
            LIST temp;

            if(trav==L)
            {
                temp = *L;
                *L = (*L)->next_rec;
                
            }
            else
            {
                temp = *trav;
                *trav = temp->next_rec;
            }

            free(temp);

            printf("\n\tSuccessfully removed Student [%d]\n\n", id);
        }
        else
        {
            noExistingRecMsg();
        }
    }
}

void filterByFname(LIST L, char *f_name)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by first name: %s\n\n--------------------------------------------------------------------------------------------------------------------------\n", f_name);
        for(check=L; check!=NULL && (strcmp(f_name, check->Stud.fName)!=0); check=check->next_rec){}

        if(check==NULL || strcmp(f_name, check->Stud.fName)!=0)
        {
            noExistingRecMsg();
        }
        else
        {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %s\n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(strcmp(trav->Stud.fName, f_name)==0)
                {
                    printf("%-15d %-15s %-15s %-17c %s\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course);
                }
            }
            printf("\n=================\n\n");
        }
    }
}

void filterByLname(LIST L, char *l_name)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by last name: %s\n\n--------------------------------------------------------------------------------------------------------------------------\n", l_name);
        for(check=L; check!=NULL && (strcmp(l_name, check->Stud.lName)!=0); check=check->next_rec){}

        if(check==NULL || strcmp(l_name, check->Stud.lName)!=0)
        {
            noExistingRecMsg();
        }
        else
        {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %s\n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(strcmp(trav->Stud.lName, l_name)==0)
                {
                    printf("%-15d %-15s %-15s %-17c %s\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course);
                }
            }
            printf("\n=================\n\n");
        }
    }
}

void filterByCourse(LIST L, char *course)
{
    if(isEmpty(L))
    {
        emptyListMsg();
    }
    else
    {
        LIST check;
        
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nFilter by course: %s\n\n--------------------------------------------------------------------------------------------------------------------------\n", course);
        for(check=L; check!=NULL && (strcmp(course, check->Stud.course)!=0); check=check->next_rec){}

        if(check==NULL || strcmp(check->Stud.course, course)!=0)
        {
            noExistingRecMsg();
        }
        else
        {
            LIST trav;
            printf("%-12s | %-12s | %-15s | %-15s | %s\n", "ID", "FIRST NAME", "LAST NAME", "M.I", "COURSE");
            for(trav=L; trav!=NULL; trav=trav->next_rec)
            {
                if(strcmp(trav->Stud.course, course)==0)
                {
                    printf("%-15d %-15s %-15s %-17c %s\n", trav->Stud.id, trav->Stud.fName, trav->Stud.lName, trav->Stud.mid_init, trav->Stud.course);
                }
            }
            printf("\n=================\n\n");
        }
    }
}

int main()
{
    LIST section_A;
    studRec stud1 = {19103991, "Shannen", "Nazareno", 'T', "Information Systems"}; 
    studRec stud2 = {9999, "Clint", "Englis", 'C', "Information Systems"};
    studRec stud3 = {9234, "Shannen", "Englis", 'C', "Information Systems"};

    initList(&section_A);

    insertUnique(&section_A, stud1);
    insertUnique(&section_A, stud2);
    insertUnique(&section_A, stud3);

    printRecords(section_A);

    deleteStudent(&section_A, 1910399);
    printRecords(section_A);

    //printf("Is present? %d", isPresent(section_A, 19103991));
    // studRec testRetrieve = searchStud(section_A, 1910399);

    filterByCourse(section_A, "Information Systems");

    return 0;
}