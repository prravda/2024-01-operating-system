// import appropriate header files
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
  // create a variable to store the process id
  pid_t pid;
  // Create a new process
  pid = fork();
  
  // if child process created successfully...
  if (pid == 0) {
    // check current process id (child process id)
    printf("This is the child process and the PID is %d\n", getpid());
  }

  // if came back to parent process successfully...
  if (pid > 0) {
    // check current process id (child process id)
    printf("This is the parent process and the PID is %d\n", getpid());
    // then wait the creation of child process using wati() syscall
    wait(NULL);
    // check pid again
    printf("Child process is created successfully\n");
  }

  // if an error is occured while creating child process...
  if (pid < 0) {
    // handle this error and exit the program
    perror("fork failed");
    exit(1);
  }
}