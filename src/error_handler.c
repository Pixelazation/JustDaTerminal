#include <stdio.h>
#include <stdlib.h>
#include <error_msgs.h>

typedef struct {
  int err_code;
  char* err_msg;
} ErrorLink;

ErrorLink error_links[] = {
  {ERR_COMMAND_NOT_FOUND, "Command not found"},
  {ERR_EXTRA_ARGS, "Too many arguments"},
  {ERR_LACKING_ARGS, "Too few arguments"},
  {ERR_LOC_NO_EXIST, "File or directory does not exist"},
  {0, "Unknown error"}   // Terminator
};

void handle_error(char *command, int error_code) {
  printf("Error running \"%s\": ", command);

  for (int i = 0; error_links[i].err_code != 0; i++) {
    if (error_code == error_links[i].err_code) {
      printf("%s\n", error_links[i].err_msg);
      return;
    }
  }

  printf("Unknown error");
}