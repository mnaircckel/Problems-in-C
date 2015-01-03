/**********************************************************************
 * Name Marcel Champagne                                              *
 * Box(s): 3245                                                       *
 * Assignment name:  Supplemental Problem 5, Fall 2014                *
 * Assignment for Tuesday, December 9                                 *
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


// import libraries for input/out, malloc, math and string manipulation
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// define linked list item structure for an inventory:
// name, price, and a pointer to the next item
#define maxNameLen 50

struct item {
  char name [maxNameLen];
  double price;
  struct item * next;
};

// functions used to modify prices

// pre-conditions: Takes a double
// post-conditions: Returns a double based on the orignal price
//                  that has been modified by simple math.
/* reduce a price by 10% */
double a (double orig_price)
{
   return 0.90 * orig_price;
}

/* increase a price using a linear formula */
double b (double orig_price)
{
   return 2.50 + 1.15 * orig_price;
}

/* change prices up and down in a curious way */
double c (double orig_price)
{
   return 12.00 + 9 * cos(orig_price);
}

// end of modify price functions


// pre-conditions: Takes a pointer to a pointer to a item node
// post-conditions: Creates a new item and makes it the head of the list
void addItem(struct item ** inventory){
  struct item * newItem = (struct item *)malloc(sizeof(struct item));
  newItem->price = -1;
  strcpy(newItem->name,"");
  // Keep checking until user enters a postive number and a name
  while( (strcmp(newItem->name,"")==0) || newItem->price < 0){
    printf("Enter a price and a name seperated by a comma (e.g. 5.25, Pants):\n");
    scanf("%lf, %s",&newItem->price,newItem->name);
    while (getchar() != '\n');
    if(!strcmp(newItem->name,""))
      printf("Invalid name or price, please try again.\n");

  }
  newItem->next = *inventory;
  *inventory = newItem; 
}


// pre-conditions: Takes a pointer to a item node
// post-conditions: Iterates through the item nodes and prints the data
void printInventory(struct item * inventory){
  printf("\nStore Inventory:\n");
  while(inventory != NULL){
    printf("'%s' has a price of: %.2lf\n",inventory->name,
                                               inventory->price);
    inventory = inventory->next;
  }
  printf("\n");

}


// pre-conditions: Takes a pointer to a item node and a function
//                 that takes and returns a double
// post-conditions: Iterates through the item nodes and modifies the price
//                  price field of each node with function func
void map(double func (double), struct item * inventory){
  while(inventory != NULL){
    inventory->price = func(inventory->price);
    inventory = inventory->next;
  }
}

// pre-conditions: Takes an item node and a pointer to a pointer of a sorted lst
// post-conditions: Takes the item node and inserts it into the correct spot to
//                  form a sorted list with an additional item
void sort(struct item ** first, struct item invItem){

  // Create a new node
  struct item * newInsertion = (struct item *)malloc(sizeof(struct item));
  // Copy values from InvItem to new Node
  newInsertion->price = invItem.price;
  strcpy(newInsertion->name,invItem.name);

  // Check for case where the list is null or price is less than
  // the price of the very first item
  if(*first == NULL || (*first)->price >= invItem.price){
    // Inserting at start
    //printf("Insertion at begining with price of %lf\n",invItem.price);
    // Make insertion
    newInsertion->next = *first;
    *first = newInsertion;
    return;
  }
  else{
    // Make temp variable and continue through sorted list 
    // Stop if insertion spot found or reach end of list
    struct item * temp = *first;
    struct item * prevTemp = temp;
    while(temp->next != NULL && temp->price <= invItem.price){
      //printf("In loop comparing v %lf to i %lf\n",temp->price,invItem.price);
      //printf("Insertion is of greater value, continuing down list\n");
      prevTemp = temp;
      temp = temp->next;
    }

    // Make insertion
    // Regular case
    if(temp->price <= invItem.price){
      //printf("Inserting\n");
      newInsertion->next = temp->next;
      temp->next = newInsertion;
    }
    // Special case
    else{
      //printf("Inserting right before end\n");
      newInsertion->next = prevTemp->next;
      prevTemp->next = newInsertion;

    }
  }
    
}
// pre-conditions: Takes a pointer to a pointer of the inventory
// post-conditions: Iterates over the original unsorted list, taking an item
//                  node and a newList which begins as a null list
//                  and passing it to the insertionSort function.
//                  Free the previous item and set the pointer to the next item
//                  in the inventory.
//                  When the function finishes, it sets pointer to a pointer of the
//                  original inventory to the new list.
void unsortedSort(struct item ** first){
  // Create a temp variable to free memory
  struct item * clear;
  // Begin with a null list
  struct item * newList = NULL;

  // Loop through the original unsorted list
  while(*first != NULL){
    // Insert the current value of first into the sorted list
    sort(&newList,**first);
    //Set a temporary variable to reference first
    clear = *first;
    *first = (*first)->next;
    // Free the old memory
    free(clear);
  }
  // Set first to refer to the new list
  *first = newList;
}

int main(){
  struct item * inventory; // Create an empty inventory
  char option[81];

  // Loop through menu displaying options until user types 'q'
  while(1){
    printf("\nStore-inventory options:\n");
    printf("   e:  add an item (cost, name) to the inventory\n");
    printf("   p:  print all items in the inventory\n");
    printf("   a:  apply function \"a\" to all prices in the inventory\n");
    printf("   b:  apply function \"b\" to all prices in the inventory\n");
    printf("   c:  apply function \"c\" to all prices in the inventory\n");
    printf("   s:  sort the inventory by placing the items in ascending order of price\n");
    printf("   q:  quit\n");

    printf ("Enter a menu option: ");
    scanf ("%s", option);
    printf("\n");
    while (getchar() != '\n');
    if(strcmp(option,"e")==0){
      addItem(&inventory);
    }
    else if(strcmp(option,"p")==0){
      printInventory(inventory);
    }
    else if(strcmp(option,"a")==0){
      printf("Modifying inventory prices...\n");
      map(a,inventory);
    }
    else if(strcmp(option,"b")==0){
      printf("Modifying inventory prices...\n");
      map(b,inventory);
    }
    else if(strcmp(option,"c")==0){
      printf("Modifying inventory prices...\n");
      map(c,inventory);
    }
    else if(strcmp(option,"s")==0){
      // If inventory has 0 or 1 item, don't attempt to sort
      if(!(inventory == NULL || inventory->next == NULL)){
       unsortedSort(&inventory);
      }
      else{
        printf("Inventory is already sorted (trivial state).");
      }
    }
    else if(strcmp(option,"q")==0){
      break;
    }
    else{
      printf("Invalid option, please try again.\n");
    }
  }
  return 0;
}
