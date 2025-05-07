#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "commands.h"
#include "error_msgs.h"

typedef int (*command_func)(char **args);

typedef struct {
  const char *name;
  command_func func;
} CommandLink;

const CommandLink command_links[] = {
  { "dir", cmd_dir },
  { "cd", cmd_cd },
  { "mkdir", cmd_mkdir },
  { "rmdir", cmd_rmdir },
  { "del", cmd_del },
  { "touch", cmd_touch },
  { "type", cmd_type },
  { "help", cmd_help },
  { "cls", cmd_cls },
  { "date", cmd_date },
  { "time", cmd_time },
  { "exit", cmd_exit },
  { NULL, NULL } // End signifier
};

int dispatch(char **args) {
  for (int i = 0; command_links[i].name; i++) {
    if (strcmp(args[0], command_links[i].name) == 0) {
      return command_links[i].func(args);
    }
  }

  return ERR_COMMAND_NOT_FOUND;
}