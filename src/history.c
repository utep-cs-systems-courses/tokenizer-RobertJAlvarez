#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

/* Initialize the linked list to keep the history. */
List *init_history()
{
  List *p = malloc(sizeof(List)); //Get a pointer pointing to enough memory to hold a List
  p->root = NULL; //Root is empty
  return p;     //Return address of List
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store */
void add_history(List *list, char *str)
{
  Item *new = malloc(sizeof(Item));  //Get a pointer pointing to enough memory to hold an Item
  Item *temp = list->root;    //Save root in temp

  if (temp == NULL) {   //If root is NULL
    list->n_items = 0;
    new->id = 1;
    new->str = str;
    new->next = NULL;
    list->root = new;
  } else {  //If root is not NULL
    while(temp->next)     //While we have another Item
      temp = temp->next;  //Set temp to the next item
    new->id = temp->id+1;
    new->str = str;
    new->next = NULL;
    temp->next = new; //Append the new item to the list
  }
  list->n_items++;
  return;
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  Item *temp = list->root;  //Save root in temp
  while(temp->id != id)     //While if of temp doesn't match the passed id
    temp = temp->next;      //Update temp to the next Item
  return temp->str;         //Return the string of the Item that match the id
}

/*Print the entire contents of the list. */
void print_history(List *list)
{
  Item *curr = list->root;  //Save root in curr
  while (curr != NULL) {    //While current is not NULL
    printf("%d: %s\n",curr->id, curr->str); //Print current id followed by current string
    curr = curr->next;      //Update current to the Item
  }
  return;
}

/*Free the history list and the strings it references. */
void free_history(List *list)
{
  if (list->root == NULL) {
    free(list);
    return;
  }
  Item *curr = list->root;
  Item *next;               //Dummy variable to hold Item after curr
  while (curr->next != NULL) {
    next = curr->next;  //Save next item in next
    free(curr->str);    //Free the space used for the string
    free(curr);         //Free the space used for the Item
    curr = next;        //Set current Item to next item
  }
  //Free the space used for the last Item
  free(curr->str);
  free(curr);
  free(list);
  return;
}

