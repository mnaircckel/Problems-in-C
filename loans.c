
    /***********************************************************************
     * Name(s) Marcel Champagne                                            *
     * Box(s):  3245                                                       *
     * Assignment name: Supplemental Problem Number 2                      *
     *      (25% off if name/number does not match assignment)             *
     * Assignment for Tuesday, September 30                                *
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

/*
This program calculates loan payments. 
*/

#include <stdio.h>

double compute_neg_power(double value, int n);
double compute_payment(double annRate, int months, double amt);
double compute_total_payment(double annRate, double amt, int doublePay, double payment);

int main ()
{
  // Define initial varibles for amount, months, and annual interest rate
  double amt = 2200.0;
  int months = 30;
  double annRate = 6.75;

  // Print information on loan
  printf("\nConsider a loan of %lf with an annual interest rate of %lf\n",amt,annRate);
  printf("and a loan length of %d months.\n\n",months);

  // Calculate the normal payment to be paid each month
  double payment = compute_payment(annRate, months, amt);
  printf("This loan will have a normal payment of $%lf\n\n",payment);
  
  //Calculate the total paid for 3 special cases described below
  double totalPaid1 = compute_total_payment(annRate, amt, 0, payment);
  int months1 = totalPaid1/payment;

  double totalPaid2 = compute_total_payment(annRate, amt, 1, payment);
  int months2 = totalPaid2/payment;

  double totalPaid3 = compute_total_payment(annRate, amt, 12, payment);
  int months3 = totalPaid3/payment;

  // Describe 3 special payment methods to the user
  printf("If the customer pays exactly the expected amount each month:\n");
  printf("The loan will be paid off in %d months.\n",months1);
  printf("The loan will have a total amount paid of $%lf.\n",totalPaid1);
  printf("Which costs $%lf more than option 3.\n\n",totalPaid1-totalPaid3);
  
  printf("If the customer pays twice the excepted amount the first\n");
  printf("month and exactly the expected amount the remaining months:\n");
  printf("The loan will be paid off in %d months.\n",months2);
  printf("The loan will have a total amount paid of $%lf.\n",totalPaid2);
  printf("Which costs $%lf more than option 3.\n\n",totalPaid2-totalPaid3);

  printf("If the customer pays twice the expected amount for the first\n");
  printf("year and exactly the expected amount the remaining months:\n");
  printf("The loan will be paid off in %d months.\n",months3);
  printf("The loan will have a total amount paid of $%lf.\n\n",totalPaid3);
  
 return 0;

}

double compute_payment(double annRate, int months, double amt){
  // compute payment using formula
  double monthlyRate = annRate / 1200.0;
  double partComp = compute_neg_power(1+monthlyRate,months);
  double payment = amt * monthlyRate / (1.0 - partComp);
  return ((int)(payment * 100.0 + 0.5)) / 100.0;		 
}

double compute_neg_power(double value, int n){
  // this function computes a double of a value raised to a negative exponent n
  int i;
  double initVal = value;
  for (i = 1; i <= n-1; i++){
    value *= initVal;
  }
  return (1.0 / value);
}

double compute_total_payment(double annRate, double amt, int doublePay, double payment){
  // compute total payment by applying interest and subtracting payment to a blanace
  double monthlyRate = annRate / 1200.0;
  double balance = amt;
  double totalPaid = 0;
  int months = 1;

  while(balance > 0){
    if (months <= doublePay){
      balance = balance + (balance * monthlyRate) - payment*2;
      totalPaid += payment*2;
    }
    else{
      balance = balance + (balance * monthlyRate) - payment;
      totalPaid += payment;
    }
    months += 1;
    }
  return totalPaid;
 }
