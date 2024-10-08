/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:14:22 by mboumlik          #+#    #+#             */
/*   Updated: 2024/10/05 11:09:31 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_garbage	*ft_grapnew(void* content)
{
	t_garbage	*node;

	node = malloc(sizeof(t_garbage));
	if (!node)
		return (NULL);
	node->ptr = content;
	node->next = NULL;
	return (node);
}

void	ft_grapadd_front(t_garbage **lst, t_garbage *new)
{
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize(t_garbage **lst)
{
	int		i;
	t_garbage	*node;

	i = 0;
	node = *lst;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}

t_garbage	*ft_graplast(t_garbage *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_grapadd_back(t_garbage **lst, t_garbage *new)
{
	t_garbage	*node;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
	new->next = NULL;
}

// free the linked list allocated by the garbage collector
// garbage: a parameter bla bla


void ft_garbage_free(t_garbage *garbage)
{
    t_garbage *current = garbage;
    t_garbage *next;

    while (current)
    {
        next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
}

// void cleanup_readline()
// {
//     // rl_clear_history();
//     // rl_free_line_state();
//     // rl_cleanup_after_signal();
// }