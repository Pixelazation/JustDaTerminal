#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 
#include "parser.h"
#include "error_msgs.h"

void print_args(char **args) {
  for (int i = 0; args[i]; i++) {
    printf("arg[%d]: %s\n", i, args[i]);
  }
}

int count_args(char **args) {
  return token_count(args) - 1;
}

int cmd_dir(char **args){ 
  if (count_args(args) > 0) {
    return ERR_EXTRA_ARGS;
  }

  system("pwd");
  return 0;
}

int cmd_cd(char **args){
  if (count_args(args) > 2) {
    return ERR_EXTRA_ARGS;
  }

  if (count_args(args) < 1) {
    return ERR_LACKING_ARGS;
  }

  if (chdir(args[1]) != 0) {
    return ERR_LOC_NO_EXIST;
  }

  return 0;
}

int cmd_mkdir(char **args){
  if (count_args(args) > 2) {
    return ERR_EXTRA_ARGS;
  }

  if (count_args(args) < 1) {
    return ERR_LACKING_ARGS;
  }

  mkdir(args[1]);

  return 0;
}

int cmd_rmdir(char **args){
  if (count_args(args) > 2) {
    return ERR_EXTRA_ARGS;
  }

  if (count_args(args) < 1) {
    return ERR_LACKING_ARGS;
  }

  if (rmdir(args[1]) != 0) {
    return ERR_LOC_NO_EXIST;
  }

  return 0;
}

int cmd_del(char **args){
  print_args(args);
  printf("Running del\n");
  return 0;
}

int cmd_touch(char **args){
  print_args(args);
  printf("Running touch\n");
  return 0;
}

int cmd_type(char **args){
  print_args(args);
  printf("Running type\n");
  return 0;
}

int cmd_help(char **args){
  print_args(args);
  printf("Running help\n");
  return 0;
}

int cmd_cls(char **args){
  if (count_args(args) > 0) {
    return ERR_EXTRA_ARGS;
  }

  system("clear");
  return 0;
}

int cmd_date(char **args){
  print_args(args);
  printf("Running date\n");
  return 0;
}

int cmd_time(char **args){
  print_args(args);
  printf("Running time\n");
  return 0;
}

int cmd_exit(char **args){
  if (count_args(args) > 0) {
    return ERR_EXTRA_ARGS;
  }

  return -1;
}