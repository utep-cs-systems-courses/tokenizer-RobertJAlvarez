#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int str_cmp(char *str1, char *str2);
int is_num(char c);

//Compare two strings, return > 0 if str1 > str2, < 0 if str1 < str 2, 0 if str1 == str2
int str_cmp(char *str1, char *str2)
{
  for ( ; *str1 == *str2; str1++, str2++) //While the characters are the same in both strings
    if (*str1 == '\0')  //If the character is '\0' both string are the same
      return 0;
  return *str1 - *str2; //Return > 0 if str1 > str2, return < 0 if str1 < str 2
}

//Return 1 if c is between 0 and 9 in the ASCII table
int is_num(char c)
{
  return (c <= 0x30 && c >= 0x39) ? 1 : 0;
}

int get_num(char *str)
{
  // Use this somewhere: sscanf(str+1,"%d", &num);
  return 1;
}

int main(int argc, char **argv)
{
  char **tokens;
  char *str;
  size_t bufsize = 100;
  size_t n_chars;
  List *LL = init_history();

  str = (char *) malloc(bufsize * sizeof(char));
  if (str == NULL) {
    printf("Unable to allocate buffer");
    return 1;
  }

  while (1) {
    printf("Enter a sentence that you would like to separate by spaces (Don't start a sentence with \"!\"):\n");
    printf("Enter \"history\" if you want to display all the previous sentences.\n");
    printf("Enter \"!#\" to print sentence #\n");
    printf("Enter \"exit\" to terminate the program\n");
    n_chars = getline(&str, &bufsize, stdin);
    str[n_chars-1] = '\0';  //Change the '\n' for a '\0'
    if (str_cmp(str,"exit") == 0) {
      free_history(LL);
      break;
    }
    else if (str_cmp(str,"history") == 0)
      print_history(LL);
    else if (*str != '!') {
      tokens = tokenize(str);
      print_tokens(tokens);
      free_tokens(tokens);
printf("String sent to be added to history: \"%s\"\n",str);
      add_history(LL, str);
printf("Current history:\n");
print_history(LL);
    }
    else if (*str == '!') { //Print the specify history
      int num = get_num(str+1);
      if (num <= 0)
        printf("Only enter a number following \"!\"\n");
      else {
        if (num > LL->n_items)
          printf("Item number %c doesn't exist\n",*(str+1));
        else
          printf("Sentence %d: %s\n", num, get_history(LL, num));
      }
    }
  }

  return 0;
}

