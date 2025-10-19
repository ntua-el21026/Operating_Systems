#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv)
{

    pid_t p = fork();

    if (p<0) {perror("fork"); exit(1);}
    else if (p==0)
    {
        if (execv("./a1.1-system_calls", argv) == -1)
        {
            perror("execv");
            exit(1);
        }
        exit(0);
    }
    else
        wait(NULL);

    return 0;
}
