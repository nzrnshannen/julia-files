#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 
typedef enum {VACANT, OCCUPIED, DAMAGED} state;
 
typedef struct{
    char idNumber[9];
    char fName[32];
    char lName[32];
}studentRecord;
 
typedef struct{
    studentRecord currentUser;
    char lastUser[9]; //ID Number of the last student who used the PC.
    int pcNumber;
    state pcState;
}pcRecord;
 
typedef struct{
    pcRecord PC[30];
    int count;    //refers to the total number of desktops
    int occupied; //refers to the number of occupied desktops
}pcList;

/*Codes have already been provided for these functions*/
char* displayState(state S); //given
void displayPCRecords(pcRecord PCList[]); //partial code
void displayPCList(pcList desktops); //done

/*Problem 1 DONE*/
void initPCList(pcList* desktops, int numPCs); //done
void populatePCList(pcList* desktops); //done

/*Problem 2*/
void usePC(pcList* desktops, int pcNumber, studentRecord SR); //done

/*Problem 3*/
void vacatePC(pcList* desktops, int pcNumber); //done

/*Problem 4*/
pcList genPCListOccupied(pcList desktops); //needs revision

/*Problem 5*/
void reportDamagedPC(pcList* desktops, studentRecord SR); //done
pcRecord* removeDamagedPCs(pcList* desktops);

int main(void) {
    pcList LB445;
    
    /*Problem 1*/
    //DONE: call initPCList() passing LB445 as the parameter. Initialize the list to have only 5 computers.

    printf("\nProblem 1:\n");
    initPCList(&LB445, 5);

    fflush(stdin);
    //DONE: call populatePCList() passing LB445 as the parameter.
    populatePCList(&LB445);

    //DONE: call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    printf("\n");
    /*Problem 2*/

    fflush(stdin);
    printf("\nProblem 2:\n");
    //DONE: Initialize a studentRecord stud1 with the values 14101941, Cris, Militante.
    studentRecord stud1 = {"14101941", "Cris", "Militante"};

    //DONE: Call usePC() passing LB445, pcNumber 8, and stud1 as the parameters. This is to check if your code works for a pcNumber that doesn't exist.
    usePC(&LB445, 8, stud1);   

    //DONE: Call usePC() passing LB445, pcNumber 3, and stud1 as the parameters.
    usePC(&LB445, 3, stud1);

    fflush(stdin);
    //DONE: call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    printf("\nTESTING\n");
    displayPCList(LB445);

    printf("\nProblem 3:\n");
    /*Problem 3*/
    //DONE: Call vacatePC() passing LB445 and pcNumber 3 as the parameter.
    vacatePC(&LB445, 3);

    //DONE: Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    //DONE: Initialize a studentRecord stud2 with the values 14101943, Gabby, Pineda.
    studentRecord stud2 = {"14101943", "Gabby", "Pineda"};

    //DONE: Call usePC() passing LB445, pcNumber 3, and stud2 as the parameters.
    usePC(&LB445, 3, stud2);

    //DONE: Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    //DONE: Initialize a studentRecord stud3 with the values 14101945, Patty, Woo.
    studentRecord stud3 = {"14101945", "Patty", "Woo"};

    //DONE: Call usePC() passing LB445, pcNumber 3, and stud3 as the parameters.
    usePC(&LB445, 3, stud3);

    //DONE: Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    
    printf("\nProblem 4:\n");
    /*Problem 4*/
    //? DONE: Initialize a new pcList occLB445 using genPCListOccupied().
    pcList occLB445 = genPCListOccupied(LB445);
    //DONE: Call displayPCList() passing LB445 as the parameter.
    displayPCList(occLB445);

    displayPCList(LB445);
   
    /*Problem 5*/

    printf("\nProblem 5:\n");
    //DONE: Call reportDamagedPC() passing LB445, and stud3 as the parameters.
    reportDamagedPC(&LB445, stud3);

    //DONE: Call reportDamagedPC() passing LB445, and stud3 as the parameters.
    reportDamagedPC(&LB445, stud3);

    //DONE: Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    //? DONE: Initialize a new array of pcRecords using removeDamagedPCs().
    pcRecord* pcRecords = removeDamagedPCs(&LB445);

    //DONE: Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    //DONE: Call displayPCRecords() passing damagedPCs as the parameter.
    displayPCRecords(pcRecords);

   
    return 0;
}

/*Code for function displayState() has already been provided*/
char* displayState(state S)
{
    char* stateDescription = NULL;
    char buffer[64];
    switch(S){
        case 0:
            strcpy(buffer, "VACANT");
            break;
        case 1:
            strcpy(buffer, "OCCUPIED");
            break;
        case 2:
            strcpy(buffer, "DAMAGED");
            break;
        default:
            strcpy(buffer, "Error Occured");
    }
   
    stateDescription = (char*) malloc (sizeof(strlen(buffer) + 1));
    if(stateDescription != NULL){
        strcpy(stateDescription, buffer);
    }
    return stateDescription;
}

/* Write the code for the function initPCList(). This function will receive a pcList,
   and the inital number of PCs. The function will initialize the arrayList of desktops to have its
   proper count and occupied values based on the parameters.
 */
void initPCList(pcList* desktops, int numPCs)
{
    desktops->count =  numPCs;
    desktops->occupied = 0;
}
 
/* Write the code for the function populatePCList(). This function will receive a pcList. The function
   will populate the pcList with default values for each PC. The default studentRecord will contain strings
   containing "XXX" for both names, and "XXXXXXXX" for the idNumber. Initialize the other structure elements
   with values that make sense. CLUE: Look at the structure of the pcRecord and think of the values that should
   be populated to those fields when a PC is initially empty.
 */
void populatePCList(pcList* desktops) 
{

    fflush(stdin);
    pcRecord defaultVal = {{"XXXXXXXX", "XXXXXXXX", "XXXXXXXX"}, "XXXXXXXX", .pcState = VACANT};

    int x;
    for(x=0; x<desktops->count; x++)
    {
        desktops->PC[x] = defaultVal;
        desktops->PC[x].pcNumber = x;
    }

    // int x;
    // for(x=0; x<desktops->count; x++)
    // {
    //     strcpy(desktops->PC[x].currentUser.fName, "XXX");
    //     strcpy(desktops->PC[x].currentUser.lName, "XXX");
    //     strcpy(desktops->PC[x].currentUser.idNumber, "XXXXXXX");
    //     strcpy(desktops->PC[x].lastUser, "XXXXXXX");
    //     desktops->PC[x].pcNumber = x;
    //     desktops->PC[x].pcState = VACANT;
    // }
}

/* Code for the function displayPCList() is partially given.*/
void displayPCList(pcList desktops)
{
    int x;
    for(x=0; x<desktops.count; x++){
        printf("PC[%d]\nState: %s\nCurrent User: %s, \nLast User: %s\n\n", desktops.PC[x].pcNumber, displayState(desktops.PC[x].pcState), desktops.PC[x].currentUser.idNumber, desktops.PC[x].lastUser);
    }

    printf("Occupancy Rate: %d/%d\n\n", desktops.occupied, desktops.count);
}
 
/* Write the code for the function usePC(). The function will receive a pcList, a pcNumber, and a studentRecord.
   The function will simulate the process of a student who wants to use the given pcNumber. The function will check
   for the following:
    1) If the pcNumber is a valid pcNumber (meaning, if there are only 5 PCs, only pcNumber 0-4 are valid.
    2) If there are still PCs that are unnoccupied.
    3) If the pcNumber that the student has selected is VACANT.
        If it is, then assign that PC to the student by setting the student's records in the pcList.
        If it isn't, then look for the nearest available PC that can be used (forward search).
        
 */
void usePC(pcList* desktops, int pcNumber, studentRecord SR)
{

    // if(pcNumber < desktops->count && pcNumber >= 0 &&  desktops->occupied < desktops->count)
    // {
    //     if(desktops->PC[pcNumber].pcState==VACANT)
    //     {
    //         desktops->PC[pcNumber].currentUser = SR;
    //         desktops->PC[pcNumber].pcState = OCCUPIED;
    //         desktops->occupied++;
    //     }
    //     else
    //     {
    //         int x;
    //         for(x=pcNumber; desktops->PC[x].pcState!=VACANT; x = (x+1) % desktops->count){}
    //         desktops->PC[x].currentUser = SR;
    //         desktops->PC[x].pcState = OCCUPIED;
    //         desktops->occupied++;
    //     }
    // }
    

    //2nd ver
    if(pcNumber < desktops->count && pcNumber >= 0 && desktops->occupied < desktops->count)
    {
        int x;
        if(desktops->PC[pcNumber].pcState == VACANT)
        {
            x = pcNumber;
        }
        else
        {
            for(x=pcNumber + 1; desktops->PC[x].pcState!=VACANT; x=(x+1) % desktops->count){}
        }

        desktops->PC[x].currentUser = SR;
        desktops->PC[x].pcState =  OCCUPIED;
        desktops->occupied++;

        // printf("\ntesting number of occupied: %d\n\n", desktops->occupied);
        // printf("\n\ttest 4th pc: %s\n\n",  displayState(desktops->PC[3].pcState));
        // printf("\ntesting next pc: %s\n\n", displayState(desktops->PC[x+1].pcState));
    }
}


/* Write the code for the function vacatePC(). The function will receive a pcList and a pcNumber as parameters.
   The function will remove the student student from the pasrsed pcNumber from the pcList, and revert the values
   to their defaults EXCEPT for the lastUser member. Update values where it makes sense.
 */
void vacatePC(pcList* desktops, int pcNumber)
{
    desktops->PC[pcNumber] = (pcRecord) {
        {"XXXXXXXX", "XXXXXXXX", "XXXXXXXX"},
        .pcState = VACANT};
    
    desktops->occupied--;
}

/* Write the code for the function reportDamagedPC(). This function will receive a pcList and a studentRecord.
   The function will go through the pcList and check if the pass studentRecord is currently using a PC. If they are,
   then update the state of the PC they are using as damaged, and assign them the next available PC from PC 0.
   CLUE: You are allowed to use functions that have already been coded.
 */
void reportDamagedPC(pcList* desktops, studentRecord SR)
{
    int x;
    for(x=0; x<desktops->count && (strcmp(SR.idNumber, desktops->PC[x].currentUser.idNumber))!=0; x++){}

    if(x<desktops->count)
    {
        desktops->PC[x].pcState = DAMAGED;


        usePC(desktops, x, SR);

        fflush(stdin);
    }
}

/* Write the code for the function genPCListOccupied(). The function will receive a pcList. The function will go
   through the passed pcList and return a new pcList containing only the OCCUPIED PCs. Do not remove the occupied
   PCs from the original list.
 */
pcList genPCListOccupied(pcList desktops)
{
    int x;
    pcList tempList;
    tempList.count = tempList.occupied = 0; 

    for(x=0; x<desktops.count; x++)
    {
        if(desktops.PC[x].pcState == OCCUPIED)
        {
            tempList.PC[tempList.count] = desktops.PC[x];
            tempList.PC[tempList.count].pcNumber = tempList.count;
            tempList.count++;
            tempList.occupied++;
        }
    }


    printf("\ntest prob 3 templist count: %d\n\n", tempList.count);
    return tempList;
}

/* Write the code for the function removeDamagedPCs(). The function will receive a pcList. The function will go
   through the given pcList and return an array of pcRecords that contain all the DAMAGED PCs from the pcList.
   Let the first index of the array of pcRecords containg a sentinel value containing "00000000", END, END, END,
   -1, VACANT. This function also deletes the damaged PCs from the original list.
 */
pcRecord* removeDamagedPCs(pcList* desktops)
{
    pcRecord sentinelVal = {{"00000000", "END", "END"}, "END", -1, VACANT};
    pcRecord damagedPCs[desktops->count];
    int x, y=0;

    damagedPCs[0] = sentinelVal;

    for(x=0; x<desktops->count; x++)
    {
        if(desktops->PC[x].pcState==DAMAGED)
        {
            damagedPCs[y] = desktops->PC[x];
            y++;

            int z;
            for(z=x; z<desktops->count-1; z++)
            {
                desktops->PC[z] = desktops->PC[z+1];
            }
        }
    }

    pcRecord *returnDamagedPCS = (pcRecord*)malloc(sizeof(pcRecord) * y);
    if(returnDamagedPCS!=NULL)
    {
        memcpy(returnDamagedPCS, damagedPCs, sizeof(pcRecord) * y);
    }

    return returnDamagedPCS;
}
 
/* Code for the function displayPCRecords() is partially given.*/
void displayPCRecords(pcRecord PCList[])
{
    int i;
    for(i=0; PCList[i].pcNumber<30; i++) //partial 
    {
        printf("PC[%d]\nState: %s\nCurrent User: %s, \nLast User: %s\n\n", PCList[i].pcNumber, displayState(PCList[i].pcState), PCList[i].currentUser.idNumber, PCList[i].lastUser);
    }
}