/** 
  test_helper.c  
**/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "unittest_defs.h"
#include "test_helper.h"


/* Execute cvms_txt as a child process */
int runCVMSTxt(const char *bindir, const char *infile, const char *outfile)
{
  char currentdir[1280];
  char runpath[1280];

  sprintf(runpath,"%s/run_cvms_txt.sh", bindir);

  /* Save current directory */
  getcwd(currentdir, 1280);
  
  /* Fork process */
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    perror("fork");
    return(1);
  } else if (pid == 0) {
    /* Change dir to cvmdir */
    if (chdir(bindir) != 0) {
      printf("FAIL: Error changing dir in runfortran\n");
      return(1);
    }

    execl( runpath, runpath, infile, outfile, (char *)0);
    perror("execl"); /* shall never get to here */
    printf("FAIL: CVM exited abnormally\n");
    return(1);
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      return(0);
    } else {
      printf("FAIL: CVM exited abnormally\n");
      return(1);
    }
  }

  return(0);
}
