#include <unistd.h>
#include <stdio.h>


int main()
{
    char cmd[] = "/usr/bin/ls";
    char *av[] = {"ls",NULL};char *env[] = {NULL};
    printf("start of exec call : %s:\n",cmd);
    printf("===============================\n");
    if (execve(cmd,av,env) == -1)
    {
        perror("execv");
    }
    printf("oops,smt went weong\n");
    return 0;
}
