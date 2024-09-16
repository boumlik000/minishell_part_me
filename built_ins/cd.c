/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:33:25 by mboumlik          #+#    #+#             */
/*   Updated: 2024/09/16 13:55:44 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//to look for =CHDIR/gentenv/getcwd/

int my_setenv(const char *name, const char *value, int overwrite) {
    // Get the current environment variable
    char *current = getenv(name);

    // If the environment variable exists and overwrite is set to 0, do nothing
    if (current && !overwrite) {
        return 0;
    }

    // Calculate the length needed for the new environment string "NAME=VALUE"
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    size_t env_len = name_len + value_len + 2; // Extra 2 for '=' and '\0'

    // Allocate space for the new environment variable
    char *env_var = malloc(env_len);
    if (!env_var) {
        perror("malloc");
        return -1;
    }

    // Construct the new environment variable "NAME=VALUE"
    strcpy(env_var, name);  // Copy the name
    strcat(env_var, "=");   // Append '='
    strcat(env_var, value); // Append the value

    // Add the new environment variable to the environment list using putenv
    if (putenv(env_var) != 0) {
        perror("putenv");
        free(env_var);  // Free the memory if putenv fails
        return -1;
    }

    // Memory for env_var should NOT be freed because putenv does not copy the string,
    // it just adds it directly to the environment.

    return 0;
}
void command_not_found(char *cmd) {
    ft_putstr_fd("minishell: command not found: ", 2);  // 2 is the file descriptor for stderr
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd("\n", 2);
}
int cd_(char **args)
{
    char *path;
    char cwd[PATH_MAX];
    char new_path[PATH_MAX];
    
    printf("%zu",ft_strlen(args[0]));
    if (ft_strlen(args[0]) != 2)
    {
        
        command_not_found(args[0]);
        // return 1;
    }
    
    // If no argument is given or the argument is NULL, change to the home directory
    if (!args[1] || args[1][0] == '\0')
    {
        path = getenv("HOME");
        if (!path)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return 1;
        }
    }
    else
    {
        path = args[1];
    }

    // Handle ~ as home directory
    if (path[0] == '~' && (path[1] == '/' || path[1] == '\0'))
    {
        char *home = getenv("HOME");
        if (!home)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return 1;
        }
        ft_strlcpy(new_path, home, PATH_MAX);
        ft_strlcat(new_path, path + 1, PATH_MAX);
        path = new_path;
    }
    // Handle relative paths
    else if (path[0] != '/')
    {
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            ft_putstr_fd("cd: Error getting current directory\n", 2);
            return 1;
        }
        ft_strlcpy(new_path, cwd, PATH_MAX);
        ft_strlcat(new_path, "/", PATH_MAX);
        ft_strlcat(new_path, path, PATH_MAX);
        path = new_path;
    }

    // Try changing the directory
    if (chdir(path) != 0)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        return 1;
    }

    // Update PWD environment variable
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (my_setenv("PWD", cwd, 1) != 0)
        {
            ft_putstr_fd("cd: Error updating PWD environment variable\n", 2);
            return 1;
        }
    }
    else
    {
        ft_putstr_fd("cd: Error retrieving new current directory\n", 2);
        return 1;
    }

    return 0;
}
