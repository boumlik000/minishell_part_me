#include "minishell.h"
int last_exit_status; 

int pwd_()
{
    printf("%s\n", getenv("PWD"));
    return 0;
}
int echo_(char **args)
{
    int i = 1;
    int newline = 1;
    if (args[1] && ft_strncmp(args[1], "-n",-1) == 0) {
        newline = 0;
        i++;
    }
    while (args[i]) {
        if (ft_strncmp(args[i], "$?", -1) == 0) {
            char *exit_status_str = ft_itoa(last_exit_status);
            if (exit_status_str)
            {
                ft_putstr_fd(exit_status_str, 1);
                free(exit_status_str);
            }
        } else
            ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', 1);
    return 0;
}

int exit_(char **args)
{
    int exit_status = 0;
    int j = 0;
    long val = ft_atoi(args[0]);
    ft_putstr_fd("exit\n", 2);
    if (!args || !*args)
        exit(0);
    if (args[0][j] == '-' || args[0][j] == '+')
        j++;
    while (args[0] && args[0][j])
    {
        if (!ft_isdigit(args[0][j]))
        {
            printf("bash: exit: %s: numeric argument required\n",args[0]);
            exit(2);
        }
        j++;
    }
    if(args && args[0] && args[1])
    {
        printf("bash: exit: too many arguments\n");
        last_exit_status = 1;
        return last_exit_status;
    }
    if ((val > 0 && args[0][0] == '-') || (val < 0 && args[0][0] != '-') || ft_strlen(args[0]) > 20)
    {
        printf("bash: exit: %s: numeric argument required\n",args[0]);
        exit(2);
    }
    exit_status = ft_atoi(args[0]) % 256;
    exit(exit_status);
}

int exec_built_in(char **arr)
{
    int status = 0;
    if (arr && arr[0] && !ft_strncmp(arr[0], "pwd", -1))
        status = pwd_();
    else if (arr && arr[0] && !ft_strncmp(arr[0], "env", -1))
        env_();
    else if (arr && arr[0] && !ft_strncmp(arr[0], "echo", -1))
        echo_(arr);
    else if (arr && arr[0] && !ft_strncmp(arr[0], "exit", -1))
        exit_(&arr[1]);
    // else if (arr && arr[0] && !ft_strncmp(arr[0], "cd", -1))
    //     cd_();
    // else if (arr && arr[0] && !ft_strncmp(arr[0], "unset", -1))
    //     unset_();
    // else if (arr && arr[0] && !ft_strncmp(arr[0], "export", -1))
    //     export_();

    // else
    // {
    //     ft_putstr_fd("minishell: command not found: `" ,2);
    //     ft_putstr_fd(arr[0] ,2);
    //     ft_putstr_fd("'\n" ,2);
    //     exit(127);
    //     // return (1);
    // }
    return (status);
}
