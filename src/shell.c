#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "shell.h"
#include "parser.h"
#include "dispatch.h"

void shell_init(void) {
  printf("===== Welcome back to JustDaTerminal / JDT =====");
  printf("\n\n");
}

void shell_loop(void) {
  char input[1024];

  while (true) {
    printf("JDT> ");

    // Take input and exit on EOF
    if (!fgets(input, sizeof(input), stdin)) {
      printf("\n");
      break;
    }

    // Remove trailing newline
    input[strcspn(input, "\n")] = '\0';

    // Skip empty lines
    if (strlen(input) == 0) {
        continue;
    }

    // Parse
    char **args = parse_tokens(input);

    // Dispatch
    dispatch(args);

    // Free args
    for (int i = 0; args[i]; i++) {
      free(args[i]);
    }

    free(args);
  }
}

void shell_exit(void) {
  printf("\n");
  printf("See you next time! Press enter to exit...");
  scanf("a");
}