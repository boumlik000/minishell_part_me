#include "minishell.h"



char **pare_cmd(char *cmd)
{
    return (ft_split(cmd, ' '));
}

// void print_splited(char **arr)
// {
//     int i = -1;
//     while(arr && arr[++i])
//     {
//         printf("%s\n", arr[i]);
//     }
// }

int exec_cmd(char **arr)
{
    exec_built_in(arr);
    return (0);
}

int main(int ac,char **av)
{
    (void)ac;
    (void)av;
    int status;
    while(1)
    {
        char *cmd = readline(">>> ");
        if (!cmd)
            break;
        char **splited = pare_cmd(cmd);
        status = exec_cmd(splited);
        // exit(status);
        // print_splited(splited);
        free_arr(splited);
    }

}