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
    char **cmd_args = NULL;
    int out_fd = -1;
    int in_fd = -1;
    int append_mode = 0;
    
    // Find redirections and command length
    int i = 0;
    int cmd_len = 0;
    int out_pos = -1;
    int in_pos = -1;
    
    while (args[i])
    {
        if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
        {
            if (out_pos == -1)
                out_pos = i;
        }
        else if (ft_strcmp(args[i], "<") == 0)
        {
            if (in_pos == -1)
                in_pos = i;
        }
        else if (out_pos == -1 && in_pos == -1)
        {
            cmd_len++;
        }
        i++;
    }
    
    // Prepare command arguments
    cmd_args = malloc(sizeof(char *) * (cmd_len + 1));
    if (!cmd_args)
        exit(1);
    
    for (i = 0; i < cmd_len; i++)
        cmd_args[i] = ft_strdup(args[i]);
    cmd_args[cmd_len] = NULL;

    // Handle input redirection
    if (in_pos != -1)
    {
        if (!args[in_pos + 1])
        {
            ft_putstr_fd("minishell: syntax error near unexpected token '<'\n", 2);
            free_array(cmd_args);
            exit(1);
        }
        
        in_fd = open(args[in_pos + 1], O_RDONLY);
        if (in_fd == -1)
        {
            perror("minishell");
            free_array(cmd_args);
            exit(1);
        }
        
        if (dup2(in_fd, STDIN_FILENO) == -1)
        {
            perror("minishell");
            close(in_fd);
            free_array(cmd_args);
            exit(1);
        }
        close(in_fd);
    }

    // Handle output redirection
    if (out_pos != -1)
    {
        if (!args[out_pos + 1])
        {
            ft_putstr_fd("minishell: syntax error near unexpected token '>' or '>>'\n", 2);
            free_array(cmd_args);
            exit(1);
        }
        
        // Check for append mode
        if (ft_strcmp(args[out_pos], ">>") == 0)
            append_mode = 1;
        
        // Open file based on mode
        if (append_mode)
            out_fd = open(args[out_pos + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            out_fd = open(args[out_pos + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        
        if (out_fd == -1)
        {
            perror("minishell");
            free_array(cmd_args);
            exit(1);
        }
        
        if (dup2(out_fd, STDOUT_FILENO) == -1)
        {
            perror("minishell");
            close(out_fd);
            free_array(cmd_args);
            exit(1);
        }
        close(out_fd);
    }
    
    // Check for builtin
    for (i = 0; builtins[i]; i++)
    {
        if (ft_strcmp(cmd_args[0], builtins[i]) == 0)
        {
            is_builtin = 1;
            break;
        }
    }
    
    // Execute command
    if (is_builtin)
    {
        exec_built_in(cmd_args, shell);
        free_array(cmd_args);
        exit(last_exit_status);
    }
    
    char *cmd_path = find_command(cmd_args[0], shell->env_array);
    if (cmd_path)
    {
        execve(cmd_path, cmd_args, shell->env_array);
        free(cmd_path);
    }
    
    ft_putstr_fd("minishell: command not found: ", 2);
    ft_putstr_fd(cmd_args[0], 2);
    ft_putstr_fd("\n", 2);
    
    free_array(cmd_args);
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

    // Count pipes
    while (args[i])
    {
        if (ft_strcmp(args[i], "|") == 0)
            pipe_count++;
        i++;
    }
    cmd_count = pipe_count + 1;

    // Create pipes
    for (int j = 0; j < pipe_count; j++)
    {
        if (pipe(pipes[j]) == -1)
        {
            perror("pipe");
            exit(1);
        }
    }

    // Execute commands
    i = 0;
    for (int cmd_index = 0; cmd_index < cmd_count; cmd_index++)
    {
        // Count arguments for current command
        int cmd_len = 0;
        while (args[i + cmd_len] && ft_strcmp(args[i + cmd_len], "|") != 0)
            cmd_len++;
        
        // Create array for current command
        char **current_cmd = malloc(sizeof(char *) * (cmd_len + 1));
        if (!current_cmd)
        {
            perror("malloc");
            exit(1);
        }
        
        for (int j = 0; j < cmd_len; j++)
            current_cmd[j] = ft_strdup(args[i + j]);
        current_cmd[cmd_len] = NULL;

        pid_t pid = fork();
        if (pid == 0)
        {
            // Child process
            if (cmd_index > 0)
                dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
            if (cmd_index < cmd_count - 1)
                dup2(pipes[cmd_index][1], STDOUT_FILENO);

            // Close all pipe fds
            for (int j = 0; j < pipe_count; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execute_command(current_cmd, shell);
            exit(1);
        }
        
        pids[cmd_index] = pid;
        free_array(current_cmd);
        i += cmd_len + 1;
    }

    // Close all pipe fds in parent
    for (int j = 0; j < pipe_count; j++)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }

    // Wait for all child processes
    for (int k = 0; k < cmd_count; k++)
    {
        int status;
        waitpid(pids[k], &status, 0);
        if (k == cmd_count - 1)
            if (WIFEXITED(status))
                last_exit_status = WEXITSTATUS(status);
    }
}

