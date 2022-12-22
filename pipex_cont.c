/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:37:09 by corellan          #+#    #+#             */
/*   Updated: 2022/12/22 17:38:42 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_prepare2(t_pipex *data)
{
	int		prep2;
	char	*str;

	prep2 = 0;
	wait(NULL);
	close(data->fd1[1]);
	free(data->path2);
	ft_free_split(data->cmd2);
	str = ft_calloc(1, 1);
	dup2(data->fdoutput, STDOUT_FILENO);
	close(data->fdoutput);
	while (str != NULL)
	{
		free(str);
		str = get_next_line(data->fd1[0]);
		if (str != NULL)
			ft_printf("%s", str);
	}
	close(data->fd1[0]);
	free(data->shell);
	return (prep2);
}

static int	ft_run_route2(char **envp, t_pipex *data)
{
	close(data->fd1[0]);
	dup2(data->fd1[1], STDOUT_FILENO);
	close(data->fd1[1]);
	if (execve((data->path2), data->cmd2, envp) < 0)
	{
		ft_free_split(data->cmd2);
		free(data->path2);
		perror(data->shell);
		free(data->shell);
		return (12);
	}
	return (0);
}

static int	ft_wait_get_path2(t_pipex *data)
{
	wait(NULL);
	close(data->fd1[1]);
	free(data->temp2);
	data->path2 = get_next_line(data->fd1[0]);
	if (data->path2 == NULL)
	{
		ft_printf("%s: command not found: %s\n", data->shell, data->cmd2[0]);
		ft_free_split(data->cmd2);
		free(data->shell);
		return (1);
	}
	ft_strlcpy(data->path2, data->path2, ft_strlen(data->path2));
	close (data->fd1[0]);
	return (0);
}

static int	ft_exec_search_2(char **envp, t_pipex *data)
{
	close(data->fd1[0]);
	dup2(data->fd1[1], STDOUT_FILENO);
	close(data->fd1[1]);
	if (execve("/usr/bin/which", data->temp2, envp) < 0)
	{
		ft_free_split(data->temp2);
		perror(data->shell);
		free(data->shell);
		return (9);
	}
	return (0);
}

int	ft_pipex_cont(char **argv, char **envp, t_pipex *data)
{
	int	prep3;

	prep3 = 0;
	if (ft_openpipe((*data).fd1, data->shell) != 0)
		return (7);
	ft_identify_route(argv, 3, &(data->cmd2), &(data->temp2));
	if (ft_forking(&(*data).pid1, data->shell) != 0)
		return (8);
	if (data->pid1 == 0)
		return (ft_exec_search_2(envp, data));
	else
	{
		if (ft_wait_get_path2(data) != 0)
			return (9);
	}
	if (ft_openpipe((*data).fd1, data->shell) != 0)
		return (10);
	if (ft_forking(&(*data).pid1, data->shell) != 0)
		return (11);
	if (data->pid1 == 0)
		return (ft_run_route2(envp, data));
	else
		prep3 = ft_prepare2(data);
	return (prep3);
}
