/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:25:08 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/06 17:54:48 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_allocation(size_t n)
{
	char	*p;

	p = (char *)malloc(sizeof(char) * (n + 1));
	if (p == NULL)
		return (NULL);
	return (p);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	n;
	char	*string;

	if (!s || !f)
		return (NULL);
	string = str_allocation(ft_strlen(s));
	if (!string)
		return (NULL);
	n = 0;
	while (s[n])
	{
		string[n] = f(n, s[n]);
		n++;
	}
	string[n] = '\0';
	return (string);
}
