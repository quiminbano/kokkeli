/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:20 by corellan          #+#    #+#             */
/*   Updated: 2023/01/03 11:24:14 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_prepare1(char **argv, char **envp, t_pipex *data)
{
	int	prep2;

	prep2 = 0;
	close(data->fd1[1]);
	dup2(data->fd1[0], STDIN_FILENO);
	close(data->fd1[0]);
	free(data->path1);
	ft_free_split(data->cmd1);
	prep2 = ft_pipex_cont(argv, envp, data);
	return (prep2);
}

static int	ft_run_route1(char **envp, t_pipex *data)
{
	close(data->fd1[0]);
	dup2(data->fdinput, STDIN_FILENO);
	close(data->fdinput);
	dup2(data->fd1[1], STDOUT_FILENO);
	close(data->fd1[1]);
	if (execve((data->path1), data->cmd1, envp) < 0)
	{
		ft_free_split(data->cmd1);
		free(data->path1);
		perror(data->shell);
		free(data->shell);
		return (3);
	}
	return (0);
}

static int	ft_wait_get_path1(char **argv, t_pipex *data)
{
	wait(NULL);
	close(data->fd1[1]);
	ft_free_split(data->temp1);
	data->path1 = get_next_line(data->fd1[0]);
	if (data->path1 == NULL)
	{
		if (argv[2][0] == '"' && argv[2][(ft_strlen(argv[2])) - 1] == '"')
			ft_printf("%s: command not found: %s\n", data->shell, argv[2]);
		else
			ft_printf("%s: command not found: %s\n", data->shell, data->cmd1[0]);
		return (1);
	}
	ft_strlcpy(data->path1, data->path1, ft_strlen(data->path1));
	close (data->fd1[0]);
	return (0);
}

static int	ft_exec_search_1(char **envp, t_pipex *data)
{
	close(data->fd1[0]);
	dup2(data->fd1[1], STDOUT_FILENO);
	close(data->fd1[1]);
	if (execve("/usr/bin/which", data->temp1, envp) < 0)
	{
		ft_free_split(data->temp1);
		perror(data->shell);
		free(data->shell);
		return (3);
	}
	return (0);
}

int	ft_pipex(char **argv, char **envp, t_pipex *data)
{
	if (ft_openpipe((*data).fd1, data->shell) != 0)
		return (1);
	if (ft_identify_route(argv, 2, &(data->cmd1), &(data->temp1)) == 1)
	{
		ft_print_error(argv, data->shell, 2);
		return (ft_error_message(argv, envp, data));
	}
	if (ft_forking(&(*data).pid1, data->shell) != 0)
		return (2);
	if (data->pid1 == 0)
		return (ft_exec_search_1(envp, data));
	else
	{
		if (ft_wait_get_path1(argv, data) != 0)
			return (ft_prepare1(argv, envp, data));
	}
	if (ft_openpipe((*data).fd1, data->shell) != 0)
		return (5);
	if (ft_forking(&(*data).pid1, data->shell) != 0)
		return (6);
	if (data->pid1 == 0)
		return (ft_run_route1(envp, data));
	return (ft_prepare1(argv, envp, data));
}
