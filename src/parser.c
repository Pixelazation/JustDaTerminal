#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 64

char **parse_tokens(const char *input) {
  char **argv = malloc(sizeof(char *) * MAX_TOKENS);
  int argc = 0;

  char *input_copy = strdup(input);
  char *token = strtok(input_copy, " \t\n");

    while (token != NULL && argc < MAX_TOKENS - 1) {
        argv[argc++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }

  argv[argc] = NULL;
  free(input_copy);
  return argv;
}

int token_count(char** tokens) {
  int i;
  for (i = 0; tokens[i]; i++);

  return i;
}