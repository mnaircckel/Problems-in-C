/**********************************************************************
 * Name Marcel Champagne                                              *
 * Box(s): 3245                                                       *
 * Assignment name:  Supplemental Problem 6, Fall 2014                *
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
     *******************************************************************/

#include <stdio.h>

// A program that reads a number n and classifies all the 
// numbers between 1 and n


// pre-conditions: a positive integer to classify, 
// and the max positive integer number to be classified

// post-conditions: print out the number followed by its non-trivial factors,
// the sum of its proper factors and it's classification.
void classify(int number, int max){
  int sumPropFactors = 0;
  int i;
  int first = 1; // Used for table formatting when seperating factors
  // If the number is a unit
  if(number == 1){
    printf("%8d : : %d : unit\n",number,sumPropFactors);
    classify(number+1,max);
  }
  // Make sure to only classify if the number is equal to or less than the max
  // number to classsify
  else if(number <= max){
    printf("%8d :",number);
    // Check all the numbers between 1 and n to see if they are factors.
    for(i = 1; i < number; i++){
      if( (number % i) == 0){
        if(i != 1){
          if(first){
            printf(" %d",i);
            first = 0;
          }
          else{
            printf(", %d",i);
          }
        }
        sumPropFactors += i; // Increase sum of proper factors
      }

    }
    // Print out classifcation based on sum of proper factors
    printf(" : %d : ",sumPropFactors);
    if(sumPropFactors == 1){
      printf("prime\n");
    }
    else if(sumPropFactors < number){
      printf("defective\n");
    }
    else if(sumPropFactors == number){
      printf("perfect\n");
    }
    else{
      printf("super perfect\n");
    }
    // Recursively call classify with number+1
    classify(number+1,max);
  }
}

int main(){
  int max = -1;
  while(max == -1){
    printf("Enter the highest number to classify: \n");
    scanf("%d",&max);
    while(getchar() != '\n');
    if(max < 1){
      printf("Please enter a positive integer.\n\n");
      max = -1;
    }
  }
  printf("\n       The classification of numbers\n\n");
  printf("       n : non-trivial factors : sum of proper factors : classification\n");
  classify(1,max);
  return 0;
}
