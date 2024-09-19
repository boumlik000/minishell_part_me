#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid1 = fork();
    if (pid1 == -1)
    {
        perror("pid1");
        return 0;
    }
    if (pid1 == 0)
    {
        sleep(3);
        printf("finished execution pid1 [%d]\n",getpid());
        return 0;
    }
    



    int pid2 = fork();
    if (pid2 == -1)
    {
        perror("pid1");
        return 0;
    }
    if (pid2 == 0)
    {
        sleep(1);
        printf("finished execution pid2 [%d]\n",getpid());
        return 0;
    }

    // int waitpid1 = wait(NULL);
    int waitpid1 = waitpid(pid1,NULL,0);
    printf("\t[%d] waitpid \n",waitpid1);
    int waitpid2 = waitpid(pid2,NULL,0);
    // int waitpid2 = wait(NULL);
    printf("\t[%d] waitpid2 \n",waitpid2);

    return 0;
}
