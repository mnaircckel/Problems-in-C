
    /***********************************************************************
     * Name(s) Marcel Champagne                                            *
     * Box(s):  3245                                                       *
     * Assignment name: Suplemental problem number 1                       *
     *      (25% off if name/number does not match assignment)             *
     * Assignment for Tuesday, September 16                                *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *    none                                                             *
     *                                                                     *
     *                                                                     *
     *   Help obtained                                                     *
     *     none                                                            *
     *                                                                     *
     *                                                                     *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature: Marcel Champagne                                       *
     ***********************************************************************/

/* This program should convert a given amount of British pounds and pence to USD
   then print the resulting amount, instructing the user a way for it to be paid

Pre-conditon: factors have been indentified at the start of the program,
              the values of pounds and pense are non-negative

Post-condition: the program prints equivalant number of dollars and cents,
                the number of bills of each denomination, and the
                number of cents in change

*/

#include <stdio.h>

int main ()
{
  // initalize the amount of British currency to be converted
  int pounds = 17;
  double pence = 32.85;

  // convert the British currency to USD
  double dollars_per_pound  = 1.697559;
  double dollars = ((pounds)+(pence/100))*dollars_per_pound;

  // print how the converted currency may be paid
  printf("%d pounds %.2lf pence translates to $%.2lf dollars \n",
	 pounds,pence,dollars-0.005);
  printf("This may be paid as\n");

  // find the number of bills and cents the USD can be paid in
  int twenties = (int)dollars / 20;
  int fives = ((int)dollars % 20) / 5;
  int ones = ((int)dollars % 5) / 1;
  int cents = (dollars - (int)dollars)*100;

  // print 20s, plural if number > 1
  if (twenties > 0){
    printf("%d twenty-dollar bill",twenties);
    if (twenties > 1){
      printf("s");
    }
    printf("\n");
  }

  // see above, except with 5s
  if (fives  > 0){
    printf("%d five-dollar bill",fives);
    if (fives  > 1){
      printf("s");
    }
    printf("\n");
  }

  // see above, except with 1s
  if (ones  > 0){
    printf("%d one-dollar bill",ones);
    if (ones > 1){
      printf("s");
    }
    printf("\n");
  }

  // print the number of cents, cents if number > 1, otherwise cent
  if (cents  > 0){
    if (cents > 1){
      printf("%d cents in change",cents);
    }
    else{
      printf("%d cents in change",cents);
    }

    printf("\n");
  }

 return 0;

}
