#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILDREN 5

int main() {
    pid_t child_pids[NUM_CHILDREN];

    // Create child processes
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) started.\n", i+1, getpid());
            // Perform child process tasks here
            sleep(5); // For example, sleep for 5 seconds
            printf("Child %d (PID: %d) finished.\n", i+1, getpid());
            return 0;
        } else if (pid > 0) {
            // Parent process
            child_pids[i] = pid;
			printf("--- PID %d\n", pid);
        } else {
            // Fork failed
            perror("Fork failed.");
            return 1;
        }
    }

    // Parent process waits for all child processes to complete
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    // Terminate all child processes using the kill syscall
    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (kill(child_pids[i], SIGKILL) == -1) {
            perror("Kill failed.");
        }
    }

    return 0;
}
