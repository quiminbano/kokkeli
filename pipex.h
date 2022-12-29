/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:06:36 by corellan          #+#    #+#             */
/*   Updated: 2022/12/29 16:20:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define FILE_DESCRIPTOR 2 

# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_pipex
{
	int		fdinput;
	int		fdoutput;
	pid_t	pid1;
	char	*path1;
	char	*path2;
	char	*shell;
	char	**cmd1;
	char	**cmd2;
	char	**temp1;
	char	**temp2;
	int		fd1[FILE_DESCRIPTOR];

}t_pipex;

int		ft_pipex(char **argv, char **envp, t_pipex *data);
int		ft_openpipe(int *fd, char *str);
int		ft_forking(int *pid, char *str);
void	ft_free_split(char **str);
int		ft_pipex_cont(char **argv, char **envp, t_pipex *data);
int		ft_identify_route(char **argv, int prog, char ***cmd, char ***temp);
int		ft_error_message(char **argv, char **envp, t_pipex *data);
void	ft_print_error(char **argv, char *shell, int prog);

#endif