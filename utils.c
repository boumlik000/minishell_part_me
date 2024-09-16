#include "minishell.h"

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

int	ft_strcmp(const char *s1,const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}