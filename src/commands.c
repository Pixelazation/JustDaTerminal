#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 
#include <direct.h>
#include <dirent.h>
#include <windows.h>
#include "parser.h"
#include "error_msgs.h"
#include "commands.h"

const CommandLink command_links[] = {
  { "dir", cmd_dir, "Lists all files and directories in current directory" },
  { "cd", cmd_cd, "Change directories" },
  { "mkdir", cmd_mkdir, "Create a directory" },
  { "rmdir", cmd_rmdir, "Remove a directory" },
  { "del", cmd_del, "Delete a file" },
  { "touch", cmd_touch, "Create a file" },
  { "type", cmd_type, "Show contents of a file" },
  { "help", cmd_help, "Show this prompt" },
  { "cls", cmd_cls, "Clear your screen" },
  { "date", cmd_date, "Display or update the system date (YYYY-MM-DD)" },
  { "time", cmd_time, "Display or update the system time (HH:MM:SS)" },
  { "exit", cmd_exit, "Exit this shell" },
  { NULL, NULL, NULL } // End signifier
};

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

  char* curr_dir = getcwd(NULL, 0);

  if (!curr_dir) {
    return 99;
  }

  printf("Listing files and directories in \"%s\":\n", curr_dir);

  DIR *dir;
  struct dirent *entry;

  dir = opendir(".");
  if (dir == NULL) {
      perror("opendir");
      return 1;
  }

  while ((entry = readdir(dir)) != NULL) {
      printf("%s\t\t\t", entry->d_name);
      printf("\n");
  }

  printf("\n");

  closedir(dir);
  return 0;

}

int cmd_cd(char **args){
  if (count_args(args) > 1) {
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
  if (count_args(args) > 1) {
    return ERR_EXTRA_ARGS;
  }

  if (count_args(args) < 1) {
    return ERR_LACKING_ARGS;
  }

  mkdir(args[1]);

  return 0;
}

int cmd_rmdir(char **args){
  if (count_args(args) > 1) {
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
  if (count_args(args) < 1) {
    return ERR_LACKING_ARGS;
  }

  if (count_args(args) > 1) {
    return ERR_EXTRA_ARGS;
  }

  if (remove(args[1]) == 0) {
      printf("Deleted file: %s\n", args[1]);
      return 0;
  } else {
      return 99;
  }
}

int cmd_touch(char **args){
  FILE *fp = fopen(args[1], "a");
  if (fp == NULL) {
      return 99;
  }

  fclose(fp);
  printf("Created file: %s\n", args[1]);
  return 0;
}

int cmd_type(char **args){
  if (count_args(args) < 1) {
    return ERR_LACKING_ARGS;
  }

  if (count_args(args) > 1) {
    return ERR_EXTRA_ARGS;
  }

  FILE *fp = fopen(args[1], "r");
  if (!fp) {
      return 99;
  }

  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      printf("%s", buffer);
  }

  fclose(fp);
  return 0;
}

int cmd_help(char **args){
  if (count_args(args) > 0) {
    return ERR_EXTRA_ARGS;
  }

  printf("\n");

  for (int i = 0; command_links[i].name; i++) {
    printf("%s \t\t %s\n", command_links[i].name, command_links[i].description);
  }

  printf("\n");

  return 0;
}

int cmd_cls(char **args){
  if (count_args(args) > 0) {
    return ERR_EXTRA_ARGS;
  }

  printf("\e[1;1H\e[2J");     // RegEx String to add lines equal to terminal height and move cursor to first char
  return 0;
}

int cmd_date(char **args){
  if (count_args(args) > 1) {
    return ERR_EXTRA_ARGS;
  }

  SYSTEMTIME st;
  GetLocalTime(&st);

  if (count_args(args) == 0) {
    printf("%04d-%02d-%02d\n", st.wYear, st.wMonth, st.wDay);
    return 0;
  }

  int year, month, day = 0;
  if (sscanf(args[1], "%d-%d-%d", &year, &month, &day) < 2) {
    return ERR_WRONG_FORMAT;
  }

  st.wYear = year;
  st.wMonth = month;
  st.wDay = day;

  if (!SetLocalTime(&st)) {
      return 99;
  }
  
  return 0;
}

int cmd_time(char **args){

  if (count_args(args) > 1) {
    return ERR_EXTRA_ARGS;
  }

  SYSTEMTIME st;
  GetLocalTime(&st);

  if (count_args(args) == 0) {
    printf("%02d:%02d:%02d\n", st.wHour, st.wMinute, st.wSecond);
    return 0;
  }

  int hour, minute, second = 0;
  if (sscanf(args[1], "%d:%d:%d", &hour, &minute, &second) < 2) {
    return ERR_WRONG_FORMAT;
  }

  st.wHour = hour;
  st.wMinute = minute;
  st.wSecond = second;

  if (!SetLocalTime(&st)) {
      return 99;
  }
  
  return 0;
}

int cmd_exit(char **args){
  if (count_args(args) > 0) {
    return ERR_EXTRA_ARGS;
  }

  return -1;
}