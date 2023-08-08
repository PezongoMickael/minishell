/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:32:46 by rel-fila          #+#    #+#             */
/*   Updated: 2023/08/06 16:32:47 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_check_separator(char const *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			j++;
		}
		i++;
	}
	return (j + 1);
}

static void	ft_free(char **strs, int i, char *str)
{
	int	y;

	y = 0;
	free(str);
	while (y < i)
		free(strs[y++]);
	free(strs);
}

char	*copy_worddup(char *str, char c, int *j)
{
	int		len;
	char	*s;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	s = malloc(sizeof(char) * (len + 1));
	len = 0;
	while (*str != c && *str)
	{
		s[len] = *str;
		len++;
		str++;
		(*j)++;
	}
	s[len] = '\0';
	return (s);
}

char	**ft_initialize_strs(char **strs, char *str, char c)
{
	size_t	i;
	size_t	len;
	int		j;

	i = 0;
	j = 0;
	len = ft_check_separator(str, c);
	while (*str && i < len)
	{
		strs[i] = copy_worddup(str + j, c, &j);
		if (!strs[i])
		{
			ft_free(strs, i, str);
			return (NULL);
		}
		while (str[j] == c && str[j])
			j++;
		i++;
	}
	strs[i] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	*str;

	if (!s)
		return (NULL);
	str = ft_strtrim(s, &c);
	if (!str)
		return (NULL);
	strs = (char **)malloc(sizeof(char **) * (ft_check_separator(str, c) + 1));
	if (!strs)
		return (NULL);
	strs = ft_initialize_strs(strs, str, c);
	if (!strs)
		return (NULL);
	free(str);
	return (strs);
}
