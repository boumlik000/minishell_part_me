/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:41:24 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/06 15:15:38 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}
// int main()
// {
// 	char c[] ="alo";int i = 0;
// 	int fd = open("mohamed.txt",O_CREAT | O_RDWR, 0777);
// 	while (c[i])
// 	{
// 		ft_putchar_fd(c[i],fd);
// 		i++;
// 	}

// 	return (0);
// }
