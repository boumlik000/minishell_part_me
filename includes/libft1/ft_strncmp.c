/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:05:04 by mboumlik          #+#    #+#             */
/*   Updated: 2024/10/05 11:07:32 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    unsigned char *x;
    unsigned char *y;

    // Add null check
    if (!s1 || !s2)
        return -1;

    x = (unsigned char *)s1;
    y = (unsigned char *)s2;
    i = 0;
    
    // Handle case where n is SIZE_MAX (-1 as size_t)
    if (n == (size_t)-1)
    {
        while (x[i] && y[i] && x[i] == y[i])
            i++;
        return x[i] - y[i];
    }
    
    // Normal case
    while (i < n && (x[i] || y[i]))
    {
        if (x[i] != y[i])
            return x[i] - y[i];
        i++;
    }
    return 0;
}
