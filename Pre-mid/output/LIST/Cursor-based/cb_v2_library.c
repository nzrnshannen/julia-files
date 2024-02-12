//not working properly atm

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define MAX_BOOKS 5
#define MAX_AUTH 3

typedef char* GENRE;
typedef char* SEX;
typedef char* BOOKSTATUS;

typedef enum{M, F} Sex;
typedef enum{BORROWED, AVAILABLE} BookStatus;
//add enum for GENRE

typedef enum{ //only 5 because this is only for testing purposes
    FANTASY=1,
    MYSTERY,
    SELF_HELP,
    ROMANCE,
    SCIFI
}Genre;

typedef struct{
    char FN[30], LN[30];
    char MI;
    int authorID;
    Sex sx;
}Author;

typedef struct{
    int bookID;
    char title[100];
    Author author;
    int year;
    int no_of_pages;
    BookStatus bookStatus;
    Genre genre;
}Book;

typedef struct{
    Book book;
    int link;
}bookSection;

typedef struct{
    Author author;
    int link;
}authorSection;

typedef struct{
    bookSection Books[MAX_BOOKS];
    authorSection Author[MAX_AUTH];
    int book_avail;
    int author_avail;
}Library, *VirtualHeap;

typedef int CLIST;

void deallocSpaceForBooks(VirtualHeap *VH, int ndx);
void deallocSpaceForAuth(VirtualHeap *VH, int ndx);
int allocSpaceForBooks(VirtualHeap *VH);
int allocSpaceForAuth(VirtualHeap *VH);
void initCList(CLIST *C);
void initAuthVirtualHeap(VirtualHeap *VH); //using version 1
void initBookVirtualHeap(VirtualHeap *VH); //using version 2


bool isEmpty(CLIST C);
bool isFull(VirtualHeap VH); //for books

void populateBooks(CLIST *C, VirtualHeap *VH);
void populateAuthors(CLIST *C, VirtualHeap *VH);

void addBook(CLIST *C, VirtualHeap *VH, Book book); //insert sorted
void deleteBookById(CLIST *C, VirtualHeap *VH, int bookID);
int searchBook(CLIST *C, VirtualHeap *VH, int bookID);
bool checkBookExistence(CLIST *C, VirtualHeap *VH, Book book);

void addAuthor(CLIST *C, VirtualHeap *VH, Author auth); //insert at end
void deleteAuthorById(CLIST *C, VirtualHeap *VH, int authID);
int searchAuthor(CLIST *C, VirtualHeap *VH, int authID);
bool checkAuthorExistence(CLIST *C, VirtualHeap *VH, Author auth);


void printAllBooks(CLIST *C, VirtualHeap *VH);
void printAllAuthors(CLIST *C, VirtualHeap *VH);
void printBookDetails(Book book);
void printAuthDetails(Author auth);

void filterBooksByAuth(CLIST *C, VirtualHeap *VH, int authID);
void filterBooksByGenre(CLIST *C, VirtualHeap *VH, Genre genre);
void fullListMsg();
void emptyListMsg();


void initCList(CLIST *C)
{
    *C = -1;
}

void fullListMsg()
{
    printf("\n\n\tList is full!\n\n");
}

void emptyListMsg()
{
    printf("\n\n\tList is empty!\n\n");
}

void initAuthVirtualHeap(VirtualHeap *VH)
{
    (*VH)->author_avail = 0;
    int x;
    for(x=0; x<MAX_AUTH-1; x++)
    {
        (*VH)->Author[x].link = x+1;
    }
    (*VH)->Author[x].link = -1;
}  

void initBookVirtualHeap(VirtualHeap *VH)
{
    (*VH)->book_avail = MAX_BOOKS-1;
    int x;
    for(x=(*VH)->book_avail; x>=0; x--)
    {
        (*VH)->Books[x].link = x-1;
    }
}

bool isEmpty(CLIST C)
{
    return (C==-1)? true: false;
}

bool isFull(VirtualHeap VH)
{
    return (VH->book_avail==-1) ? true: false;
}

int allocSpaceForBooks(VirtualHeap *VH)
{
    int retval = (*VH)->book_avail;
    if(retval!=-1)
    {
        (*VH)->book_avail = (*VH)->Books[retval].link;
    }

    return retval;
}

int allocSpaceForAuth(VirtualHeap *VH)
{
    int retval = (*VH)->author_avail;
    if(retval!=-1)
    {
        (*VH)->author_avail = (*VH)->Author[retval].link;
    }

    return retval;
}

void deallocSpaceForBooks(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<MAX_BOOKS)
    {
        (*VH)->Books[ndx].link = (*VH)->book_avail;
        (*VH)->book_avail = ndx;
    }
}

void deallocSpaceForAuth(VirtualHeap *VH, int ndx)
{
    if(ndx>=0 && ndx<MAX_AUTH)
    {
        (*VH)->Author[ndx].link = (*VH)->author_avail;
        (*VH)->author_avail = ndx;
    }
}



void addBook(CLIST *C, VirtualHeap *VH, Book book)
{
    if(isFull(*VH))
    {
        fullListMsg();
    }//put an else if clause to search if book exists
    else if(checkBookExistence(C, VH, book))
    {
        int ndx = searchBook(C, VH, book.bookID);
        printf("\n\tIdenfication Number %d already existed!\n", book.bookID); //idk what I'm doing in this part
        printBookDetails((*VH)->Books[ndx].book);
    }
    else
    {
        int ndx = allocSpaceForBooks(VH);
        if(ndx!=-1)
        {
            (*VH)->Books[ndx].book = book;
            (*VH)->Books[ndx].link = -1;
            if(isEmpty(*C))
            {
                *C = ndx;
            }
            else
            {
                int x;
                for(x=*C; (*VH)->Books[x].link!=(*VH)->book_avail && (strcmp(book.title,(*VH)->Books[x].book.title) <= 0); x=(*VH)->Books[x].link){}
            
                (*VH)->Books[ndx].link = x;
                if(x==*C)
                {
                    *C = ndx;
                }
                else
                {
                    int y;
                    for(y=*C; (*VH)->Books[y].link!=x; y = (*VH)->Books[y].link){}
                    (*VH)->Books[y].link = ndx;
                }
            }
        }
        else
        {
            fullListMsg();
        }

        if(!(checkAuthorExistence(C, VH, book.author)))
        {
            addAuthor(C, VH, book.author);
        }
    }
}

SEX printSex(Sex sx)
{
    switch(sx)
    {
        case M: return "Male"; break;
        case F: return "Female"; break;
        default: return "XXXXX"; break;
    }
}

GENRE printGenre(Genre genre)
{
    switch(genre)
    {
        case FANTASY: return "Fantasy"; break;
        case MYSTERY: return "Mystery"; break;
        case SELF_HELP: return "Self-Help"; break;
        case ROMANCE: return "Romance"; break;
        case SCIFI: return "Science Fiction"; break;

        default: return "XXXXX"; break;
    }
}

BOOKSTATUS printBookStat(BookStatus bookStatus)
{
    switch(bookStatus)
    {
        case BORROWED: return "Borrowed"; break;
        case AVAILABLE: return "Available"; break;

        default: return "XXXXX"; break;
    }
}

int searchBook(CLIST *C, VirtualHeap *VH, int bookID)
{
    int x;
    for(x=*C; x!=-1 && (*VH)->Books[x].book.bookID!=bookID; x=(*VH)->Books[x].link){}

    return (x!=-1 && (*VH)->Books[x].book.bookID==bookID) ? x : -1;
}

bool checkBookExistence(CLIST *C, VirtualHeap *VH, Book book)
{
    int x;
    for(x=*C; x!=-1 &&(*VH)->Books[x].book.bookID!=book.bookID; x=(*VH)->Books[x].link){}

    return (x!=-1 && (*VH)->Books[x].book.bookID==book.bookID) ? true : false;
}

void deleteBookById(CLIST *C, VirtualHeap *VH, int bookID)
{
    if(isEmpty(*C))
    {
        emptyListMsg();
    }
    else
    {
        int ndx = searchBook(C, VH, bookID);
        if(ndx!=-1)
        {
            int x;
            for(x=*C; (*VH)->Books[x].link!=ndx; x=(*VH)->Books[x].link){}

            (*VH)->Books[x].link = (*VH)->Books[ndx].link;

            if(ndx==*C)
            {
                *C = (*VH)->Books[ndx].link;
            }

            deallocSpaceForBooks(VH, ndx);
        }
        else
        {
            printf("\n\tBook doesn't exists!\n\n");
        }
    }
}

void addAuthor(CLIST *C, VirtualHeap *VH, Author auth)
{
    if(checkAuthorExistence(C, VH, auth))
    {
        printf("\n\tAuthor already existed!\n\n");
        //print author details here
    }
    else
    {
        int ndx = allocSpaceForAuth(VH);
        if(ndx!=-1)
        {
            (*VH)->Author[ndx].author = auth;
            (*VH)->Author[ndx].link = -1;

            if(isEmpty(*C))
            {
                *C = ndx;
            }
            else
            {
                int x;
                for(x=*C; (*VH)->Author[x].link!=-1; x = (*VH)->Author[x].link){}

                (*VH)->Author[x].link = ndx;
            }
        }
    }
}

int searchAuthor(CLIST *C, VirtualHeap *VH, int authID)
{
    int x;
    for(x=*C; x!=-1 && (*VH)->Author[x].author.authorID!=authID; x=(*VH)->Author[x].link){}

    return (x!=-1 && (*VH)->Author[x].author.authorID==authID) ? x : -1;
}

bool checkAuthorExistence(CLIST *C, VirtualHeap *VH, Author auth)
{
    int x;
    for(x=*C; x!=-1 && (*VH)->Author[x].author.authorID!=auth.authorID; x=(*VH)->Author[x].link){}

    return (x!=-1 && (*VH)->Author[x].author.authorID==auth.authorID) ? true : false;
}

void deleteAuthorById(CLIST *C, VirtualHeap *VH, int authID)
{
    int ndx = searchAuthor(C, VH, authID);
    if(ndx!=-1)
    {
        if(ndx==*C)
        {
            *C = (*VH)->Author[ndx].link;
        }
        else
        {
            int x;
            for(x=*C; (*VH)->Author[x].link!=ndx; x = (*VH)->Author[x].link){}

            (*VH)->Author[x].link = (*VH)->Author[ndx].link;

            deallocSpaceForAuth(VH, ndx);
        }
    }
    else
    {
        printf("\n\tAuthor doesn't exists!\n\n");
    }
}

void printBookDetails(Book book)
{
    printf("\n\n\t=========================\n");
    printf("\tBook ID: %d\n", book.bookID);
    printf("\tTitle: %s\n", book.title);
    printf("\tAuthor: %s %c. %s\n", book.author.FN, book.author.MI, book.author.LN);
    printf("\tYear Published: %d\n", book.year);
    printf("\tNumber of Pages: %d\n", book.no_of_pages);
    printf("\tBook Status: %s\n", printBookStat(book.bookStatus));
    printf("\tGenre: %s\n\n", printGenre(book.genre));
}

void printAuthDetails(Author auth)
{
    printf("\n\n\t=========================\n");
    printf("\tAuthor ID: %d\n", auth.authorID);
    printf("\tName: %s %c. %s\n", auth.FN, auth.MI, auth.LN);
    printf("\tSex: %s\n\n", printSex(auth.sx));
}

void printAllBooks(CLIST *C, VirtualHeap *VH)
{
    if(isEmpty(*C))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\t\tLIST OF BOOKS\n");
        printf("==============================================================================================\n");
        printf("%-15s %-15s %-25s %-15s %-15s\n", "BOOK ID", "TITLE", "AUTHOR", "YEAR PUBLISHED", "GENRE");
        printf("-----------------------------------------------------------------------------------------------\n");

        int x;
        for(x=*C; x!=-1; x=(*VH)->Books[x].link)
        {
            printf("%-15d %-15s %s %c. %-15s %-15d %-15s\n", (*VH)->Books[x].book.bookID, (*VH)->Books[x].book.title, (*VH)->Books[x].book.author.FN, (*VH)->Books[x].book.author.MI, (*VH)->Books[x].book.author.LN, (*VH)->Books[x].book.year, printGenre((*VH)->Books[x].book.genre));
        }
        printf("\n\n");
    }
}

void printAllAuthors(CLIST *C, VirtualHeap *VH)
{
    if(isEmpty(*C))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\t\tLIST OF AUTHORS\n");
        printf("===========================================================\n");
        printf("%-15s %-15s %-15s\n", "ID", "NAME", "SEX");
        printf("-----------------------------------------------------------\n");

        int x;
        for(x=*C; x!=-1; x=(*VH)->Author[x].link)
        {
            printf("%-15d %s %c. %-15s %-15s\n", (*VH)->Author[x].author.authorID, (*VH)->Author[x].author.FN, (*VH)->Author[x].author.MI, (*VH)->Author[x].author.LN, printSex((*VH)->Author[x].author.sx));
        }

        printf("\n\n");
    }
}

void filterBooksByAuth(CLIST *C, VirtualHeap *VH, int authID)
{
    if(isEmpty(*C))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\n*********************************************\n");

        int authNdx = searchAuthor(C, VH, authID);
        if(authNdx!=-1)
        {
            printf("Filter books by Author ID: %d\n\n", authID);
            //will add the author name here instead using authNdx

            printf("================================================\n");
            printf("%-15s %-15s %-15s %-15s %-15s\n", "BOOK ID", "TITLE", "AUTHOR", "YEAR PUBLISHED", "GENRE");
            printf("-------------------------------------------------\n");

            int x;
            for(x=*C; x!=-1; x=(*VH)->Books[x].link)
            {
                if((*VH)->Books[x].book.author.authorID==authID)
                {
                    printf("%-15d %-15s %s %c. %-15s %-15d %-15s\n", (*VH)->Books[x].book.bookID, (*VH)->Books[x].book.title, (*VH)->Books[x].book.author.FN, (*VH)->Books[x].book.author.MI, (*VH)->Books[x].book.author.LN, (*VH)->Books[x].book.year, printGenre((*VH)->Books[x].book.genre));
                }
            }

            printf("\n\n");
        }
    }
}

void filterBooksByGenre(CLIST *C, VirtualHeap *VH, Genre genre)
{
    if(isEmpty(*C))
    {
        emptyListMsg();
    }
    else
    {
        printf("\n\n*************************************************\n");

        printf("Filter books by Genre: %s\n\n", printGenre(genre));
        printf("=====================================================\n");
        
        printf("%-15s %-15s %-15s %-15s %-15s\n", "BOOK ID", "TITLE", "AUTHOR", "YEAR PUBLISHED", "GENRE");
        printf("-------------------------------------------------\n");

        int x;
        for(x=*C; x!=-1; x=(*VH)->Books[x].link)
        {
            if((*VH)->Books[x].book.genre==genre)
            {
                printf("%-15d %-15s %s %c. %-15s %-15d %-15s\n", (*VH)->Books[x].book.bookID, (*VH)->Books[x].book.title, (*VH)->Books[x].book.author.FN, (*VH)->Books[x].book.author.MI, (*VH)->Books[x].book.author.LN, (*VH)->Books[x].book.year, printGenre((*VH)->Books[x].book.genre));
            }
        }

        printf("\n\n");
    }
}

void populateBooks(CLIST *C, VirtualHeap *VH)
{
    Book book1 = {1, "Testing Book", {"Shannen", "Nazareno", 'T', 19103991, F}, 2023, 143, AVAILABLE, SCIFI};
    Book book2 = {2, "Apple", {"Shannen", "Nazareno", 'T', 19103991, F}, 2001, 146, BORROWED, FANTASY};
    Book book3 = {19, "Sugar Rush", {"Butter", "Cup", 'S', 899, F}, 2022, 1000, AVAILABLE, MYSTERY};
    addBook(C, VH, book1);
    // addBook(C, VH, book2);
    // addBook(C, VH, book3);
}

int main()
{
    CLIST Book;
    CLIST Auth;

    Library Lib;

    VirtualHeap book_VH = &Lib;
    VirtualHeap auth_VH = &Lib;

    initBookVirtualHeap(&book_VH);
    initAuthVirtualHeap(&auth_VH);

    initCList(&Book);
    initCList(&Auth);

    populateBooks(&Book, &book_VH);

    printAllBooks(&Book, &book_VH);
    printAllAuthors(&Auth, &auth_VH);
    return 0;
}