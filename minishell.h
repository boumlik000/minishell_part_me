#ifndef MINISHELL_H
#define MINISHELL_H


typedef struct s_garbage
{
    void *ptr;
    struct s_garbage *next;

}   t_garbage;

typedef struct s_env
{
 char   *value;
 char      *key;
 struct s_env *next;
}    t_env;

typedef struct  s_shell
{
    t_env *env;
    t_garbage *garbage;
}t_shell;



#include "./includes/libft1/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>



extern int last_exit_status;

int exec_cmd(char **arr,t_shell *shell);
int exec_built_in(char **arr,t_shell *shell);

void env_(t_env *env);
void free_arr(char **arr);
int echo_(char **args);
int exit_(char **args);
int pwd_();
int cd_(char **args);


//env
t_env *create_node(char *env);
t_env *get_last_node(t_env *head);
void add_back(t_env **head ,t_env *new_content);
t_env *cp_env_in_liste(char **env, t_shell *shell);

// garbage collector utiles
void free_env(t_shell *t_shell);

void	ft_grapadd_back(t_garbage **lst, t_garbage *new);
t_garbage	*ft_graplast(t_garbage *lst);
int	ft_lstsize(t_garbage **lst);
void	ft_grapadd_front(t_garbage **lst, t_garbage *new);
t_garbage	*ft_grapnew(void* content);
void ft_garbage_free(t_garbage *garbage);
// void cleanup_readline();
// int	ft_strcmp(const char *s1,const char *s2);

// 

#endif