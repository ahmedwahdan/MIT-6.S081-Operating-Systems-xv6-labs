// pingpong exercise for xv6 OS chapter 1: Operating System Interfaces
#include "kernel/types.h"
#include "user/user.h"

#define BYTES_TO_SEND (10000U)
#define READ_FD (0U)
#define WEITE_FD (1U)
#define TIMER_RESOLTION (100)

int main() {

  int ping_pipe_fd[2];
  int pong_pipe_fd[2];
  int fd;
  char buf[1] = {'A'};
  uint start_xticks = 0;
  uint end_xticks = 0;

  // create pipes
  if (pipe(ping_pipe_fd) < 0 || pipe(pong_pipe_fd) < 0) {
    fprintf(2, "pipe creation failed\n");
    exit(1);
  }

  // create child process
  fd = fork();
  if (fd < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  }

  if (fd > 0) {
    // close unused pipe ends
    close(ping_pipe_fd[READ_FD]);
    close(pong_pipe_fd[WEITE_FD]);

    printf("Starting parent process\n");
    start_xticks = uptime();
    for (uint i = 0; i < BYTES_TO_SEND; i++) {
      if (write(ping_pipe_fd[WEITE_FD], buf, 1) != 1) {
        fprintf(2, "Write error\n");
        break;
      }
      if (read(pong_pipe_fd[READ_FD], buf, 1) != 1) {
        fprintf(2, "Read error\n");
        break;
      }
    }
    end_xticks = uptime();
    // close pipes
    close(ping_pipe_fd[WEITE_FD]);
    close(pong_pipe_fd[READ_FD]);
    // wait for child process to terminate
    int status;
    wait(&status);

    if (status == 0) {
      printf("start ticks %d, end ticks %d\n", start_xticks, end_xticks);
      int elapsed = (end_xticks - start_xticks) * TIMER_RESOLTION;
      printf("Elapsed time %d milliseconds\n", elapsed);
      if (elapsed > 0) {
        int elapsed_seconds = elapsed / 1000;
        printf("Ping/Pong completed, performance: %d exchanges per second\n",
               BYTES_TO_SEND / elapsed_seconds);
      } else {
        printf("Ping/Pong completed too quickly to measure performance "
               "accurately\n");
      }
    } else {
      fprintf(2, "Child process exited with error\n");
    }

  } else {
    // close unused pipe ends
    close(ping_pipe_fd[WEITE_FD]);
    close(pong_pipe_fd[READ_FD]);
    int n;
    while ((n = read(ping_pipe_fd[READ_FD], buf, 1)) > 0) {
      buf[0]++;
      if (write(pong_pipe_fd[WEITE_FD], buf, 1) != 1) {
        fprintf(2, "Child write error\n");
        exit(1);
      }
    }
    if (n < 0) {
      fprintf(2, "Child read error\n");
      exit(1);
    }
    // close pipes
    close(ping_pipe_fd[READ_FD]);
    close(pong_pipe_fd[WEITE_FD]);
    printf("Finishing child process\n");
    exit(0);
  }
  exit(0);
}
