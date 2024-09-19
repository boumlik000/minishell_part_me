#include <unistd.h>
#include <stdio.h>

int main(int ac,char **av,char **env)
{
    // char **av;
    (void)ac;
    (void)av;
    // char **env;
    int i = -1;

    while (env && env[++i])
    {
        printf("%s\n",env[i]);
        /* code */
    }
    
    return 0;
}
