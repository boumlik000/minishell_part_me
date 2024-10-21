#include "minishell.h"

void free_arr(char **arr)
{
    int i = -1;
    while (arr && arr[++i])
    {
        free(arr[i]);
    }
    free(arr);
}

