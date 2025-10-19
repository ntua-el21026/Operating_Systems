#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/* Theoroume tis eisodous argv[1],argv[2] ta onomata twn arxeiwn
pros diavasma kai grapsimo antistoixa. To argv[3][0] einai o
xarakthras pros anazhthsh */

int main(int argc, char**argv)
{

// arxikopoioume tis metavlhtes gia ta read kai write

        int fd1, fd2;
        int oflags, mode;
        oflags=O_CREAT | O_WRONLY | O_TRUNC;
        mode = S_IRUSR | S_IWUSR;
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


/* ektelesh tou open kai gia ta 2 arxeia. To
   prwto einai read only enw to deftero write only */

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

/*ekteloume thn diadikasia read, vazontas '\0' sto telos kathe diavasmatos
  gia na mporoume mporoyme na elegxoume to telos tou buff */

        for (;;)
        {
                rcnt = read(fd1, buff, sizeof(buff)-1);
                if (rcnt==0) break;
                if (rcnt==-1)
                {
                    perror("read");
                    return 1;
                }
                buff[rcnt]= '\0';
                int i=0;
                while (buff[i]!='\0')
                {
                    if (buff[i++]==argv[3][0]) count++;
                }
        }

/* me thn sprintf metatrepoume thn frash pros egrafh se string (enw arxika eixe kai int kai char)
   gia na mpoume na ektelesoume thn write */

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

    close(fd1);
    close(fd2);
    return 0;
}
