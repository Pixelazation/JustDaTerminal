#ifndef COMMANDS_H
#define COMMANDS_H

int cmd_dir(char **args);
int cmd_cd(char **args);
int cmd_mkdir(char **args);
int cmd_rmdir(char **args);
int cmd_del(char **args);
int cmd_touch(char **args);
int cmd_type(char **args);
int cmd_help(char **args);
int cmd_cls(char **args);
int cmd_date(char **args);
int cmd_time(char **args);
int cmd_exit(char **args);

typedef int (*command_func)(char **args);

typedef struct {
  const char *name;
  command_func func;
  const char *description;
} CommandLink;

extern const CommandLink command_links[];

#endif