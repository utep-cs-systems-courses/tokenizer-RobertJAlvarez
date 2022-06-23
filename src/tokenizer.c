#include <stdio.h>
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
  while (*str != '\0' && space_char(*str))
    str++;
  return str;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  word = word_start(word);
  while (*word != '\0' && non_space_char(*word))
    word++;
  return word;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int n_words = 0;
  while (*str != '\0') {
    str = word_start(str);
    if (*str != '\0') //If the next word start with a '\0' is because there are no more words
      n_words++;      //Add one to the counter
    str = word_terminator(str);
  }
  return n_words;
}

//Return length from beginning to end of word
int word_len(char *str)
{
  return word_terminator(str) - word_start(str);
}

//Return length from beginning to end of string (initial white spaces count)
int str_len(char *str)
{
  char *temp = str;
  while (*temp++ != '\0');
  return temp - str;
}

/* Returns a freshly allocated new zero-terminated string containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  char *new_str = malloc(sizeof(char) * (len+1)); //len+1 because of the extra '\0'
  if (new_str == NULL) return NULL; //Not enough space in malloc
  char *temp = new_str; //save starting position of the new string
  while (len-- && (*temp++ = *inStr++) != '\0');
  *temp = '\0';   //Set last character to '\0'
  return new_str;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
    tokens[0] = "hello"     tokens[1] = "world"     tokens[2] = "string"     tokens[3] = 0 */
char **tokenize(char *str)
{
  int n_words = count_words(str);
  char **arr = malloc(sizeof(char *) * (n_words+1));  //n_words+1 because of the extra '\0'
  for (int i = 0; i < n_words; i++) {
    str = word_start(str);
    arr[i] = copy_str(str,word_len(str));
    str = word_terminator(str) + 1; //Start after the blank of the found word
  }
  arr[n_words] = '\0';  //Set last item in arr to '\0'
  return arr;
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  for (int i = 0; *tokens; tokens++)      //Iterate every token in tokens
    printf("Token %d: %s\n",++i,*tokens); //Print string being pointed by p
  printf("\n");
  return;
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens)
{
  for (char **p = tokens; *p; p++)
    free(*p);   //Free the space allocated for the string
  free(tokens); //Free the space to store the pointer to the string
  return;
}

