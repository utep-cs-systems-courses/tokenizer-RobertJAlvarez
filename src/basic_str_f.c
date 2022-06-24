//Compare two strings, return > 0 if str1 > str2, < 0 if str1 < str 2, 0 if str1 == str2
int str_cmp(char *str1, char *str2)
{
  for ( ; *str1 == *str2; str1++, str2++) //While the characters are the same in both strings
    if (*str1 == '\0')  //If the character is '\0' both string are the same
      return 0;
  return *str1 - *str2; //Return > 0 if str1 > str2, return < 0 if str1 < str 2
}

//Change the int number pointed by *str to an int variable and return it
int get_num(char *str)
{
  int num;
  sscanf(str,"%d", &num);
  return num;
}

//Delete white spaces at the beginning of str and return the pointer to the first char != ' '
char *trim_str(char *str)
{
  while (*str != '\0' && *str == ' ')
    str++;
  return str;
}

