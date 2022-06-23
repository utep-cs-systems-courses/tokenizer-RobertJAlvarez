#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

void print_menu();
int str_cmp(char *str1, char *str2);
int get_num(char *str);

void print_menu()
{
  printf("Enter a sentence that you would like to separate by spaces (Don't start a sentence with \"!\"):\n");
  printf("Enter \"history\" if you want to display all the previous sentences.\n");
  printf("Enter \"!#\" to print sentence #\n");
  printf("Enter \"exit\" to terminate the program\n");
  return;
}

//Compare two strings, return > 0 if str1 > str2, < 0 if str1 < str 2, 0 if str1 == str2
int str_cmp(char *str1, char *str2)
{
  for ( ; *str1 == *str2; str1++, str2++) //While the characters are the same in both strings
    if (*str1 == '\0')  //If the character is '\0' both string are the same
      return 0;
  return *str1 - *str2; //Return > 0 if str1 > str2, return < 0 if str1 < str 2
}

int get_num(char *str)
{
  int num;
  sscanf(str,"%d", &num);
  return num;
}

int main(int argc, char **argv)
{
  char *str;
  size_t bufsize = 100; //Limit input line size
  size_t n_chars;
  List *LL = init_history();

  str = (char *) malloc(bufsize * sizeof(char));
  if (str == NULL) {
    printf("Unable to allocate buffer");
    exit(1);
  }

  while (1) {
    print_menu();
    n_chars = getline(&str, &bufsize, stdin); //Read line in str and save number of characters
    str[n_chars-1] = '\0';  //Change the '\n' for a '\0'
    if (str_cmp(str,"exit") == 0) { //Free space and exit the program
      free_history(LL);
      break;
    }
    else if (str_cmp(str,"history") == 0) //Print history
      print_history(LL);
    else if (*str == '!') {     //Print the specify history if match exist
      int num = get_num(str+1);
      if (num > LL->n_items || num < 1)  //Make sure to not look/print an invalid history item
        printf("Item number %d doesn't exist\n",num);
      else
        printf("Sentence %d: %s\n", num, get_history(LL, num));
    }
    else {                    //Break input into tokens, print them individually and save string
      char **tokens = tokenize(str);
      print_tokens(tokens);
      free_tokens(tokens);
      add_history(LL, copy_str(str,n_chars-1));
    }
  }
  return 0;
}

