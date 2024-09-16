/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:29:48 by mboumlik          #+#    #+#             */
/*   Updated: 2024/09/16 12:26:34 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    search_in(char *str, char c)
{
    int    i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (i);
}

t_env *create_node(char *env)
{
    int i = 0;
    t_env *lst;
    char *key ;
    char *value;
    lst = malloc(sizeof(t_env));
    key = ft_substr(&env[i],0,search_in(env,'='));
    lst->key = key;
    value = ft_substr(&env[i],search_in(env,'=') + 1,ft_strlen(env));
    lst->value = value;
    lst->next = NULL;
    return lst;
}

t_env *get_last_node(t_env *head)
{
    if (!head)
        return NULL;
    while(head->next)
        head = head->next;
    return head;
}

void add_back(t_env **head ,t_env *new_content)
{
    t_env *last;
    if(!head || !new_content)
        return;
    if(*head)
    {
        last = get_last_node(*head);
        last->next = new_content;
    }
    else
        *head = new_content;
}


void free_env(t_shell *shell)
{
    t_env *current = shell->env;
    t_env *next;

    while (current)
    {
        next = current->next;
        free(current->value);
        free(current->key);
        free(current);
        current = next;
    }
    shell->env = NULL;
}

t_env *cp_env_in_liste(char **env, t_shell *shell)
{
    int i = 0;
    t_env *lst = NULL;
    t_env *ptr;

    while (env[i])
    {
        ptr = create_node(env[i]);
        if (!ptr)
        {
            free_env(shell);
            return NULL;
        }
        add_back(&lst, ptr);
        i++;
    }
    return lst;
}

void env_(t_env *env)
{
    if (!env)
        return ;
    t_env *current = env;
    while (current != NULL)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}