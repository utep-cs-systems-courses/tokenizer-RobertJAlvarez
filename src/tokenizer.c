#include <stdlib.h>
#include "tokenizer.h"

/* Return true (non-zero) if c is a white space character ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c)
{
  return (c == '\t' || c == ' ') ? 1 : 0;
}

/* Return true (non-zero) if c is a non-white space character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c)
{
  return !space_char(c);
}

/* Returns a pointer to the first character of the next space-separated word in
  zero-terminated str. Return a zero pointer if str does not contain any words. */
char *word_start(char *str)
{
  if (*str == '\0') return str;
  while (*str != '\0' && space_char(*str))
    str++;    //Add one to str until you are not on a space character
  return str;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  while (*word != '\0' && non_space_char(*word))
    word++;   //Go to next char in word until word is a space char
  return word;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int n_words = 0;
  do {
    str = word_start(str);
    if (*str != '\0')
      n_words++;
    str = word_terminator(str);
  } while (*str != '\0');
  return n_words;
}

/* Returns a freshly allocated new zero-terminated string containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  char *new_str = malloc(sizeof(char) * len);
  if (new_str == NULL) return NULL; //return null if there was not enough space in malloc
  char *temp = new_str;
  while (*temp++ = *inStr++);
  return new_str;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
    tokens[0] = "hello"     tokens[1] = "world"     tokens[2] = "string"     tokens[3] = 0 */
char **tokenize(char *str)
{
  return 0;
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  return;
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens)
{
  return;
}

