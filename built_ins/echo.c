/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:49:04 by mboumlik          #+#    #+#             */
/*   Updated: 2024/09/06 09:49:36 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo_(char **args)
{
    int i = 1;
    int newline = 1;
    if (args[1] && ft_strncmp(args[1], "-n",-1) == 0) {
        newline = 0;
        i++;
    }
    while (args[i]) {
        if (ft_strncmp(args[i], "$?", -1) == 0) {
            char *exit_status_str = ft_itoa(last_exit_status);
            if (exit_status_str)
            {
                ft_putstr_fd(exit_status_str, 1);
                free(exit_status_str);
            }
        } else
            ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', 1);
    return 0;
}
