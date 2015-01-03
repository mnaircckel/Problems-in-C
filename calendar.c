/**********************************************************************
 * Name Marcel Champagne                                              *
 * Box(s): 3245                                                       *
 * Assignment name:  Supplemental Problem 4, Fall 2014                *
 * Assignment for Friday, November 20th                                *
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


// Program to maintain a person's daily calendar

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Appointment
#define maxLen 80
struct appt {
  int year;
  int month; /* 1=January, 2=February, ..., 12=December */
  int day;
  char text[maxLen];
};


/* Post-conditions: returns 1 if the date for appointment app1 comes before the 
   date for app2, and returns 0 otherwise */
// Pre-conditions: Takes two valid appt structs
int comesFirstByDate (struct appt app1, struct appt app2){
  //compare year
  if(app1.year < app2.year){
    return 1;
  }
  else if(app1.year > app2.year){
    return 0;
  }

  //compare month
  else if(app1.month < app2.month){
    return 1;
  }
  else if(app1.month > app2.month){
    return 0;
  }

  //compare day
  else if(app1.day < app2.day){
    return 1;
  }
  else if(app1.day > app2.day){
    return 0;
  }

  //same date
  else{
    return 0;
  }

}


/* Post-conditions: returns 1 if the text for appointment app1 comes before the 
   date for app2, and returns 0 otherwise */
// Pre-conditions: Takes two valid appt structs
int comesFirstByText (struct appt app1, struct appt app2){
  if(strcmp(app1.text,app2.text) < 0)
    return 1;
  return 0;
}

//implementation of insertion sort for array of structs
// pre-conditions: takes an array of appointments, the number of appts
// and the func to sort by 
// post-conditions: sorts the array by alphabetically or by date
void apptSort(struct appt * apptArray, int numAppts, int comesFirst(struct appt app1, struct appt app2)){
  int i;
  int j;
  for(i = 1; i < numAppts; i++){
    struct appt item = apptArray[i];
    int t = i-1;
    while ((t >= 0) && (comesFirst(apptArray[t],item) == 0)){
      apptArray[t+1] = apptArray[t];
      t--;
    }
    apptArray[t+1] = item;

  }
}


//double size of memory allocated for struct object
// pre-conditions: takes a pointer to the location of apptArray and
// the number of appts and a pointer to the maxSize to be stored
// post-conditions: doubles the size allocated
void apptResize(struct appt ** apptArray, int numAppts, int * maxSize){
  *maxSize *= 2; /* double maxSize */
  int i;
  struct appt * newApptArray = malloc (*maxSize * sizeof (struct appt));
  for(i = 0; i < numAppts; i++){
    newApptArray[i] = (*apptArray)[i];
  }
  free(*apptArray);
  *apptArray = newApptArray;
}

// pre-conditions: takes the apptArray to be added to, and a pointer to numAppts
// post-conditions: adds an appointment (if valid) to the end of the apptArray
// prompt the user to enter an appointment
void apptAdd(struct appt * apptArray, int * numAppts){
  
  printf("Enter the appointment in the following format:\n");
  printf("[month] [day], [year]: [text] (e.g. November 27, 2014: Thanksgiving Day): \n");
  char month[81];
  scanf("%s %d, %d: %s",&month,
                        &apptArray[*numAppts].day,
                        &apptArray[*numAppts].year,
                        apptArray[*numAppts].text);
  char c = getchar();

  // Convert month to number
  if(strcmp(month,"January") == 0){
    apptArray[*numAppts].month = 1;}
  else if(strcmp(month,"February") == 0){
    apptArray[*numAppts].month = 2;}
  else if(strcmp(month,"March") == 0){
    apptArray[*numAppts].month = 3;}
  else if(strcmp(month,"April") == 0){
    apptArray[*numAppts].month = 4;}
  else if(strcmp(month,"May") == 0){
    apptArray[*numAppts].month = 5;}
  else if(strcmp(month,"June") == 0){
    apptArray[*numAppts].month = 6;}
  else if(strcmp(month,"July") == 0){
    apptArray[*numAppts].month = 7;}
  else if(strcmp(month,"August") == 0){
    apptArray[*numAppts].month = 8;}
  else if(strcmp(month,"September") == 0){
    apptArray[*numAppts].month = 9;}
  else if(strcmp(month,"October") == 0){
    apptArray[*numAppts].month = 10;}
  else if(strcmp(month,"November") == 0){
    apptArray[*numAppts].month = 11;}
  else if(strcmp(month,"December") == 0){
    apptArray[*numAppts].month = 12;}
  else{
    printf("Invalid format, appointment will not be recorded.\n");
    return;
  }


  // Get the rest of the text entered by the user
  if( (c != '\n') && (apptArray[*numAppts].text[0] != '\0') ){
    int i;
    for(i = 0; i < maxLen; i++){
      if((c != '\n') && (apptArray[*numAppts].text[i] == '\0')){
        apptArray[*numAppts].text[i] = c;
        c = getchar();
      }
    }
    *numAppts += 1;

  }
  else if(c != '\n'){
    printf("Invalid format, appointment will not be recorded.\n");
  }
  else{
    *numAppts += 1;
  }

}

// pre-conditions: takes the apptArray to be printed and the numAppts
// Print out each appointment in the apptArray
void apptPrint(struct appt * apptArray, int numAppts){
  int i;
  char * month;
  // Convert number back to string
  for(i = 0; i < numAppts; i++){
    if(apptArray[i].month == 1){
      month = "January";}
    else if(apptArray[i].month == 2){
      month = "February";}
    else if(apptArray[i].month == 3){
      month = "March";}
    else if(apptArray[i].month == 4){
      month = "April";}
    else if(apptArray[i].month == 5){
      month = "May";}
    else if(apptArray[i].month == 6){
      month = "June";}
    else if(apptArray[i].month == 7){
      month = "July";}
    else if(apptArray[i].month == 8){
      month = "August";}
    else if(apptArray[i].month == 9){
      month = "September";}
    else if(apptArray[i].month == 10){
      month = "October";}
    else if(apptArray[i].month == 11){
      month = "November";}
    else if(apptArray[i].month == 12){
      month = "December";}

    printf("%s %d, %d : %s\n", month, 
                               apptArray[i].day, 
                               apptArray[i].year,
                               apptArray[i].text);
  }
}

// Main Menu
int main (){

  int maxSize = 1; /* current size of the apptArray */
  struct appt * apptArray = malloc (maxSize * sizeof (struct appt));
  int numAppts = 0;

  char inputOption[80];
  while(strcmp(inputOption,"q")){
    printf("Max number of appointments (dynamically updated): %d \n",maxSize );
    printf("\n\nCalendar program options:\n");
    printf("\te:  enter a new appointment (date, text)\n");
    printf("\td:  sort appointments by date\n");
    printf("\ta:  sort appointments alphabetically by appointment text\n");
    printf("\tp:  print current appointments\n");
    printf("\tq:  quit\n");
    scanf("%s",inputOption);
    while(getchar() != '\n');
    if(strcmp(inputOption,"e") == 0){
      if(numAppts == maxSize){
        apptResize(&apptArray,numAppts,&maxSize);
      }
      apptAdd(apptArray,&numAppts);
    }
    else if(strcmp(inputOption,"p") == 0){
      apptPrint(apptArray,numAppts);
    }
    else if(strcmp(inputOption,"d") == 0){
      apptSort(apptArray,numAppts,comesFirstByDate);
    }
    else if(strcmp(inputOption,"a") == 0){
      apptSort(apptArray,numAppts,comesFirstByText);
    }
  }

  return 0;
}
