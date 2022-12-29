/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:10:05 by corellan          #+#    #+#             */
/*   Updated: 2022/12/29 17:20:03 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(char **argv, char *shell, int prog)
{
	if (argv[prog][0] == ' ')
		ft_printf("%s: command not found: %s\n", shell, argv[prog]);
	else
		ft_printf("%s: permission denied:\n", shell);
}

int	ft_error_message(char **argv, char **envp, t_pipex *data)
{
	if (ft_openpipe((*data).fd1, data->shell) != 0)
		return (1);
	if (ft_forking(&(*data).pid1, data->shell) != 0)
		return (2);
	if (data->pid1 == 0)
	{
		close(data->fd1[0]);
		write(data->fd1[1], "\0", 1);
		close(data->fd1[1]);
		return (1);
	}
	else
	{
		wait(NULL);
		close(data->fd1[1]);
		dup2(data->fd1[0], STDIN_FILENO);
		close(data->fd1[0]);
		return (ft_pipex_cont(argv, envp, data));
	}
	return (1);
}
