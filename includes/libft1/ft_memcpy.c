/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:21:50 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/07 09:21:55 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;
	size_t			i;

	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	if (dest == src)
		return (dest);
	if (destination == NULL && source == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char c[] = "hello world";
// 	char b[] = "moha";
// 	ft_memcpy(b + 4, c, 12);
// 	int i = 0;
// 	while (b[i])
// 	{
// 		if (i == 4)
// 			printf("%c", ' ');
// 		printf("%c", b[i]);
// 		i++;
// 	}

// 	return (0);
// }