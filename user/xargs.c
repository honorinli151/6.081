#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) {
  int pid, n, buf_index = 0;
  char buf, arg[1024], *args[MAXARG];

  for (int i=1; i<argc; i++) args[i-1] = argv[i];
  args[argc-1] = arg;
  args[argc] = 0;

  while ( (n = read(0, &buf, 1)) > 0) {
    if (buf == '\n') {
      arg[buf_index] = 0;

      if ( (pid = fork()) < 0) {
        fprintf(2, "failed to fork");
        exit(1);
      }
      else if (pid == 0) {
        exec(args[0], args);
      }
      else {
        wait(0);
        buf_index = 0;
      }
    }
    else {
      arg[buf_index] = buf;
      buf_index++;
    }
  }

  exit(0);
}
