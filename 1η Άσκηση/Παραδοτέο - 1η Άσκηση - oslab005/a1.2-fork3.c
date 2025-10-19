#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{

    int fd1, fd2;
    int oflags, mode;
    oflags=O_CREAT | O_WRONLY | O_TRUNC;
    mode=S_IRUSR | S_IWUSR;
    int count=0;
    ssize_t rcnt;
    char buff[1024];
    ssize_t wcnt, wcnt2;

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
//------------------------------------------- parent opens files

    fd1=open(argv[1],O_RDONLY);
    if (fd1==-1)
    {
        perror("open");
        return 1;
    }

    fd2=open(argv[2], oflags,mode);
    if (fd2==-1)
    {
        perror("open");
        return 1;
    }

//-------------------------------------------

    pid_t p = fork();

    if (p<0) {perror("fork"); exit(1);}
    else if (p == 0)
    {
        for (;;)
        {
            rcnt = read(fd1, buff, sizeof(buff)-1);
            if (rcnt==0) break;
            if (rcnt==-1) {perror("read"); return 1;}
            buff[rcnt]= '\0';
            int i=0;
            while (buff[i]!='\0')
            {
            if (buff[i++]==argv[3][0]) count++;
            }
        }

    int n = sprintf(buff, "The character '%c' appears %d times in the file '%s'.\n", argv[3][0], count, argv[1]);
    wcnt = write(fd2, buff, n);
    if (wcnt == -1)
    {
        perror("write");
        return 1;
    }
    if (wcnt < n)
    {
        perror("write_space");
        return 1;
    }

    exit(0);

    }
    else
    {
        wait(NULL);
        close(fd1);
        close(fd2);
    }

    return 0;
}
