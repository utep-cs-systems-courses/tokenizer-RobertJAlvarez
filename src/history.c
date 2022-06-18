#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store */
void add_history(List *list, char *str)
{
  return;
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  return list->root->str;
}

/*Print the entire contents of the list. */
void print_history(List *list)
{
  return;
}

/*Free the history list and the strings it references. */
void free_history(List *list)
{
  return;
}

