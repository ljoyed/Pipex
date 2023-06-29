/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:57:24 by loandrad          #+#    #+#             */
/*   Updated: 2023/05/23 12:16:32 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_quote_count(int *index, char *str)
{
	int	counter;

	counter = 0;
	if (str[(*index)] == 34)
	{
		(*index)++;
		while (str[(*index)] != 34 && str[(*index)])
			(*index)++;
		if (str[(*index) + 1] != '\0')
			counter++;
	}
	if (str[(*index)] == 39)
	{
		(*index)++;
		while (str[(*index)] != 39 && str[(*index)])
			(*index)++;
		if (str[(*index) + 1] != '\0')
			counter++;
	}
	return (counter);
}

static int	ft_char_count(char *str)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	while (str[index])
	{
		if (str[index] == ' ')
		{
			while (str[index] == ' ' && str[index] != '\0')
				index++;
			counter++;
		}
		counter += ft_quote_count(&index, str);
		index++;
	}
	return (counter);
}

static void	ft_count(char *str, size_t *index, size_t *len)
{
	while (str[(*index)] == ' ' && str[(*index)] != '\0')
		(*index)++;
	(*len) = (*index);
	if (str[(*len)] == 34)
	{
		(*len)++;
		while (str[(*len)] != 34 && str[(*len)] != '\0')
			(*len)++;
		(*index)++;
	}
	else if (str[(*len)] == 39)
	{
		(*len)++;
		while (str[(*len)] != 39 && str[(*len)] != '\0')
			(*len)++;
		(*index)++;
	}
	else
	{
		while (str[(*len)] != ' ' && str[(*len)] != '\0')
			(*len)++;
	}
}

static char	**make_split(char *cmd)
{
	size_t			i;
	size_t			len;
	char			**split_string;
	int				index;

	index = 0;
	i = 0;
	if (cmd == 0)
		return (NULL);
	split_string = malloc (sizeof(char *) * (ft_char_count(cmd) + 2));
	if (split_string == NULL)
		return (NULL);
	while (index < (ft_char_count(cmd) + 1))
	{
		ft_count(cmd, &i, &len);
		split_string[index] = ft_substr(cmd, i, len - i);
		if (!split_string[index])
			return (ft_free_splitarray(index, split_string));
		index++;
		i = len;
	}
	split_string[index] = NULL;
	return (split_string);
}

char	**ft_split_pipex(char *cmd)
{
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (cmd[index])
	{
		if (cmd[index] == 34 || cmd[index] == 39)
			count++;
		index++;
	}
	if (count % 2 != 0)
		ft_error(0, "pipex");
	return (make_split(cmd));
}
