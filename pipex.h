/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:40 by loandrad          #+#    #+#             */
/*   Updated: 2023/05/23 12:20:49 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define STDIN_FILENO 0
# define STDOUT_FILENO 1

void	free_array(char **array);
char	*mygetenv(char *cmd, char *envp[]);
int		ft_openfile(char *fname, int fdmode);
char	*getcmd(char *cmd, char **envp);
void	ft_error(int type, char *function);
void	ft_childprocess(char *infile, int *pip_fd);
void	ft_parentprocess(char *outfile, int *pip_fd);
void	ft_execute(char *cmd, char **envp);
char	**ft_free_splitarray(int j, char **des);
char	**ft_split_pipex(char *s);
void	ft_fork_this(char **argv, char **envp);
void	ft_free_all(char **splitcmd, char *cmd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif
