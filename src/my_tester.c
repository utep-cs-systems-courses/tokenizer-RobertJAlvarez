#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

int main(int argc, char **argv)
{
  //echo
  for (char **p = &argv[1]; *p; p++)
    printf("%s ",*p);
  printf("\n");

  char *str = "ABC def GhI J";

  //count_words test
  int n_words = count_words(str);
  printf("\"%s\" is make out of %d words\n", str, n_words);

  printf("str1 = %s\t, str1 address: %x\n",str,str);
  char *str2 = copy_str(str,str_len(str));
  printf("str2 = %s\t, str2 address: %x\n",str2, str2);

  //Tokenize
  char **arr = tokenize(str);
  printf("\n");
  print_tokens(arr);

  //History
  List *LL = init_history();
  for (char **p = arr; *p; p++)
    add_history(LL, *p);
  printf("Printing history:\n");
  print_history(LL);

  printf("\nHistory of 1: %s\n",get_history(LL,1));
  printf("We have %d items in history.\n",LL->n_items);

  printf("\nFreeing tokens space.\n");
  free_tokens(arr);
  printf("Tokens space free:)\n");

  printf("\nFreeing history.\n");
  free_history(LL);
  printf("History has been free\n");

  return 0;
}

