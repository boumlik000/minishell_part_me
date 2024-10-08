#include "minishell.h"

int last_exit_status;

char **parse_cmd(char *cmd)
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

int exec_cmd(char **arr, t_shell *shell)
{
    if (!arr || !arr[0])
        return 1;
    
    int i = 0;
    int has_pipe = 0;
    while (arr[i])
    {
        if (!ft_strncmp(arr[i], "|", -1))
        {
            has_pipe = 1;
            break;
        }
        i++;
    }
    
    if (has_pipe)
    {
        make_pipe(arr, shell);
    }
    else
    {
        // Check for builtin first
        char *builtins[] = {"pwd", "env", "echo", "exit", "cd", "export", "unset", NULL};
        int is_builtin = 0;
        
        for (int i = 0; builtins[i]; i++)
        {
            if (ft_strcmp(arr[0], builtins[i]) == 0)
            {
                is_builtin = 1;
                break;
            }
        }
        if (is_builtin)
            return exec_built_in(arr, shell);
            
        pid_t pid = fork();
        if (pid == 0)
        {
            // Child process
            char *cmd_path = find_command(arr[0], shell->env_array);
            if (cmd_path)
            {
                execve(cmd_path, arr, shell->env_array);
                free(cmd_path);  // Free if execve fails
            }
            ft_putstr_fd("minishell: command not found: ", 2);
            ft_putstr_fd(arr[0], 2);
            ft_putstr_fd("\n", 2);
            exit(127);
        }
        else
        {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                last_exit_status = WEXITSTATUS(status);
        }
    }
    
    return 0;
}



void init_shell(t_shell *shell, char **env)
{
    ft_bzero(shell, sizeof(t_shell));
    shell->env = cp_env_in_liste(env, shell);
    shell->garbage = NULL;
    
    // Create env_array for execve
    int env_count = 0;
    t_env *current = shell->env;
    while (current)
    {
        env_count++;
        current = current->next;
    }
    
    shell->env_array = malloc(sizeof(char *) * (env_count + 1));
    if (!shell->env_array)
        return;
    
    current = shell->env;
    int i = 0;
    while (current)
    {
        shell->env_array[i] = ft_strjoin(current->key, "=");
        char *temp = shell->env_array[i];
        shell->env_array[i] = ft_strjoin(temp, current->value);
        free(temp);
        current = current->next;
        i++;
    }
    shell->env_array[i] = NULL;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_shell shell;

    init_shell(&shell, env);

    while(1)
    {
        char *cmd = readline(">>> ");
        if (!cmd)
            break;
        add_history(cmd);
        
        char **splited = parse_cmd(cmd);
        if (splited)
        {
            exec_cmd(splited, &shell);
            free_array(splited);
        }
        
        ft_grapadd_back(&shell.garbage, ft_grapnew(cmd));
    }

    free_env(&shell);
    free_array(shell.env_array);
    clear_history();
    ft_garbage_free(shell.garbage);
    return last_exit_status;
}