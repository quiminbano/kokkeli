/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:20 by corellan          #+#    #+#             */
/*   Updated: 2022/12/18 18:47:45 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_run_route1(char **argv, char **envp, t_pipex *data)
{
	close(data->fd1[0]);
	dup2(data->fdinput, STDIN_FILENO);
	close(data->fdinput);
	if (execve((data->path1), data->cmd1, envp) < 0)
	{
		ft_free_split(data->cmd1);
		free(data->path1);
		perror("Pipex");
		return (3);
	}
	return (0);
}

static int	ft_wait_get_path1(char **argv, char **envp, t_pipex *data)
{
	wait(NULL);
	close(data->fd1[1]);
	data->cmd1 = ft_split(argv[2], ' ');
	data->path1 = get_next_line(data->fd1[0]);
	if(data->path1 == NULL)
	{
		ft_printf("Pipex: command not found: %s\n", data->cmd1[0]);
		ft_free_split(data->cmd1);
		return (1);
	}
	ft_strlcpy(data->path1, data->path1, ft_strlen(data->path1));
	close (data->fd1[0]);
	return (0);
}

static int	ft_identify_route1(char **argv, char **envp, t_pipex *data)
{
	char	*temp;

	close(data->fd1[0]);
	data->cmd1 = ft_split(argv[2], ' ');
	temp = ft_strjoin("which ", data->cmd1[0]);
	data->temp1 = ft_split(temp, ' ');
	free(temp);
	ft_free_split(data->cmd1);
	dup2(data->fd1[1], STDOUT_FILENO);
	close(data->fd1[1]);
	if (execve("/usr/bin/which", data->temp1, envp) < 0)
	{
		ft_free_split(data->temp1);
		perror("Pipex");
		return (3);
	}
	return (0);
}

int	ft_pipex(char **argv, char **envp, t_pipex *data)
{
	if (ft_openpipe((*data).fd1) != 0)
		return (1);
	if (ft_forking(&(*data).pid1) != 0)
		return (2);
	if (data->pid1 == 0)
		return (ft_identify_route1(argv, envp, data));
	else
	{
		if (ft_wait_get_path1(argv, envp, data) != 0)
			return (4);
	}
	if (ft_openpipe((*data).fd1) != 0)
		return (5);
	if (ft_forking(&(*data).pid1) != 0)
		return (6);
	if (data->pid1 == 0)
		return (ft_run_route1(argv, envp, data));
	else
	{
		wait(NULL);
		ft_printf("Hello again\n");
	}
	return (0);
}