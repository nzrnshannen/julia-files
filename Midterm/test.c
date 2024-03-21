#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef int SET[MAX];

void display(SET A, int count);
SET *Union(SET A, SET B);
SET *Intersection(SET A, SET B);
SET *Difference(SET A, SET B);
bool isSubset(SET A, SET B);

int main(){
    SET A = {1, 3, 5, 7, 8};
    SET B = {1, 2, 3, 6, 7};
    
    int countA = sizeof(A)/sizeof(A[0]);
    int countB = sizeof(B)/sizeof(B[0]);
    
    printf("\nsize a = %d\n", countA);
    display(A, countA);
    display(B, countB);

    printf("\nUnion: ");
    SET *C = Union(A, B);
    int countC = sizeof(C)/sizeof((C)[0]);
    display(*C, countC);

    printf("test = %d\n", *(C)[1]);
    free(C);
    
    return 0;
}

void display(SET A, int count){
    int x;
    for(x = 0; x < count; x++){
        printf("%d ", A[x]);
    }
    printf("\n");
}

SET *Union(SET A, SET B){
    int x, y, z = 0;
    SET *C = (SET*)malloc(sizeof(SET));
    
    if(C != NULL){
        int countA, countB;
        countA = sizeof(*A)/sizeof(A[0]);
        countB = sizeof(*B)/sizeof(B[0]);
        
        for(x = 0, y = 0; x < countA && y < countB;){
            if(A[x] < B[y])
            {
                (*C)[z] = A[x];
                x++;
            } 
            else if(A[x] > B[y])
            {
                (*C)[z] = B[y];
                y++;
            }
            else
            {
                (*C)[z] = A[x];
                x++, y++;
            }
            z++;
        }

        if(x < countA){
            for(; x < countA; x++){
                (*C)[z] = A[x];
                z++;
            }
        }
        if(y < countB){
            for(; y < countB; y++){
                (*C)[z] = B[y];
                z++;
            }
        }
    }
    return C;
}

SET *Intersection(SET A, SET B){
    SET *C = (SET*)malloc(sizeof(int));
    int x, y, z = 0;
    
    if(C != NULL){
        int countA, countB;
        countA = sizeof(*A)/sizeof(A[0]);
        countB = sizeof(*B)/sizeof(B[0]);
        
        for(x = 0, y = 0; x < countA && y < countB;){
            if(A[x] < B[y]){
                x++;
            } else if(A[x] > B[y]){
                y++;
            } else{
                (*C)[z] = A[x];
                x++, y++, z++;
            }
        }
    }
    return C;
}

SET *Difference(SET A, SET B){
    int x, y, z = 0;
    SET *C = (SET*)malloc(sizeof(int));
    
    if(C != NULL){
        int countA, countB;
        countA = sizeof(*A)/sizeof(A[0]);
        countB = sizeof(*B)/sizeof(B[0]);
        
        for(x = 0, y = 0; x < countA && y < countB;){
            if(A[x] < B[y]){
                (*C)[z] = A[x];
                x++, z++;
            } else if(A[x] > B[y]){
                y++;
            } else{
                x++, y++;
            }
        }
        if(x < countA){
            for(; x < countA; x++){
                (*C)[z] = A[x];
                z++;
            }
        }
    }
    return C;
}

bool isSubset(SET A, SET B){
    int x, y;
    bool isSub;
    int countA, countB;
    countA = sizeof(*A)/sizeof(A[0]);
    countB = sizeof(*B)/sizeof(B[0]);
    
    isSub = (countA <= countB) ? true : false;
    
    for(x = 0; isSub == false && x < countA; x++){
        for(y = 0; x < countB && A[x] != B[y]; y++){}
        if(A[x] != B[y]){
            isSub = false;
        }
    }
    return isSub;
}