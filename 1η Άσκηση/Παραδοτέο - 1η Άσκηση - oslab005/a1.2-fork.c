#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

int x = 100;
pid_t p=fork();

if (p<0)
{
        perror("fork");
        exit(1);
}
else if (p==0) // Diergas;ia - paidi
{

//------------------------------------------------------------------------------------------------------
        printf("Hello world. My id (child) is %d and my parent's id is %d.\n",getpid(),getppid());
        printf("%d\n", x);
        x=50;
        printf("%d\n", x);
//------------------------------------------------------------------------------------------------------


        exit(0);
}
else // Diergasia - goneas
{
//-------------------------------------------------------------------------------------------------------
        printf("%d\n", x);
        x=80;
        printf("%d\n", x);
        printf("My child's id is %d.\n",wait(NULL));
//-------------------------------------------------------------------------------------------------------
}

return 0;
}
