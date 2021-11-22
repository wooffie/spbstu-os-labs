#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <errno.h>

#include <signal.h>


int main(void) {

    void signal_p(int);
    void signal_c(int);

    struct sigaction sa;
    sa.sa_flags = 0;
    sigemptyset( & sa.sa_mask);

    int p_pid = getpid();
    int c_pid = fork();
    if (c_pid == -1) {
        perror("Bad fork");
        exit(4);
    }

    if (c_pid == 0) {

        c_pid = getpid();
        printf("Child PID: %d\n\n", c_pid);

        sa.sa_handler = signal_c;
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            printf("Signal not received");
            perror("SIGQUIT");
            exit(1);
        }
        if (sigaction(SIGUSR2, &sa, NULL) == -1) {
            printf("Signal not received");
            perror("SIGQUIT");
            exit(1);
        }

        for (int i = 1;; i++) {
            sleep(1);
            switch (i % 3) {
            case 0:
                kill(c_pid, SIGUSR1);
                break;
            case 1:
                kill(p_pid, SIGUSR1);
                break;
            default:
                kill(p_pid, SIGUSR2);
            }

        }

    } else {

        printf("Parent PID: %d\n", p_pid);

        sa.sa_handler = signal_p;
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            printf("Signal not received");
            perror("SIGQUIT");
            exit(1);
        }
        if (sigaction(SIGUSR2, &sa, NULL) == -1) {
            printf("Signal not received");
            perror("SIGQUIT");
            exit(1);
        }

        for (int i = 1;; i++) {
            sleep(1);
            switch (i % 3) {
            case 0:
                kill(c_pid, SIGUSR1);
                break;
            case 1:
                kill(c_pid, SIGUSR2);
                break;
            default:
                kill(p_pid, SIGUSR2);
            }

        }

    }

}

void signal_p(int the_sig) {
    signal(the_sig, signal_p);
    printf("Parent received %d\n\n", the_sig);
    if (the_sig == SIGQUIT) {
        exit(1);
    }
}

void signal_c(int the_sig) {
    signal(the_sig, signal_c);
    printf("Child received %d\n\n", the_sig);
    if (the_sig == SIGQUIT) {
        exit(1);
    }
}
