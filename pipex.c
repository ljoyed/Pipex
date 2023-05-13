/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:36 by loandrad          #+#    #+#             */
/*   Updated: 2023/05/13 13:54:18 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK) == -1)
		{	
			perror("pipex ");
			strerror(errno);
		}
		return (open(filename, O_RDONLY));
	}
	else
	{
		if (access(filename, F_OK) == -1)
			exit(EXIT_FAILURE);
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	}
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_n_cmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_i_chr(path, ':') > -1)
	{
		dir = str_n_dup(path, str_i_chr(path, ':'));
		bin = path_join(dir, cmd);
		if (!bin)
			free(bin);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_i_chr(path, ':') + 1;
	}
	return (cmd);
}

void	exec_func(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = str_split(cmd, ' ');
	if (!args)
		free(args);
	if (str_i_chr(args[0], '/') > -1)
		path = args[0];
	else
		path = get_path(args[0], env);
	execve(path, args, env);
	perror("pipex ");
	strerror(errno);
	exit(EXIT_FAILURE);
}

void	processes(char *cmd, char **env, int file_in)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		waitpid(pid, &status, WNOHANG);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		if (file_in == STDIN)
			exit(1);
		else
			exec_func(cmd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	int	file_in;
	int	file_out;

	if (ac == 5)
	{
		file_in = openfile(av[1], INFILE);
		file_out = openfile(av[4], OUTFILE);
		dup2(file_in, STDIN);
		dup2(file_out, STDOUT);
		processes(av[2], env, file_in);
		exec_func(av[3], env);
	}
	else
		write(STDERR, "Invalid number of arguments.\n", 29);
	return (1);
}
