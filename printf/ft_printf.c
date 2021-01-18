/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:00:31 by frfrance          #+#    #+#             */
/*   Updated: 2020/01/23 15:46:46 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_atoi(const char *str, int *i)
{
	int j = 0;

	while (*str && *str >= '0' && *str <= '9')
	{
		j = j * 10 + (*str - 48);
		str++;
		*i += 1;
	}
	return (j);
}

int ft_itoa(char *buff, unsigned int nb, char *base, int base_l)
{
	int i = 0;
	unsigned int val = nb;

	buff[4999 - i++] = base[val % base_l];
		while ((val /= base_l) > 0)
			buff[4999 - i++] = base[val % base_l];
	return (i);
}

int ft_printf(char *str, ...)
{
	int i = -1;
	int nb = 0;
	int len = 0;
	int w = 0;
	int s = 0;
	int p = -1;
	va_list arg;
	char buff[5000];
	char *ptr;\

	va_start(arg, str);
	while (str[++i])
	{
		if (str[i] != '%' && ++len)
			write(1, &str[i], 1);
		else
		{
			i++;
			while (str[i])
			{
				if (str[i] >= '0' && str[i] <= '9')
					w = ft_atoi(&str[i], &i);
				else if (str[i] == '.' && i++)
					p = ft_atoi(&str[i], &i);
				else
					break;
			}
			if (str[i] == 'd')
			{
				nb = va_arg(arg, int);
				if (nb == 0 && p >= 0)
					s = 0;
				else
					s = ft_itoa(buff, nb < 0 ? -nb : nb, "0123456789", 10);
				if (p > -1)
					while (s < p)
						buff[4999 - s++] = '0';
				if (nb < 0)
					buff[4999 - s++] = '-';
				while (s < w)
					buff[4999 - s++] = ' ';
				write(1, &buff[4999 - s + 1], s);
			}
			if (str[i] == 'x')
			{
				nb = va_arg(arg, unsigned int);
				if (nb == 0 && p >= 0)
					s = 0;
				else
					s = ft_itoa(buff, nb, "0123456789abcdef", 16);
				if (p > -1)
					while (s < p)
						buff[4999 - s++] = '0';

				while (s < w)
					buff[4999 - s++] = ' ';
				write(1, &buff[4999 - s + 1], s);
			}
			if (str[i] == 's')
			{
				ptr = va_arg(arg, char*);
				while (ptr[s])
					s++;
				s = p > -1 && p < s ? p : s;
				while (w-- > s)
				{
					write(1, " ", 1);
					len++;
				}
				write(1, ptr, s);
			}
		}
	}
	len += s;
	va_end(arg);
	return (len);
}
/*
 int main(void)
{
	// printf("ret %d\n", printf("%5d\n", 8));
	// printf("ret %d\n", ft_printf("%5d\n", 8));
	// printf("ret %d\n", printf("%.5d\n", 8));
// 	// printf("ret %d\n", ft_printf("%.5d\n", 8));
// 	// printf("ret %d\n", printf("%.d\n", 8));
// 	// printf("ret %d\n", ft_printf("%.d\n", 8));
// 	// printf("ret %d\n", printf("%5d\n", 0));
// 	// printf("ret %d\n", ft_printf("%5d\n", 0));
// 	// printf("ret %d\n", printf("%.8d\n", 0));
// 	// printf("ret %d\n", ft_printf("%.8d\n", 0));
// 	// printf("ret %d\n", printf("%18d\n", 8));
// 	// printf("ret %d\n", ft_printf("%18d\n", 8));
// 	// //printf("ret %d\n", printf("%18d\n", -8));
// 	// // printf("ret %d\n", ft_printf("%18d\n", -8));
// 	// // printf("ret %d\n", printf("%.5d\n", -8));
// 	// // printf("ret %d\n", ft_printf("%.5d\n", -8));
// 	// // printf("ret %d\n", printf("%.d\n", -8));
// 	// // printf("ret %d\n", ft_printf("%.d\n", -8));
// 	// // printf("ret %d\n", printf("%.d\n", 8));
// 	// // printf("ret %d\n", ft_printf("%.d\n", 8));
// 	// printf("ret %d\n", printf("%5x\n", 15));
// 	// printf("ret %d\n", ft_printf("%5x\n", 15));
// 	// printf("ret %d\n", printf("%.5x\n", 15));
// 	// printf("ret %d\n", ft_printf("%.5x\n", 15));
// 	// printf("ret %d\n", printf("%.x\n", 15));
// 	// printf("ret %d\n", ft_printf("%.x\n", 15));
	printf("ret %d\n", printf("%s\n", "bonjour"));
	printf("ret %d\n", ft_printf("%s\n", "bonjour"));
	printf("ret %d\n", printf("%.5s\n", "bonjour"));
	printf("ret %d\n", ft_printf("%.5s\n", "bonjour"));
	printf("ret %d\n", printf("%5s\n", "bonjour"));
	printf("ret %d\n", ft_printf("%5s\n", "bonjour"));
	printf("ret %d\n", printf("%s\n", ""));
	printf("ret %d\n", ft_printf("%s\n", ""));
 	return (0);
 }

*/
