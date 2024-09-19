//to learn waitpid
//to learn access
//to learn execve
//to learn readline


#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "../includes/libft/libft.h"
#include <fcntl.h>

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
    char *path = NULL;
    char *path_copy = NULL;
    char *dir = NULL;
    char *full_path = NULL;

    // Find PATH in environment variables
    for (int i = 0; env[i]; i++)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            path = env[i] + 5;
            break;
        }
    }

    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2);
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

void make_pipe(char **args, char **env)
{
    if (!args)
        return;

    int i = 0;
    int pipe_count = 0;
    pid_t pids[1024]; // Assuming a maximum of 1024 piped commands

    while (args[i])
    {
        int j = i;
        while (args[j] && strcmp(args[j], "|") != 0)
            j++;
        int has_pipe = (args[j] && strcmp(args[j], "|") == 0);
        printf("[%d][%d]||",has_pipe,j);
        int fd[2];
        if (has_pipe && pipe(fd) == -1)
        {
            perror("pipe");
            exit(1);
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        if (pid == 0)
        {
            if (has_pipe)
            {
                args[j] = NULL;
                set_dup(has_pipe, fd, STDOUT_FILENO);
            }
            char *cmd_path = find_command(args[i], env);
            if (cmd_path)
            {
                execve(cmd_path, &args[i], env);
                free(cmd_path);
            }
            perror("execve");
            exit(1);
        }
        else
        {
            pids[pipe_count++] = pid;
            if (has_pipe)
            {
                close(fd[1]);
                if (dup2(fd[0], STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
                close(fd[0]);
                i = j + 1;
            }
            else
            {
                i = j;
                break;
            }
        }
    }
    // Wait for all child processes to complete
    int k = -1;
    while (++k < pipe_count)
    {
        int status;
        waitpid(pids[k],&status,0);
    }

    // Reset standard input to the terminal
    if (pipe_count > 0)
    {
        int fd_terminal = open("/dev/tty", O_RDONLY);
        if (fd_terminal == -1)
        {
            perror("open /dev/tty");
            exit(1);
        }
        if (dup2(fd_terminal, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(1);
        }
        close(fd_terminal);
    }
}

int main(int ac, char **av, char **env) 
{
    while (1) 
    {
        char *line = readline(">>> ");
        if (!line)
            break;
        add_history(line);

        char **array = ft_split(line, ' ');
        
        if (array)
        {
            make_pipe(array, env);
            free_array(array);
        }
        else
        {
            fprintf(stderr, "Memory allocation failed\n");
        }
        
        free(line);
    }
    clear_history();
    return 0;    
}