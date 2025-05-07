#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

int dir(char **args){ 
  print_args(args);
  printf("Running dir\n");
  return 0;
}

int cd(char **args){
  print_args(args);
  printf("Running cd\n");
  return 0;
}

int mkdir(char **args){
  print_args(args);
  printf("Running mkdir\n");
  return 0;
}

int rmdir(char **args){
  print_args(args);
  printf("Running rmdir\n");
  return 0;
}

int del(char **args){
  print_args(args);
  printf("Running del\n");
  return 0;
}

int touch(char **args){
  print_args(args);
  printf("Running touch\n");
  return 0;
}

int type(char **args){
  print_args(args);
  printf("Running type\n");
  return 0;
}

int help(char **args){
  print_args(args);
  printf("Running help\n");
  return 0;
}

int cls(char **args){
  print_args(args);
  printf("Running cls\n");
  return 0;
}

int date(char **args){
  print_args(args);
  printf("Running date\n");
  return 0;
}

int time(char **args){
  print_args(args);
  printf("Running time\n");
  return 0;
}

int exit_terminal(char **args){
  if (count_args(args) > 0) {
    return ERR_EXTRA_ARGS;
  }

  return -1;
}