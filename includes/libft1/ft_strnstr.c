/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:05:43 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/02 17:46:53 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *str1, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str && len == 0)
		return ((char *)str);
	if (!str1[i])
		return ((char *)str);
	while (len > i && str[i])
	{
		while (str[i + j] == str1[j] && str[i + j] && len > (i + j))
			j++;
		if (!str1[j])
			return ((char *)(str + i));
		j = 0;
		i++;
	}
	return (NULL);
}
