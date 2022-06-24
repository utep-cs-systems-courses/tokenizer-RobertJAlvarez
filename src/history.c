#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

/* Initialize the linked list to keep the history. */
List *init_history()
{
  List *p = malloc(sizeof(List));
  p->root = NULL; //list is empty
  return p;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store */
void add_history(List *list, char *str)
{
  Item *new = malloc(sizeof(Item));
  Item *temp = list->root;

  if (temp == NULL) {   //If this is the first item in list
    list->n_items = 0;
    list->root = new;
  } else {
    //Get last Item in list
    while(temp->next)
      temp = temp->next;
    if (str_cmp(temp->str, str) == 0) //Don't add line to history if identical to previous input
      return;
    temp->next = new; //Append new item to list
  }
  new->id = ++list->n_items;
  new->str = str;
  new->next = NULL;
  return;
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  Item *temp = list->root;
  while(temp->id != id)
    temp = temp->next;
  return temp->str; //return the string of the Item that match the id
}

/*Print the entire contents of the list. */
void print_history(List *list)
{
  Item *curr = list->root;
  while (curr != NULL) {
    printf("%d: %s\n",curr->id, curr->str);
    curr = curr->next;
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
  Item *next;           //Dummy variable to hold Item after curr
  while (curr->next != NULL) {
    next = curr->next;  //Save next item so we can free curr space without losing next item
    free(curr->str);
    free(curr);
    curr = next;
  }
  //Free the space used for the last Item
  free(curr->str);
  free(curr);
  free(list);
  return;
}

