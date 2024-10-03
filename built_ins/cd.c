/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:33:25 by mboumlik          #+#    #+#             */
/*   Updated: 2024/10/02 12:48:54 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//to look for =CHDIR/gentenv/getcwd/

void update_env_var(t_shell *shell, const char *key, const char *value)
{
    t_env *current;
    t_env *new_node;
    
    if (!shell || !key || !value)
        return;

    current = shell->env;
    
    // Search for existing key
    while (current)
    {
        if (current->key && ft_strncmp(current->key, key,-1) == 0)
        {
            // Free old value and update with new one
            if (current->value)
                free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    
    // If key doesn't exist, create new node
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return;
    
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = shell->env;
    shell->env = new_node;
}

char *get_env_value(t_env *env, const char *key)
{
    t_env *current;
    
    if (!env || !key)
        return NULL;

    current = env;
    while (current)
    {
        if (current->key && ft_strncmp(current->key, key,-1) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

int cd_(char **args, t_shell *shell)
{
    char *path;
    char cwd[PATH_MAX];
    char old_cwd[PATH_MAX];
    char new_path[PATH_MAX];    

    if (!shell)
        return 1;

    // Store the current directory as OLD_PWD
    if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
    {
        ft_putstr_fd("cd: Error getting current directory\n", 2);
        return 1;
    }

    // If no argument is given or the argument is NULL, change to the home directory
    if (!args[1] || args[1][0] == '\0')
    {
        path = get_env_value(shell->env, "HOME");
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
        char *home = get_env_value(shell->env, "HOME");
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

    // Update PWD and OLDPWD environment variables
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        update_env_var(shell, "OLDPWD", old_cwd);
        update_env_var(shell, "PWD", cwd);
    }
    else
    {
        ft_putstr_fd("cd: Error retrieving new current directory\n", 2);
        return 1;
    }

    return 0;
}
