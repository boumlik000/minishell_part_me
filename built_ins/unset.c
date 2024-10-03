/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:20:29 by mboumlik          #+#    #+#             */
/*   Updated: 2024/10/02 12:20:44 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_env_name(char *str)
{
    int i;

    if (!str || !str[0] || ft_isdigit(str[0]))
        return (0);
    i = 0;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void remove_env_var(t_env **env, char *key)
{
    t_env *current;
    t_env *prev;

    if (!env || !*env || !key)
        return;
    
    current = *env;
    prev = NULL;

    while (current)
    {
        if (!ft_strncmp(current->key, key, -1))
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            // Note: Depending on your memory management strategy,
            // you might need to free current->key and current->value
            // and add them to your garbage collector
            return;
        }
        prev = current;
        current = current->next;
    }
}

int unset_(char **args, t_shell *shell)
{
    int i;
    int status;

    if (!args || !args[1])
        return (0);  // No arguments, successfully do nothing
    
    status = 0;
    i = 1;
    while (args[i])
    {
        if (!is_valid_env_name(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            status = 1;
        }
        else
            remove_env_var(&shell->env, args[i]);
        i++;
    }
    return (status);
}