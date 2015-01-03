/**********************************************************************
 * Name Marcel Champagne                                              *
 * Box(s): 3245                                                       *
 * Assignment name:  Supplemental Problem 13, Fall 2014               *
 * Assignment for Extra Credit                                        *
 **********************************************************************/

/* *********************************************************************
 * Academic honesty certification:                                     *
 *   Written/online sources used:                                      *
 *      None                                                           *
 *                                                                     *
 *   Help obtained                                                     *
 *      None
 *   My/our signature(s) below confirms that the above list of sources *
 *     is complete AND that I have not talked to anyone else           *
 *     about the solution to this problem                              *
 *                                                                     *
 *   Signature:                                                        *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A program that takes the name of a file and reads through the file to
// determine the rank of Powershiek county regarding amount of population
// that is African American


#define maxNameLen 50

struct county {
  char name [maxNameLen];
  int blackPopulation;
  struct county * next;
};

// Pre-conditions: Takes the name of a file, and a pointer to a pointer to a
//                 county struct
// Post-conditions: Goes through the file, reading the county name and the
//                  the 7 columns of data of different popultion demographics
//                  and creates  a linked list of counties containing their
//                  black population.
void readFile(FILE * file, struct county ** populations){
  char name [maxNameLen];
  char n1[maxNameLen],n2[maxNameLen],n3[maxNameLen],
       n4[maxNameLen],n5[maxNameLen],n6[maxNameLen],n7[maxNameLen];
  while(1){
    if( fscanf(file,"%s",name) == EOF)
      break;
    while(getc(file) != '\n');
    if( fscanf(file,"%s %s %s %s %s %s %s",n1,n2,n3,n4,n5,n6,n7) == EOF)
      break;
    int blackPop = atoi(n3);
    if(strlen(name) != 0){
      struct county * newCounty = (struct county*)malloc(sizeof(struct county));

      strcpy(newCounty->name,name);
      newCounty->blackPopulation = blackPop;
      newCounty->next = *populations;
      *populations = newCounty;
    }
    
  }

}


// Pre-conditions: Takes a pointer to the head of a linked list of counties
//                 and a county name
// Post-conditions: Finds the black population of the given county and the
//                  ranking compared to Iowa's other counties.
void rankAfricanAmerican(struct county * populations,char name[]){
  int rank = 1;
  int blackPop;
  struct county * temp = populations;
  while(temp != NULL){
    if(!strcmp(name,temp->name)){
      blackPop = temp->blackPopulation;
      break;
    }
    temp = temp->next;
  }
  temp = populations;
  while(temp != NULL){
    if(temp->blackPopulation > blackPop)
      rank += 1;
    temp = temp->next;
  }
  printf("\n%s has a African American population of %d.\n",name,blackPop);
  printf("%s's rank is %d out of all the counties in Iowa. \n\n",name,rank);
}

int main(){
  char filename[81];
  FILE * fp = NULL;
  struct county * populations = NULL;
  while(fp == NULL){
    printf("\nEnter the population data file for the program to read: \n");
    scanf("%s",filename);
    while(getchar() != '\n');
    fp = fopen(filename, "r");
    if(fp == NULL){
      printf("Invalid file name.\n");
    }
  }
  printf("\nThis program determines the ranking of Poweshiek County in Iowa\n");
  printf("regarding the total number of Black/African Americans.\n\n");
  readFile(fp,&populations);
  fclose(fp);
  rankAfricanAmerican(populations,"Poweshiek");
}
