/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:41:46 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/06 16:48:29 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
// int main()
// {
// 	char *c[] ={"hello ","charaf "};
// 	int i = 0;
// 	int fd = open("mohamed.txt",O_CREAT | O_RDWR, 0777);
// 	while (i <= 1)
// 	{
// 		ft_putendl_fd(c[i],fd);
// 		i++;
// 	}
// 	return 0;
// }