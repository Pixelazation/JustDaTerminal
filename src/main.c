#include "shell.h"

int main() {
  
  shell_init();
  shell_loop();
  shell_exit();

  return 0;
}