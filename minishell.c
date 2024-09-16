#include "minishell.h"

int last_exit_status;

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

int exec_cmd(char **arr,t_shell *shell)
{
    
    exec_built_in(arr,shell);
    return (0);
}


void init_shell(t_shell *shell, char **env)
{
    ft_bzero(shell, sizeof(t_shell));
    shell->env = cp_env_in_liste(env,shell);
    shell->garbage = NULL;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    int status;
    t_shell shell;

    init_shell(&shell, env);

    while(1)
    {
        char *cmd = readline(">>> ");
        if (!cmd)
            break;
        
        char **splited = pare_cmd(cmd);
        status = exec_cmd(splited, &shell);
        
        ft_grapadd_back(&shell.garbage, ft_grapnew(cmd));
        free_arr(splited);
    }

    free_env(&shell);
    ft_garbage_free(shell.garbage);
    // rl_clear_history();
    return 0;
}