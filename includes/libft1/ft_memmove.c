/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:10:15 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/06 13:53:09 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;

	source = (const char *)src;
	destination = (char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (destination > source)
	{
		while (n-- > 0)
			destination[n] = source[n];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
// int main()
// {
// 	char c[] = "hello world";
// 	char *x = ft_memmove(c,c+5,6);
// 	printf("%s",x);	
// 	return 0;
// }