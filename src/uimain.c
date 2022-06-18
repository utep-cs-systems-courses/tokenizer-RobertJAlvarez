#include <stdio.h>
#include "tokenizer.h"
#include "history.h"

int main(int argc, char **argv)
{
  //echo
  for (char **p = &argv[1]; *p; p++)
    printf("%s ",*p);
  printf("\n");

  char *str = "A b C?";
  //count_words test
  printf("%d == 3?\n", count_words(str));

  printf("str1 = %s,\t str1 address: %x\n",str,str);
  char *str2 = copy_str(str,7);
  printf("str2 = %s\t, str2 address: %x\n ",str2, str2);
  return 0;
}

