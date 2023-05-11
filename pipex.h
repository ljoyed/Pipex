/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loandrad <loandrad@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:53:40 by loandrad          #+#    #+#             */
/*   Updated: 2023/05/11 17:23:49 by loandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INFILE 0
# define OUTFILE 1

char	*path_join(char *path, char *bin);
int		str_n_cmp(char *str1, char *str2, int n);
int		str_i_chr(char *str, char c);
char	*str_n_dup(char *str, unsigned int n);
char	**str_split(char *str, char sep);

#endif