#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "json_parser.h"

//class JSONParser;

char* JSONParser :: trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while (isspace((unsigned char)*str)) str++;

  if (*str == 0) // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end + 1) = 0;

  return str;
}

char* JSONParser :: get_key(char input_buffer[], char input_key[]) {
  int idx = 0;
  int slen = strlen(input_buffer);
  int kv = 0;

  char key[15] ;//= (char *)malloc(sizeof(char) * 20);
  char *value = (char *)malloc(sizeof(char) * 20);

  while (idx != slen)
  {
    int startIdx;
    if (input_buffer[idx] == '\"') {
      idx++;
      startIdx = idx;
      while (input_buffer[idx] != '\"')
      {
        idx++;
      }
      if (kv == 0)
      {
        memset(key, '\0', sizeof(key));
        strncpy(key, input_buffer + startIdx, idx - startIdx);
      }
      else if (kv == 1)
      {
        memset(value, '\0', sizeof(value));
        strncpy(value, input_buffer + startIdx, idx - startIdx);
      }

      kv++;
      if (kv == 2)
      {
        kv = 0;
        if(strcmp(trimwhitespace(key),input_key)==0)
            return trimwhitespace(value);
      }
    }
    idx++;
}
return NULL;
}
