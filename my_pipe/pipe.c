//to learn waitpid
//to learn access
//to learn execve
//to learn readline




#include "../minishell.h"

void print_array(char **array)
{
    if (!array)
        return;
    
    for (int i = 0; array[i]; i++)
        printf("%s\n", array[i]);
}

void free_array(char **array)
{
    if (!array)
        return;
    
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

char *find_command(char *cmd, char **env)
{
    // If cmd starts with "./", "../", or "/", try to execute directly
    if (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
    {
        if (access(cmd, X_OK) == 0)
        {
            return ft_strdup(cmd);  // Return a copy to maintain consistent memory handling
        }
        return NULL;
    }

    char *path = NULL;
    char *path_copy = NULL;
    char *dir = NULL;
    char *full_path = NULL;

    // Find PATH in environment variables
    for (int i = 0; env[i]; i++)
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            path = env[i] + 5;
            break;
        }
    }

    if (!path)
        return NULL;

    path_copy = ft_strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
        if (!full_path)
        {
            free(path_copy);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, cmd);
        
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        
        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

void set_dup(int has_pipe, int fd[2], int end)
{
    if (has_pipe)
    {
        if (dup2(fd[end], end) == -1)
        {
            perror("dup2");
            exit(1);
        }
        if (close(fd[0]) == -1 || close(fd[1]) == -1)
        {
            perror("close");
            exit(1);
        }
    }
}
void execute_command(char **args, t_shell *shell)
{
    if (!args || !args[0])
        exit(1);

    char *builtins[] = {"pwd", "env", "echo", "exit", "cd", "export", "unset", NULL};
    int is_builtin = 0;
    
    for (int i = 0; builtins[i]; i++)
    {
        if (ft_strcmp(args[0], builtins[i]) == 0)
        {
            is_builtin = 1;
            break;
        }
    }
    
    if (is_builtin)
    {
        exec_built_in(args, shell);
        exit(last_exit_status);
    }
    
    char *cmd_path = find_command(args[0], shell->env_array);
    if (cmd_path)
    {
        execve(cmd_path, args, shell->env_array);
        free(cmd_path);  // Free if execve fails
    }
    ft_putstr_fd("minishell: command not found: ", 2);
    ft_putstr_fd(args[0], 2);
    ft_putstr_fd("\n", 2);
    exit(127);
}
void make_pipe(char **args, t_shell *shell)
{
    if (!args)
        return;

    int i = 0;
    int pipe_count = 0;
    pid_t pids[1024];
    int pipes[1024][2];
    int cmd_count = 0;
    char **current_cmd = NULL;

    // Count pipes and commands
    while (args[i])
    {
        if (ft_strcmp(args[i], "|") == 0)
            pipe_count++;
        i++;
    }
    cmd_count = pipe_count + 1;

    // Create all pipes first
    for (int j = 0; j < pipe_count; j++)
    {
        if (pipe(pipes[j]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }

    // Create all child processes
    i = 0;
    for (int cmd_index = 0; cmd_index < cmd_count; cmd_index++)
    {
        // Create array for current command
        int cmd_len = 0;
        while (args[i + cmd_len] && ft_strcmp(args[i + cmd_len], "|") != 0)
            cmd_len++;
        
        current_cmd = malloc(sizeof(char *) * (cmd_len + 1));
        if (!current_cmd)
        {
            perror("malloc");
            exit(1);
        }
        
        for (int j = 0; j < cmd_len; j++)
            current_cmd[j] = args[i + j];
        current_cmd[cmd_len] = NULL;

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        
        if (pid == 0)
        {
            // Child process
            // Set up pipes
            if (cmd_index > 0)
            {
                dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
            }
            if (cmd_index < cmd_count - 1)
            {
                dup2(pipes[cmd_index][1], STDOUT_FILENO);
            }

            // Close all pipe file descriptors
            for (int j = 0; j < pipe_count; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execute_command(current_cmd, shell);
            // If execute_command returns (it shouldn't), exit
            exit(1);
        }
        else
        {
            // Parent process
            pids[cmd_index] = pid;
            free(current_cmd);
        }

        // Move to next command
        i += cmd_len + 1;
    }

    // Close all pipe file descriptors in the parent
    for (int j = 0; j < pipe_count; j++)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }

    // Wait for all child processes to complete
    for (int k = 0; k < cmd_count; k++)
    {
        int status;
        waitpid(pids[k], &status, 0);
        if (k == cmd_count - 1)  // Only set exit status for the last command
        {
            if (WIFEXITED(status))
                last_exit_status = WEXITSTATUS(status);
        }
    }
}

// int main(int ac, char **av, char **env) 
// {
//     while (1) 
//     {
//         char *line = readline(">>> ");
//         if (!line)
//             break;
//         add_history(line);

//         char **array = ft_split(line, ' ');
        
//         if (array)
//         {
//             make_pipe(array, env);
//             free_array(array);
//         }
//         else
//         {
//             fprintf(stderr, "Memory allocation failed\n");
//         }
        
//         free(line);
//     }
//     clear_history();
//     return 0;    
// }