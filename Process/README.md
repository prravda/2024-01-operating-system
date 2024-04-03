# Fork hands on
## description
운영체제 수업을 듣던 도중, process fork 과정 등을 직접 해 보라는 교수님의 추천이 있어서, 적절한 사례를 온라인에서 찾아본 뒤 직접 코드를 만들면서 공부한 단락입니다. 

## code
```c
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
```
## fork()
Clang 의 `fork()` 는 현재 process 를 그대로 복제한 뒤 새로운 process 를 만든다. 해당 호출이 성공하는 경우 `pid` 의 값은 `0`으로, 새로운 child process 가 만들어졌다는 뜻이다. 실패하면 `-1`을 반환한다. 

> The fork() function in C creates a new process by duplicating the existing process. The new process, called the child, is an exact copy of the calling process, called the parent. The fork() function returns the process id of the child process to the parent, and 0 to the child process. If the fork() function fails, it returns -1.

그리고 fork 가 성공적으로 이뤄진 순간, parent process, 그리고 child process 가 동시에 실행된다. 그래서 pid 가 0인 child process 의 execution 의 경우엔 child process 라고 printf 로 출력을 하고 process 가 마무리되는 거고, pid 가 0보다 큰 경우는 parent process 의 실행인 경우 또 조건에 맞게 프로그램이 실행되고 마무리되는 것이다. 

## wait()
syscall 중 `wait` 은 zombie process(orphan) 를 방지하는 역할을 한다. parent process 의 execution 이 먼저 실행되고 먼저 끝이 나는 순간, child process 는 parent process 를 잃게 된다. 그래서 `wait(NULL)` 을 통해 child process 의 실행이 끝날 때까지 명시적으로 대기할 것을 명령하는 것이다. 

물론 이렇게 orphan process 가 만들어 져도, init process (PID 0)가 처리하지만, 명시적인 표현이 아무래도 더 낫다. 
