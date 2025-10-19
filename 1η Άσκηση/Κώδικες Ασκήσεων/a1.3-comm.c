#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

// Prints the active children of the process
short unsigned int c_counter = 0, result = 0, P = 5;
int fd[2];
void child_counter (int signum)
{
        // Printing the new signal
        close(fd[1]);
        for (short unsigned int i = 0; i < P; i++)
        {
                short unsigned int temp2 = 0;
                if (read(fd[0], &temp2, sizeof(temp2)) == 0) break;
                result += temp2;
                c_counter--;
        }

        char buff_s[60];
        int ns = sprintf(buff_s, "Control_C pressed: the number of active children is: %d.", c_counter);
        ssize_t wcnt = write(0, buff_s, ns);
        if (wcnt == -1) // Write error
        {
                perror("write");
                exit(1);
        }
        if (wcnt < ns)
        {
                perror("write_space");
                exit(1);
        }
}

int main(int argc, char** argv)
{
        // Signal Handler
        struct sigaction sa;
        sigset_t sigset;
        sa.sa_handler = child_counter;
        sa.sa_flags = SA_RESTART;
        memset(&sa.sa_restorer, 0, sizeof sa.sa_restorer);
        memset(&sa.sa_mask, 0, sizeof sa.sa_mask);
        if (sigaction(SIGINT, &sa, NULL) < 0)
        {
                perror("sigaction");
                exit(1);
        }

        int f2;
        int oflags = O_CREAT | O_WRONLY | O_TRUNC, mode = S_IRUSR | S_IWUSR;
        ssize_t wcnt2;

/* elegxoume an ta orismata einai akrivws 3 kai typwnoyme to mynhma me write kai fd=0*/

        if (argc!=4)
        {
            wcnt2 = write(0,"The number of arguments must be exactly 3.\n",strlen("The number of arguments must be exactly 3.\n"));
            if (wcnt2 == -1) // Write error
            {
                perror("write");
                return 1;
            }
            if (wcnt2 < strlen("The number of arguments must be exactly 3.\n"))
            {
                perror("write_space");
                return 1;
            }
            return 1;
        }

/* elegxoume an to trito orisma einai mono enas xarakthras
   kai typwnoume to mhnyma me write kai fd=0 */

        if (argv[3][1]!='\0')
        {
            wcnt2 = write(0,"The third argument must be only 1 character.\n",strlen("The third argument must be only 1 character.\n"));
            if (wcnt2 == -1) // Write error
            {
                perror("write");
                return 1;
            }
            if (wcnt2 < strlen("The third argument must be only 1 character.\n"))
            {
                perror("write_space");
                return 1;
            }
            return 1;
        }

        // Pipe could not be established
        if (pipe(fd) < 0)
        {
                perror("pipe");
                exit(1);
        }

        // Error opening the file to write
        f2 = open(argv[2], oflags, mode);
        if (f2 == -1)
        {
                perror("open");
                exit(1);
        }

        for (short unsigned int i = 0; i < P; i++)
        {
                c_counter++;
                pid_t p = fork();
                if (p < 0) // Error in the fork
                {
                        perror("fork");
                        exit(1);
                }
                else if (p == 0) // Child proc
                {
                        close(fd[0]);

                        // Signal Handler
                        struct sigaction sa;
                        sigset_t sigset;
                        sa.sa_handler = SIG_IGN;
                        memset(&sa.sa_restorer, 0, sizeof sa.sa_restorer);
                        memset(&sa.sa_flags, 0, sizeof sa.sa_flags);
                        memset(&sa.sa_mask, 0, sizeof sa.sa_mask);
                        if (sigaction(SIGINT, &sa, NULL) < 0)
                        {
                                perror("sigaction");
                                exit(1);
                        }

                        int f1 = open(argv[1], O_RDONLY);
                        if (f1 == -1)
                        {
                                perror("open");
                                exit(1);
                        }
                        ssize_t rcnt;
                        char buff[1];
                        short unsigned int count = 0;
                        lseek(f1, i, SEEK_SET);
                        while (1)
                        {
                                rcnt = read(f1, buff, 1);
                                if (rcnt == 0) break;
                                if (rcnt == -1)
                                {
                                        perror("read");
                                        exit(1);
                                }
                                if (buff[0] == argv[3][0]) count++;
                                lseek(f1, P-1, SEEK_CUR);
                        }
                        write(fd[1], &count, sizeof(count));
                        close(f1);
                        exit(0);
                }
                else ;
        }

        //for (short unsigned int i = 0; i < P; i++) wait(NULL);

        short unsigned int temp;
        // Calculating the result
        close(fd[1]);
        for (short unsigned int i = 0; i < P; i++)
        {
                if (read(fd[0], &temp, sizeof(temp)) == 0) break;
                result += temp;
                c_counter--;
        }

        // Printing the result
        char buff_r[60];
        int n = sprintf(buff_r, "The character '%c' appears %d times in the file '%s'.\n", argv[3][0], result, argv[1]);
        ssize_t wcnt = write(f2, buff_r, n);
        if (wcnt == -1) // Write error
        {
                perror("write");
                return 1;
        }
        if (wcnt < n)
        {
                perror("write_space");
                return 1;
        }

        close(f2);

        return 0;
}
