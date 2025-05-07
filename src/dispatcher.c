#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "commands.h"

typedef int (*command_func)(char **args);

typedef struct {
  const char *name;
  command_func func;
} CommandLink;

const CommandLink command_links[] = {
  { "dir", dir },
  { "cd", cd },
  { "mkdir", mkdir },
  { "rmdir", rmdir },
  { "del", del },
  { "touch", touch },
  { "type", type },
  { "help", help },
  { "cls", cls },
  { "date", date },
  { "time", time },
  { "exit", exit_terminal },
  { NULL, NULL } // End signifier
};

int dispatch(char **args) {
  for (int i = 0; command_links[i].name; i++) {
    if (strcmp(args[0], command_links[i].name) == 0) {
      return command_links[i].func(args);
    }
  }

  return -1;
}