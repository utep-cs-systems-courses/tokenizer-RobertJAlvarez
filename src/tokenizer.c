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
    str++;    //Add one to str until you are not on a space character
  return str;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  word = word_start(word);
  while (*word != '\0' && non_space_char(*word))
    word++;   //Go to next char in word until word is a space char
  return word;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int n_words = 0;
  while (*str != '\0') {
    str = word_start(str); //Get to the end of the word
    if (*str != '\0') //If the next word start with a '\0' is because there are no more words
      n_words++;      //Add one to the counter
    str = word_terminator(str); //Get to the end of the word
  }
  return n_words; //Return number of words
}

int word_len(char *str)
{
  return word_terminator(str) - word_start(str);
}

int str_len(char *str)
{
  char *temp = str;
  while (*(temp = word_terminator(temp)) != '\0');
  return temp - str;
}

/* Returns a freshly allocated new zero-terminated string containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  char *new_str = malloc(sizeof(char) * (len+1)); //Allocate enough space to store len characters and null
  if (new_str == NULL) return NULL; //return null if there was not enough space in malloc
  char *temp = new_str;   //Create a pointer to new_str
  while (len-- > 0)       //While we have more character to copy
    (*temp++ = *inStr++); //Copy next character and increase temp and inStr by one
  *temp = '\0';           //Set last character to '\0'
  return new_str;         //Return the copy word
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
    tokens[0] = "hello"     tokens[1] = "world"     tokens[2] = "string"     tokens[3] = 0 */
char **tokenize(char *str)
{
  int n_words = count_words(str); //Calculate number of words in str
  char **arr = malloc(sizeof(char) * (n_words+1));  //Allocate enough space to store (n_words+1) pointers to characters

  for (int i = 0; i < n_words; i++) {
    str = word_start(str);     //Get beginning of word
    arr[i] = copy_str(str,word_len(str));  //Copy word
    str = word_terminator(str) + 1; //Start after the blank of the found word
  }
printf("Pointer at %x is pointing to:\n",arr);
for (int j = 0; j < 3; j++)
  printf("arr[0][%d] = %c\n", j, arr[0][j]);
printf("arr[0] = %s at address %x\n", arr, arr);
  arr[n_words] = '\0';  //Set last item in arr to '\0'
  return arr; //Return array of pointer to arrays of characters
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  int i = 0;
  for (char **p = tokens; *p; p++)    //Iterate every token in tokens
    printf("Token %d: %s in address %x\n",++i,*p, p);  //Print string being pointed by p
  printf("\n");
  return;
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens)
{
  printf("Inside of free_tokens function\n");
  for (char **p = tokens; *p; p++) {  //Iterate every token in tokens
    printf("%s in %x\n", *p, p);
    free(p);    //Free the space allocated for the string in p
  }
  free(tokens);
  return;
}

