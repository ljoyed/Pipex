/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:32 by loandrad          #+#    #+#             */
/*   Updated: 2023/05/23 12:10:51 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int type, char *function)
{
	ft_putstr_fd("error, ", 2);
	ft_putstr_fd(function, 2);
	ft_putendl_fd(" could not execute", 2);
	exit(type);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_openfile(char *fname, int fdmode)
{
	int	fd;

	if (fdmode == 0)
	{
		fd = open(fname, O_RDONLY, 0777);
		if (fd == -1)
		{
			perror("pipex: infile");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (fd == -1)
		{
			perror("pipex: outfile");
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

void	ft_free_all(char **splitcmd, char *cmd)
{
	if (splitcmd)
		free_array(splitcmd);
	if (cmd)
		free(cmd);
}
