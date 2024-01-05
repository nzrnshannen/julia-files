/*------------------------------------------------------------------------------------

Name: Shannen T. Nazareno
Date: 01/04/2024
Program: Library Transactions using ADT List (Array Implementation v3) UNFINISHED

- transactions part not yet done
- borrowers part not yet done

Note: this is a messy program as I only focus on implementing v3 (w/ expand and shrink size)

Aside from speedrunning this program, 

Library transactions may not work well as expected esp the borrow-return process.
It's better to use file handling in here so that database will be stored:
                    -> such as borrowers account
                    -> transactions
                    -> pending request and return

Functions to be implemented:
- shrinkBookSize

---------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define BOOK_BORROW_LIMIT 3
#define MAX_BOOKS 2 //for testing purposes
#define STUDENT_CAPACITY 2 //for testing purposes
#define TRANSACTION_CAP 5
typedef char GENRE;
typedef char AVAILABILITY;
typedef char AUTHOR;
typedef char SEX;
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
    Transactions *transactions;
    Book borrowedBooks[BOOK_BORROW_LIMIT];
    int borrowCount;
};

struct Transactions{
    Borrower *Borrower;
    Date issueDate;
    Date returnDate;
    Book borrowedBook;
};
typedef struct{
    Book *books;
    Transactions *transactions;
    Borrower *borrowers;
    int borrowerCount;
    int bookCount;
}Library;


void initializeLIB(Library *LIB);

//books
void populateWithBooks(Library *LIB);
void printBooks(Library LIB);
AVAILABILITY* bookAvailability(AVAILABILITY avail);
GENRE* bookGenre(GENRE Genre);
void printBookDetails(Book book);
bool checkIfBookExists(Library *LIB, int bookId);
void deleteBook(Library *LIB, int bookId);

//borrower
void populateWithBorrowers(Library *LIB);
void addBorrower(Library *LIB, Borrower brwer);
void removeBorrower(Library *LIB, Borrower removeBor);
void printBorrowerDetails(Borrower Borrower);
void printBorrowers(Library *LIB);
bool checkIfBorrowerExists(Library *LIB, int stud_id);
SEX* borrowerSex(Sex sex);
bool requestBorrow(Library *LIB, Book book);
bool requestReturn(Library *LIB, Book book);

void shrinkBorrowerSize(Library *LIB, int init_cap);
//transactions
bool acceptReqBorrower(Library *LIB, Borrower b);
bool acceptReqReturn(Library* LIB, Borrower b);

//filter: books
void filterByGenre(Library *LIB, GENRE Genre);
void filterByAvailability(Library *LIB, AVAILABILITY Avail);
void filterByAuthor(Library *LIB, Author author);

void clearList(Library *LIB);

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

void addBorrower(Library *LIB, Borrower brwer)
{
    if(checkIfBorrowerExists(LIB, brwer.stud.id))
    {
        printf("\n\tBorrower already exists!\n");
        printBorrowerDetails(brwer);
    }
    else
    {
        if(LIB->borrowerCount==STUDENT_CAPACITY)
        {
            printf("\n\tCapacity full! Reallocating...\n");
            int init_cap = LIB->borrowerCount;
            LIB->borrowers = (Borrower*)realloc(LIB->borrowers, sizeof(Borrower) * (init_cap + 1));
            if(LIB->borrowers==NULL)
            {
                printf("\nMemory allocation failure!\n");
                exit(1);
            }
        }

        LIB->borrowers[LIB->borrowerCount++] = brwer;

        printf("\n\t>> Successfully added student %d.<<\n\n", brwer.stud.id);
    }
}

void printBorrowerDetails(Borrower Borrower)
{
    int x;
    printf("\n===========================\n");
    printf("ID: %d\n", Borrower.stud.id);
    printf("Name: %s %c. %s\n", Borrower.stud.FN, Borrower.stud.MI, Borrower.stud.LN);
    printf("Sex: %s\n", borrowerSex(Borrower.stud.sex));
    printf("Year: %d\n", Borrower.stud.year);
    printf("\n\tBorrowed books: ");
    for(x=0; x<Borrower.borrowCount; x++)
    {
        printBookDetails(Borrower.borrowedBooks[x]);
    }
    if(Borrower.borrowCount==0)
    {
        printf("\n\tEMPTY\n");
    }

    printf("\n=============================\n\n");
}

SEX* borrowerSex(Sex sex)
{
    switch(sex)
    {
        case F: return "Female"; break;
        case M: return "Male"; break;
        default: return "XXXXX"; break;
    }
}

void printBorrowers(Library *LIB)
{
    int x;
    for(x=0; x<LIB->borrowerCount; x++)
    {
        printf("\n=========================================\n");
        printf("\tID: %d\n", LIB->borrowers[x].stud.id);
        printf("Name: %s %c. %s\n", LIB->borrowers[x].stud.FN, LIB->borrowers[x].stud.MI, LIB->borrowers[x].stud.LN);
        printf("Sex: %s\n", borrowerSex(LIB->borrowers[x].stud.sex));
        printf("Year: %d\n----------------------------------------\n\n", LIB->borrowers[x].stud.year);
    }
}

bool checkIfBorrowerExists(Library *LIB, int stud_id)
{
    int x;
    for(x=0; x<LIB->borrowerCount && LIB->borrowers[x].stud.id!=stud_id; x++){}
    
    return (LIB->borrowers[x].stud.id==stud_id) ? true : false;
}

void populateWithBorrowers(Library *LIB)
{
    Student s1 = {19103991, "Butter", "Cup", 'N', F, 2};
    Student s2 = {123456, "Yollie", "Cup", 'T', F, 1};
    Student s3 = {5101520, "Cream", "Cup", 'S', F, 1};
    Student s4 = {9999, "Sky", "Lue", 'B', F, 2};

    Borrower b1;
    Borrower b2;
    Borrower b3;
    Borrower b4;

    b1.stud = s1;
    b1.borrowCount=0;
    b2.stud = s2;
    b2.borrowCount=0;
    b3.stud = s3;
    b3.borrowCount = 0;
    b4.stud = s4;
    b4.borrowCount = 0;
    addBorrower(LIB, b1);
    addBorrower(LIB, b2);
    addBorrower(LIB, b3);
    addBorrower(LIB, b4);

    removeBorrower(LIB, b1);
}

void removeBorrower(Library *LIB, Borrower removeBor)
{
    if(checkIfBorrowerExists(LIB, removeBor.stud.id))
    {  
        int x, init_cap;
        init_cap = removeBor.borrowCount;
        for(x=0; x < LIB->borrowerCount&&LIB->borrowers[x].stud.id!=removeBor.stud.id; x++){}

        for(; x<LIB->borrowerCount-1; x++)
        {
            LIB->borrowers[x] = LIB->borrowers[x+1];
        }
        LIB->borrowerCount--;
        shrinkBorrowerSize(LIB, init_cap);

        printf("\n\tSuccessfully removed student %d.\n\n", removeBor.stud.id);
    }
    else
    {
        printf("\n\tStudent %d doesn't exists!\n", removeBor.stud.id);
    }
}

void shrinkBorrowerSize(Library *LIB, int init_cap)
{
    if(init_cap > STUDENT_CAPACITY && init_cap > LIB->borrowerCount)
    {
        printf("\n********\nShrinking the size...\n*******\n\n");
        LIB->borrowers= (Borrower*)realloc(LIB->borrowers, sizeof(Borrower) * LIB->borrowerCount);
        if(LIB->borrowers ==NULL)
        {
            printf("\nMemory allocation failure!\n");
            exit(1);
        }
    }
}

void clearList(Library *LIB)
{
    free(LIB->books);
    free(LIB->borrowers);

    
    LIB->books = NULL;
    LIB->borrowers = NULL;
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

    LIB->borrowerCount=0;
    LIB->borrowers = (Borrower*)malloc(sizeof(Borrower) * STUDENT_CAPACITY);
    if(LIB->borrowers==NULL)
    {
        printf("\nMemory allocation failure.\n\n");
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

    populateWithBorrowers(&testLib);
    printBorrowers(&testLib);
    
    printf("Borrower count = %d\n", testLib.borrowerCount);
    clearList(&testLib);
    return 0;
}
