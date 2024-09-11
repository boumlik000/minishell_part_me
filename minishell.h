#ifndef MINISHELL_H
#define MINISHELL_H


typedef struct s_garbage
{
    void *ptr;
    struct s_garbage *next;

}   t_garbage;

#include "./includes/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

extern int last_exit_status;

int exec_cmd(char **arr);
int exec_built_in(char **arr);
void free_arr(char **arr);
int echo_(char **args);
int exit_(char **args);
int pwd_();


// garbage collector utiles

void	ft_grapadd_back(t_garbage **lst, t_garbage *new);
t_garbage	*ft_graplast(t_garbage *lst);
int	ft_lstsize(t_garbage **lst);
void	ft_grapadd_front(t_garbage **lst, t_garbage *new);
t_garbage	*ft_grapnew(void* content);
void ft_garbage_free(t_garbage *garbage);


#endif