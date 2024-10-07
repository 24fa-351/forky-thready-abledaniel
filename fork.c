#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int process(int num, int total, int pattern)
{
    printf("Process %d beginning\n", num);

    unsigned int sleep_rand = rand() % 8 + 1;
    sleep(sleep_rand);

    if (pattern == 1)
    {
        if (num == 1)
        {
            for (int i = 2; i <= total; i++)
            {
                pid_t pid = fork();
                if (pid == 0)
                {
                    printf("Process %d creating Process %d\n", num, i);
                    process(i, total, pattern);
                    exit(0);
                }
            }
        }
        for (int i = 1; i <= total; i++)
        {
            wait(NULL);
        }
    }

    if (pattern == 2)
    {
        if (num < total)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                printf("Process %d creating Process %d\n", num, num + 1);
                process(num + 1, total, pattern);
                exit(0);
            }
            wait(NULL);
        }
    }

    printf("Process %d exiting\n", num);
}

int main(int argc, char *argv[])
{
    int total = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if (total < 1 || 255 < total)
    {
        printf("Invalid total\n");
        return 1;
    }

    srand(time(NULL));
    printf("Pattern %d\n", pattern);
    process(1, total, pattern);
    printf("\n\n");

}