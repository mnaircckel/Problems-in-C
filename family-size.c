/**********************************************************************
 * Name Marcel Champagne                                              *
 * Box(s): 3245                                                       *
 * Assignment name:  Supplemental Problem 3, Fall 2014                *
 * Assignment for Monday, November 3rd                                *
 **********************************************************************/

/* *********************************************************************
 * Academic honesty certification:                                     *
 *   Written/online sources used:                                      *
 *      Stub from statement of the problem                             *
 *      Couple-2.c                                                     *
 *      www.lemoda.net/c/printf-left-justify                           *
 *                                                                     *
 *   Help obtained                                                     *
 *      None
 *   My/our signature(s) below confirms that the above list of sources *
 *     is complete AND that I have not talked to anyone else           *
 *     about the solution to this problem                              *
 *                                                                     *
 *   Signature:                                                        *
     *******************************************************************/


/***********************************************************************
 *  Program to tabulate the results of a simulation                    *
 *  in both a table and a histogram.                                   *
 *******************************************************************/

#include <stdio.h>
/* libraries for the random number generator */
#include <stdlib.h>
#include <time.h>
#include <math.h>


/* pre-conditions: famSize is an array that counts
  the number of occurances of family sizes determined in main,
  length is the max family size recorded and should be a postive number */
void printTable(int famSize[],int length){
  printf("family size counts\n");
  printf("# children: count\n");
  int i;
  // Prints a table listings family size and number of occurances
  for(i = 0; i<= length; i++){
    printf("%8d  : %5d\n",i,famSize[i]);
  }

}

/* pre-conditions: famSize is an array that counts
  the number of occurances of family sizes determined in main, 
  length is the max family size recorded and should be a postive number */
void printHistogram(int famSize[], int length, int heightOfHistogram){
  printf("Histogram of family sizes\n");
  printf("# couples\n");
  int i;
  int maxCouples = 0;

  // Determines the highest family size in the simulation
  for(i = 0; i <= length; i++){
    if(famSize[i] > maxCouples){
      maxCouples = famSize[i];
    } 
  }
  // Determines what to to decrease the #couples by each row
  double inc = (double)(maxCouples-1)/heightOfHistogram;
  int number;

  //prints the rows of the historgram
  for(i = 1; i <= heightOfHistogram; i++){
    number = (maxCouples-(inc*i))+.5;
    if(i == 1)
      number = maxCouples;
    printf("%5d :",number);
    int j;
    //prints the columns of the histogram with a * if the family size
    //occurs more than the number in the row
    for(j = 0; j <= length; j++){
      if(famSize[j] >= number)
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
  }
  // prints the graphic at the bottom
  printf("       ");
  for(i = 0; i <= length; i++){
    if((i % 10) == 0)
      printf("+");
    else
      printf("-");
  }
  printf("\n");
  printf("       ");

  //prints the number value of the family size axis every 10 units along the axis
  int dontPrint = 0;
  for(i = 0; i <= length; i++){
    if(((i) % 10) == 0){
      printf("%d",i);
      dontPrint = 1;
    }
    else if(dontPrint == 0)
      printf(" ");
    else
      dontPrint--;
  }
  printf("\n                family sizes\n");

}

int main ()
{
  printf ("Program to tabulate the results of a simulation ");
  printf ("in both a table and a histogram.\n");

  /* the number of couples in the simulation */
  /* this variable may be assigned a value in the program or read
     from the terminal */
  /* const int numberOfCouples = 60; /* // declaration, if asssigned */
  int numberOfCouples;                  // declaration, if read      */
  printf ("Enter number of couples in the simulation:  ");
  scanf ("%d", &numberOfCouples);

  /* number of children is recorded for sizes 1 .. maxRecordedSize */
  const int maxRecordedSize = 50;
  int famSize [maxRecordedSize + 1];

  /* the highest point of the histogram will have heightOfHistogram *'s */
  const int heightOfHistogram = 40;

  /* initialize random number generator */
  /* change the seed to the random number generator, based on the time of day */
  srand (time ((time_t *) 0) );

  /* array to keep track of the number couples with each number of children,
     initialize them all to 0
  */
  int i = 0;
  while(i <= maxRecordedSize){
    famSize[i] = 0;
    i++;
  }

  /* variable to track number of total children*/
  int numChildren = 0;
  int maxChildren = 0;

  int couple;
  for (couple = 0; couple < numberOfCouples; couple++)
    {
      /* couple starts with no children */
      int boys = 0;
      int girls = 0;
      int children = 0;
      
      /* couple has children */
      while ((boys == 0) || (girls == 0))
        {
          if ((rand() / (double) RAND_MAX) < 0.5) /* RAND_MAX is maximum random */
            boys++;
          else
            girls++;
        }

      // truncates the family size to maxRecorded size
      children = boys + girls;
      if(children > maxRecordedSize)
        children = maxRecordedSize;

      // increases the occure at set family size of children
      famSize[children] += 1;

      // adds children to total number of children and checks
      // if children is the new maximum number of children from any couple
      numChildren += children;
      if(children > maxChildren)
        maxChildren = children;
    }

  // Display info to the user
  printf ("\n\nSimulation based on %d couples\n", numberOfCouples);
  printf ("     family sizes truncated to %d\n", maxRecordedSize);
  printf ("     maximum height of histogram: %d\n\n",heightOfHistogram);
  printf ("     average number of children = %1.1lf\n", 
          numChildren / (double) numberOfCouples);
  printf ("     maximum number of children = %d\n\n",maxChildren);

  /* print out the table and histogram based on the simulation */
  printTable(famSize,maxRecordedSize);
  printf("\n\n");
  printHistogram(famSize,maxRecordedSize, heightOfHistogram);
  return 0;
}
