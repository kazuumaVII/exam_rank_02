
#include <unistd.h>
#include <stdlib.h>

#define BUFF_S 5000

int ft_find_c(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

char *ft_calloc(int c, int l)
{
	int i = 0;
	char *tab;

	if (!(tab = malloc(c * l)))
		return (NULL);
	if (!c || !l)
		return (tab);
	while (i < c * l)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}

char *ft_substr(char *str, int start, int len)
{
	int i = 0;
	char *tab;

	if (!str || start > ft_find_c(str, '\0'))
		return (NULL);
	if (!(tab = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[start] && len)
	{
		tab[i++] = str[start++];
		len--;
	}
	tab[i] = '\0';
	return (tab);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *tab;

	if (s1 && s2)
	{
		if (!(tab = malloc(sizeof(char) * (ft_find_c(s1, '\0') + ft_find_c(s2, '\0') + 1))))
			return (NULL);
		while (s1[i])
		{
			tab[i] = s1[i];
			i++;
		}
		while (s2[j])
		{
			tab[i + j] = s2[j];
			j++;
		}
		free(s1);
		tab[i + j] = '\0';
		return (tab);
	}
	return (NULL);
}

int get_next_line(char **line)
{
	static char *stock;
	char buff[BUFF_S + 1];
	char *tmp;
	int ret;

	if (!line)
		return (-1);
	if (!stock && !(stock = ft_calloc(sizeof(char), 1)))
		return (-1);
	while (ft_find_c(stock, '\n') < 0 && (ret = read(0, buff, BUFF_S)) > 0)
	{
		buff[ret] = '\0';
		stock = ft_strjoin(stock, buff);
	}
	*line = ft_substr(stock, 0, ft_find_c(stock, '\n'));
	if (ft_find_c(stock, '\n') < 0)
	{
		free(stock);
		return (0);
	}
	tmp = stock;
	stock = ft_substr(stock, ft_find_c(stock, '\n') + 1, ft_find_c(stock, '\0'));
	free(tmp);
	return (1);
}
