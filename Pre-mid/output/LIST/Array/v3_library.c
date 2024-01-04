/*------------------------------------------------------------------------

Name: Shannen T. Nazareno
Date: 01/04/2024
Program: Library Transactions using ADT List (Array Implementation v3) UNFINISHED

- transactions part not yet done
-------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define BOOK_BORROW_LIMIT 3
#define MAX_BOOKS 2 //for testing purposes

typedef char GENRE;
typedef char AVAILABILITY;
typedef char AUTHOR;

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
    BORROWED,
    AVAILABLE
}BookStatus;

typedef enum{
    FICTION = 1,
    NONFICTION,
    MYSTERY,
    SCIFI,
    FANTASY,
    ROMANCE,
    HORROR,
    HISTORICAL,
    BIOGRAPHY,
    SCIENCE,
    SELFHELP,
    TRAVEL,
    HUMOR,
    YOUNG_ADULT,
    DRAMA
}Genre;

typedef enum {NULLVAL =-1, M, F} Sex;

typedef struct{
    Month m;
    int day;
    int year;
}Date;

typedef struct{
    int authorId;
    char FN[30], LN[30];
    char MI;
}Author;

typedef struct{
    int id;
    char FN[30], LN[30];
    char MI;
    Sex sex;
    int year;
}Student;

typedef struct Borrower Borrower;
typedef struct Transactions Transactions;
typedef struct Book Book;


struct Book{
    int bookId;
    char title[100];
    Author author;
    int publicationYear;
    // Borrower borrower;
    BookStatus bookstat;
    Genre genre;
};

struct Borrower{
    Student stud;
    struct{
        Borrower *borrower;
        Date issuedate;
        Date returnDate;
        Book borrowedBook;
    }Transactions;

    Transactions *transactions;
    int borrowedBooks[BOOK_BORROW_LIMIT];
    int borrowCount;
};

typedef struct{
    Book *books;
    Transactions *transactions;
    Borrower *borrowers;
    int bookCount;
}Library;


void initializeLIB(Library *LIB);
void populateWithBooks(Library *LIB);
void printBooks(Library LIB);
AVAILABILITY* bookAvailability(AVAILABILITY avail);
GENRE* bookGenre(GENRE Genre);

void printBookDetails(Book book);
bool checkIfBookExists(Library *LIB, int bookId);
void deleteBook(Library *LIB, int bookId);

//filter
void filterByGenre(Library *LIB, GENRE Genre);
void filterByAvailability(Library *LIB, AVAILABILITY Avail);
void filterByAuthor(Library *LIB, Author author);


bool checkIfBookExists(Library *LIB, int bookId)
{
    int x;
    for(x=0; x<LIB->bookCount && LIB->books[x].bookId!=bookId; x++){}

    return (LIB->books[x].bookId==bookId) ? true : false;
}



void addBook(Library *LIB, Book book)
{
    if(checkIfBookExists(LIB, book.bookId))
    {
        printf("\n\tBook already exists!\n");
        printBookDetails(book);
    }
    else
    {  
        if(LIB->bookCount==MAX_BOOKS)
        {
            printf("\n\t--> Reached the maximum capacity of books. Resizing... <--\n");
            int INIT_CAPACITY = LIB->bookCount;
            LIB->books = (Book*)realloc(LIB->books, sizeof(Book) * (INIT_CAPACITY +1));
            if(LIB->books==NULL)
            {
                printf("\nMemory allocation failure!\n");
                exit(1);
            }
        }
        LIB->books[LIB->bookCount++] = book;
        printf("\n\tSuccessfully added book!\n\n");
    }
}

void printBookDetails(Book book)
{
    printf("\n\t===========================\n");
    printf("\tBook number: %d\n", book.bookId);
    printf("\tBook title: %s\n", book.title);
    printf("\tAuthor: %s %c. %s\n", book.author.FN, book.author.MI, book.author.LN);
    printf("\tGenre: %s\n", bookGenre(book.genre));
    printf("\tPublication Year: %d\n", book.publicationYear);
    //assuming that the book has only one copy in the library so I excluded the 2 statements below:
    // printf("Total Copies: %d\n", book.totalCopies);
    // printf("Available Copies: %d\n", book.availableCopies);
    printf("\tAvailability: %s\n", bookAvailability(book.bookstat));
}

GENRE* bookGenre(GENRE Genre)
{
    switch(Genre)
    {
        case FICTION: return "Fiction"; break;
        case NONFICTION: return "Non-Fiction"; break;
        case MYSTERY: return "Mystery/Thriller"; break;
        case SCIFI: return "Sci-Fi"; break;
        case FANTASY: return "Fantasy"; break;
        case ROMANCE: return "Romance"; break;
        case HORROR: return "Horror"; break;
        case HISTORICAL: return "Historical"; break;
        case BIOGRAPHY: return "Biography"; break;
        case SCIENCE: return "Science"; break;
        case SELFHELP: return "Self-Help"; break;
        case TRAVEL: return "Travel"; break;
        case HUMOR: return "Humor"; break;
        case YOUNG_ADULT: return "Young Adult"; break;
        case DRAMA: return "Drama"; break;

        default: return "XXXX"; break;
    }
}

AVAILABILITY* bookAvailability(AVAILABILITY avail)
{
    switch(avail)
    {
        case BORROWED: return "Borrowed"; break;
        case AVAILABLE: return "Available"; break;
        default: return "XXXXX"; break;
    }
}

void printBooks(Library LIB)
{
    int x;
    for(x=0; x<LIB.bookCount; x++)
    {
        printf("\n=========================================\n");
        printf("\tBook number: %d\n", LIB.books[x].bookId);
        printf("\nBook title: %s\n", LIB.books[x].title);
        printf("Author: %s %c. %s\n", LIB.books[x].author.FN, LIB.books[x].author.MI, LIB.books[x].author.LN);
        printf("Genre: %s\n", bookGenre(LIB.books[x].genre));
        printf("Publication Year: %d\n", LIB.books[x].publicationYear);
        printf("Availability: %s\n", bookAvailability(LIB.books[x].bookstat));
        printf("\n---\n");
    }
    printf("\n");
}

void deleteBook(Library *LIB, int bookId)
{
    if (!checkIfBookExists(LIB, bookId))
    {
        printf("\n\tBook doesn't exists!\n\n");
    }
    else
    {
        int x;
        for(x=0; x<LIB->bookCount && LIB->books[x].bookId!=bookId; x++){}

        int y;
        for(y=x; y<LIB->bookCount-1; y++)
        {
            LIB->books[y] = LIB->books[y+1];
        }
        LIB->bookCount--;

        printf("\n\tSuccessfully removed book.\n\n");
    }
}

void filterByGenre(Library *LIB, GENRE Genre)
{
    bool isTrue = false;
    printf("\n******************************************\n");
    printf("Filter by Genre: %s\n", bookGenre(Genre));
    int x;
    for(x=0; x<LIB->bookCount; x++)
    {
        if(((GENRE)LIB->books[x].genre) == Genre) //typecast
        {
            isTrue = true;
            printBookDetails(LIB->books[x]);
        }
    }

    if(!isTrue)
    {
        printf("\n\t = = No records found! = =\n");
    }
}

void filterByAuthor(Library *LIB, Author author)
{
    bool isTrue = false;
    printf("\n******************************************\n");
    printf("Filter by Author: %s %c. %s\n", author.FN, author.MI, author.LN);
    int x;
    for(x=0; x<LIB->bookCount; x++)
    {
        if(((strcmp(LIB->books[x].author.FN, author.FN)==0) && 
        (strcmp(LIB->books[x].author.LN, author.LN)==0)) || 
        (LIB->books[x].author.authorId==author.authorId))
        {
            isTrue = true;
            printBookDetails(LIB->books[x]);
        }
        printf("\n");
    }

    if(!isTrue)
    {
        printf("\n\t = = No records found! = =\n");
    }
}

void filterByAvailability(Library *LIB, AVAILABILITY avail)
{
    bool isTrue = false;
    printf("\n******************************************\n");
    printf("Filter by Book Status: %s\n", bookAvailability(avail));
    int x;
    for(x=0; x<LIB->bookCount; x++)
    {
        if(((AVAILABILITY)LIB->books[x].bookstat) == avail)
        {
            isTrue = true;
            printBookDetails(LIB->books[x]);
        }
    }

    if(!isTrue)
    {
        printf("\n\t = = No records found! = =\n");
    }

}

void populateWithBooks(Library *LIB)
{   
    // Borrower dummyVal = {
    //     .stud = {0, "XXXXX", "XXXXX", 'X', NULLVAL, 0}
    // };

    Author auth1 = {19103991, "Shannen", "Nazareno", 'T'};

    // Borrower borrower1;
    Book book1 = {1010, "Testing Book", auth1, 2024, AVAILABLE, FICTION};
    Book book2 = {1234, "Magic Wand", auth1, 2002, AVAILABLE, NONFICTION};

    Author auth2 = {12345, "Author Test FN", "Author Test LN", 'Z'};
    Book book3 = {9999, "Cry", auth2, 2004, BORROWED, SCIFI};

    addBook(LIB, book1);
    addBook(LIB, book2);
    addBook(LIB, book3);
    addBook(LIB, book1);

    // filterByAuthor(LIB, auth1);

}


void initializeLIB(Library *LIB)
{
    LIB->bookCount = 0;
    LIB->books = (Book*)malloc(sizeof(Book) * MAX_BOOKS);
    if(LIB->books==NULL)
    {
        printf("\n\nMemory allocation failure\n");
        exit(1);
    }
}

int main()
{
    Author auth = {12345, "Author Test FN", "Author Test LN", 'Z'};
    Library testLib;
    initializeLIB(&testLib);
    populateWithBooks(&testLib);
    printBooks(testLib);
    //deleteBook(&testLib, 1234);
    printBooks(testLib);
    filterByAuthor(&testLib, auth);
    filterByAvailability(&testLib, AVAILABLE);
    return 0;
}
