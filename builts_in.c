#include "minishell.h"


int exec_built_in(char **arr,t_shell *shell)
{
    int status = 0;
    if (arr && arr[0] && !ft_strncmp(arr[0], "pwd", -1))
        status = pwd_(shell);
    else if (arr && arr[0] && !ft_strncmp(arr[0], "env", -1))
        env_(shell->env);
    else if (arr && arr[0] && !ft_strncmp(arr[0], "echo", -1))
        echo_(arr);
    else if (arr && arr[0] && !ft_strncmp(arr[0], "exit", -1))
        exit_(&arr[1]);
    else if (arr && arr[0] && !ft_strncmp(arr[0], "cd", -1))
        cd_(arr,shell);
    else if (arr && arr[0] && !ft_strncmp(arr[0], "export", -1))
        export_(arr,shell);
    else if (arr && arr[0] && !ft_strncmp(arr[0], "unset", -1))
        status = unset_(arr,shell);

    // else
    // {
    //     ft_putstr_fd("minishell: command not found: `" ,2);
    //     ft_putstr_fd(arr[0] ,2);
    //     ft_putstr_fd("'\n" ,2);
    //     status = last_exit_status = 127;
    //     // return (1);
    // }
    return (status);
}
