#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

void print_menu();
int str_cmp(char *str1, char *str2);
int get_num(char *str);
char *trim_str(char *str);

void print_menu()
{
  printf("Enter a sentence that you would like to separate by spaces (Don't start a sentence with \"!\"):\n");
  printf("Enter \"history\" if you want to display all the previous sentences.\n");
  printf("Enter \"!#\" to print sentence #\n");
  printf("Enter \"exit\" to terminate the program\n");
  return;
}

int main()
{
  char *str, *inp_str;
  size_t bufsize = 100; //Limit input line size
  size_t n_chars;
  List *LL = init_history();

  inp_str = (char *) malloc(bufsize * sizeof(char));
  if (inp_str == NULL) {
    printf("Unable to allocate buffer");
    exit(1);
  }

  while (1) {
    print_menu();
    n_chars = getline(&inp_str, &bufsize, stdin); //Read line and save number of characters
    inp_str[n_chars-1] = '\0';  //Change the '\n' for a '\0'
    str = trim_str(inp_str);
    if (str_cmp(str,"exit") == 0) { //Free space and exit the program
      free_history(LL);
      break;
    }
    else if (str_cmp(str,"history") == 0) { //Print history
      add_history(LL, copy_str(str,n_chars-1));
      print_history(LL);
    }
    else if (*str == '!') {     //Print the specify history if match exist
      int num = get_num(str+1);
      if (num > LL->n_items || num < 1)  //Make sure to not look/print an invalid history item
        printf("Item number %d doesn't exist\n",num);
      else
        printf("Sentence %d: %s\n", num, get_history(LL, num));
    }
    else if (*str != '\0') {  //Break input into tokens, print them and save string
      char **tokens = tokenize(str);
      print_tokens(tokens);
      free_tokens(tokens);
      add_history(LL, copy_str(str,n_chars-1));
    }
  }
  return 0;
}

