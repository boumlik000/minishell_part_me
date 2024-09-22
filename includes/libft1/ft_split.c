/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboumlik <mboumlik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:14:34 by mboumlik          #+#    #+#             */
/*   Updated: 2023/12/07 09:58:58 by mboumlik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	words_nbr(const char *str, char s)
{
	int	i;
	int	words_count;
	int	start;

	i = 0;
	words_count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == s)
			i++;
		start = i;
		while (str[i] && str[i] != s)
			i++;
		if (start != i)
			words_count++;
		if (str[i] == '\0')
			return (words_count);
		i++;
	}
	return (words_count);
}

static char	*malloc_word(const char *s, int b, int e)
{
	int		i;
	char	*str;

	str = (char *)malloc((e - b + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (b < e)
	{
		str[i] = s[b];
		i++;
		b++;
	}
	str[i] = '\0';
	return (str);
}

static char	**freefun(char **p, int j)
{
	while (j >= 0)
	{
		free(p[j]);
		j--;
	}
	free(p);
	return (NULL);
}

static char	**list(char **lst, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			k = i;
			while (s[i] && s[i] != c)
				i++;
			lst[j] = malloc_word(s, k, i);
			if (!lst[j])
				return (freefun(lst, j));
			j++;
		}
		else
			i++;
	}
	lst[j] = NULL;
	return (lst);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;

	if (!s)
		return (NULL);
	lst = (char **)malloc((words_nbr(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	return (list(lst, s, c));
}
// int main()
// {
// 	char p[]="    hellom n  ;f     msd     anf    sa      sa world hahaha   ";
// 	char c = ' ';
// 	int i = 0;
// 	char **res = ft_split(p,c);
// 	while (res[i])
// 	{
// 		printf("%s\n",res[i]);
// 		i++;
// 	}
// 	return 0;
// }
