/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:47:33 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/06 19:20:57 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*x;

	if (size && count > __SIZE_MAX__ / size)
		return (NULL);
	i = count * size;
	x = malloc(i);
	if (!x)
		return (NULL);
	ft_bzero(x, i);
	return (x);
}
// int main()
// {
// 	int i = 0,j = 0;
// 	char c[]= "hello world";

// 	char *p = (char *)ft_calloc(strlen(c) +1, sizeof(char));
// 	while (i < strlen(c))
// 	{
// 		p[i] = c[i];
// 		printf("%c",p[i]);
// 		i++;
// 	}
// 	free(p);

// 	return (0);
// }
