/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:36 by loandrad          #+#    #+#             */
/*   Updated: 2023/05/23 12:10:54 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(char *cmd, char **envp)
{
	char	**splitcmd;
	char	*cmdline;

	splitcmd = ft_split_pipex(cmd);
	cmdline = getcmd(splitcmd[0], envp);
	if (ft_strncmp(cmd, "", ft_strlen(cmd)) == 0)
	{
		if (execve(cmdline, splitcmd, 0) == -1)
		{
			ft_putendl_fd("pipex: permission denied: ", 2);
			ft_free_all(splitcmd, cmdline);
			exit(1);
		}
	}
	else
	{
		if (execve(cmdline, splitcmd, 0) == -1)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(splitcmd[0], 2);
			free(cmdline);
			exit(127);
		}
	}
}

void	ft_childprocess(char *infile, int *pip_fd)
{
	int	fdin;

	fdin = ft_openfile(infile, STDIN);
	if (dup2(fdin, STDIN) == -1)
		ft_error(1, "dup2");
	if (close(pip_fd[0]) < 0)
		ft_error(1, "close");
	if (dup2(pip_fd[1], STDOUT_FILENO) == -1)
		ft_error(1, "dup2");
	if (close(fdin) < 0)
		ft_error(1, "close");
	if (close(pip_fd[1]) < 0)
		ft_error(1, "close");
}

void	ft_parentprocess(char *outfile, int *pip_fd)
{
	int	fdout;

	fdout = ft_openfile(outfile, STDOUT);
	if (dup2(fdout, STDOUT) == -1)
		ft_error(1, "dup2");
	if (close(pip_fd[1]) < 0)
		ft_error(1, "close");
	if (dup2(pip_fd[0], STDIN_FILENO) == -1)
		ft_error(1, "dup2");
	if (close(fdout) < 0)
		ft_error(1, "close");
	if (close(pip_fd[0]) < 0)
		ft_error(1, "close");
}

void	ft_fork_this(char **argv, char **envp)
{
	pid_t	pid;
	int		pip_fd[2];

	if (pipe(pip_fd) == -1)
		ft_error(1, "pipe not created");
	pid = fork();
	if (pid == -1)
		ft_error(1, "fork");
	if (pid == 0)
	{
		ft_childprocess(argv[1], pip_fd);
		ft_execute(argv[2], envp);
	}
	else
	{
		waitpid(-1, NULL, WNOHANG);
		ft_parentprocess(argv[4], pip_fd);
		ft_execute(argv[3], envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;

	if (argc != 5)
	{
		ft_putendl_fd("./pipex infile cmd1 cmd2 outfile", STDERR);
		exit(1);
	}
	pid = fork();
	if (pid < 0)
		ft_error(1, "fork");
	if (pid == 0)
		ft_fork_this(argv, envp);
	else
		waitpid(-1, NULL, WNOHANG);
	return (0);
}
