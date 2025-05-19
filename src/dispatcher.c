#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "commands.h"
#include "error_msgs.h"

int dispatch(char **args) {
  for (int i = 0; command_links[i].name; i++) {
    if (strcmp(args[0], command_links[i].name) == 0) {
      return command_links[i].func(args);
    }
  }

  return ERR_COMMAND_NOT_FOUND;
}