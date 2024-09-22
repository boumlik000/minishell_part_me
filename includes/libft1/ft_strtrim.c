/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:46:17 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/05 21:07:00 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char t, char *set)
{
	int	y;

	y = 0;
	while (set[y])
	{
		if (set[y] == t)
			return (1);
		y++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		x;
	int		len;
	char	*result;

	x = 0;
	if (!s1 || !set)
	{
		if (!set)
			return ((char *)s1);
		return (NULL);
	}
	while (s1[x] && check(s1[x], (char *)set))
		x++;
	len = ft_strlen(s1);
	while (len > 0 && s1[len - 1] && check(s1[len - 1], (char *)set) && len > x)
		len--;
	if (len <= x)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (len - x + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1 + x, len - x);
	result[len - x] = '\0';
	return (result);
}
