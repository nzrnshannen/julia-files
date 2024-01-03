#include<stdio.h>
#include<stdbool.h>
#define SIZE 10 //deleteStudent() doesn't work if SIZE is 1

typedef enum {INACTIVE, ACTIVE} accType;
typedef enum {F = 1, M} sex;
typedef struct{
    char email[30], password[20];
    accType status;
}studAcc;
typedef struct {
    int id;
    char FN[30], LN[30], course[30];
    char MI;
    int year;
    studAcc acc;
    sex a;
    int age;
}studList;

typedef struct{
    studList S[SIZE];
    int count;
}studRec;

void initializeList(studRec *stud);
void addStudent(studRec *stud, studList details);
void deleteStudent(studRec * stud, int id);
void filterByYear(studRec stud, int year);
void displayRecords(studRec stud);

bool searchStudent(studRec stud, int id);

void emptyRecordsMsg();
void fullRecordsMsg();

void addStudent(studRec *stud, studList details)
{
    if(searchStudent(*stud, details.id))
    {
        printf("\n\n\tStudent [%d] already exists!\n\n", details.id);
    }
    else if(stud->count==SIZE)
    {
        printf("\n\n\tList is full!\n\n");
    }
    else
    {
        stud->S[stud->count++] = details;
        printf("\n\n\tStudent [%d] added.\n\n", details.id);
    }
}   

void initializeList(studRec *stud)
{
    stud->count = 0;
}

bool searchStudent(studRec stud, int id)
{
    int x;
    for(x=0; x<stud.count && stud.S[x].id!=id; x++){}

    return (stud.S[x].id==id) ? true : false;
}

char* printSex(sex s)
{
    return (s == F)? "Female": "Male";
}

char* printStats(accType stat)
{
    return (stat == ACTIVE) ? "Active" : "Inactive";
}

void deleteStudent(studRec *stud, int id)
{
    if(stud->count==SIZE)
    {
        fullRecordsMsg();
    }
    else
    {
        int x;
        for(x=0; x<stud->count && stud->S[x].id!=id; x++){}

        if(x < stud->count && stud->S[x].id==id)
        {
            if(stud->count==1)
            {
                stud->count=0;
            }
            else
            {
                int y;
                for(y=x; y<stud->count-1; y++)
                {
                    stud->S[y] = stud->S[y+1];
                }
                stud->count--;

                printf("\n-------------------\n");
                printf("\nStudent [%d] removed.\n", id);
                printf("\n-------------------\n\n");
            }
        }
        else
        {
            printf("\n\n\tStudent %d doesn't exists!\n\n", id);
        }
    }
}

void fullRecordsMsg()
{
    printf("\n\n >> List is full. Cannot add anymore students. << \n\n");
}

void emptyRecordsMsg()
{
    printf("\n\n >> List is empty. Please add a student. <<\n\n");
}

void displayRecords(studRec stud)
{
    if(stud.count==0)
    {
        emptyRecordsMsg();
    }
    else
    {
        int x;
        for(x=0; x<stud.count; x++)
        {
            printf("\n-----------------------\n");
            printf("ID: %d\n", stud.S[x].id);
            printf("Year: %d\n", stud.S[x].year);
            printf("Name: %s %c. %s\n", stud.S[x].FN, stud.S[x].MI, stud.S[x].LN);
            printf("Sex: %s\n", printSex(stud.S[x].a));
            printf("Age: %d\n", stud.S[x].age);
            printf("Course: %s\n", stud.S[x].course);
            printf("Email: %s\n", stud.S[x].acc.email);
            printf("Account status: %s\n\n", printStats(stud.S[x].acc.status));
        }
    }
}

void populate(studRec *stud)
{
    studList stud1 = {19103991, "Shannen", "Nazareno", "Information Systems", 'T', 2, {"nzrnshannen@gmail.com", "test", ACTIVE}, F, 21};
    addStudent(stud, stud1);

    studList stud2 = {123, "Clint", "Englis", "Information Systems", 'C', 3, {"clint@gmail.com", "cat", INACTIVE}, M, 21};
    addStudent(stud, stud2);
}

void filterByYear(studRec stud, int year)
{
    if(stud.count==0)
    {
        emptyRecordsMsg();
    }
    else
    {
        int x;
        int flag = 0; //can use enum here instead
        printf("\nFilter by year: %d\n", year);
        for(x=0; x<stud.count; x++)
        {
            if(stud.S[x].year==year)
            {
                flag = 1;
                printf("---------------------------------\n");
                printf("Year: %d\n", stud.S[x].year);
                printf("ID: %d\n", stud.S[x].id);
                printf("Course: %s\n", stud.S[x].course);
                printf("Name: %s %c. %s\n", stud.S[x].FN, stud.S[x].MI, stud.S[x].LN);
                printf("Age: %d\n", stud.S[x].age);
                printf("Sex: %s\n", printSex(stud.S[x].a));
                printf("Email: %s\n", stud.S[x].acc.email);
                printf("Account status: %s\n\n", printStats(stud.S[x].acc.status));
            }
        }

        if(flag==0)
        {
            printf("\n\nNo record!\n\n");
        }
    }
}
int main()
{
    studRec s1;
    initializeList(&s1);
    populate(&s1);
    //deleteStudent(&s1, 19103991);
    displayRecords(s1);
    filterByYear(s1, 1);
    return 0;
}