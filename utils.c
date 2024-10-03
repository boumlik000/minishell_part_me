/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:13:55 by mboumlik          #+#    #+#             */
/*   Updated: 2024/10/01 13:53:04 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void int_to_str(int num, char *str)
{
    int i = 0;
    int is_negative = 0;
    
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    
    if (num < 0)
    {
        is_negative = 1;
        num = -num;
    }
    
    while (num != 0)
    {
        int digit = num % 10;
        str[i++] = digit + '0';
        num = num / 10;
    }
    
    if (is_negative)
        str[i++] = '-';
    
    str[i] = '\0';
    
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


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

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
char    *ft_strncpy(char *dest,  char *src, unsigned int n)
{
        unsigned int i;
        i = 0;
    while (i < n && src[i] != '\0') //copia o src para o dest
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n) //preenche o resto do dest com null
    {
        dest[i] = '\0';
        i++;
    }
        
    return dest;    
}