#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0
#define WRITE 1

int main() {

  pid_t pid;
  int   fd[2];
char *const comando[]={"wc",NULL};;
char *const comando2[]={"ls",NULL};;

  if (pipe(fd) == -1) {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

  case 0:
    // Close the pipe write descriptor.
    close(fd[WRITE]);
    // Redirect STDIN to read from the pipe.
    dup2(fd[READ], STDIN_FILENO);
  	
    execvp(comando[0],comando);
	break;
  case -1:
    perror("fork() failed)");
    exit(EXIT_FAILURE);
	break;
  default:
    // Close the pipe read descriptor.
    close(fd[READ]);
    // Redirect STDOUT to write to the pipe.
    dup2(fd[WRITE], STDOUT_FILENO);
      
    execvp(comando2[0],comando2);
    break;
  }
}

