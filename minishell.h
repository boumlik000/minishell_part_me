#ifndef MINISHELL_H
#define MINISHELL_H

#include "./includes/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int exec_cmd(char **arr);
int exec_built_in(char **arr);
void free_arr(char **arr);
int echo_(char **args);

int pwd_();

#endif