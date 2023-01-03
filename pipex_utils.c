/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:19:11 by corellan          #+#    #+#             */
/*   Updated: 2023/01/03 11:42:13 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_identify_route(char **argv, int prog, char ***cmd, char ***temp)
{
	char	*t;

	(*cmd) = ft_split(argv[prog], ' ');
	if ((*cmd)[0] == NULL || argv[prog][0] == '\0')
	{
		ft_free_split((*cmd));
		return (1);
	}
	t = ft_strjoin("which ", (*cmd[0]));
	(*temp) = ft_split(t, ' ');
	free(t);
	return (0);
}

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	if (str[i] != NULL)
		free(str[i]);
	if (str != NULL)
		free(str);
}

int	ft_forking(int *pid, char *str)
{
	((*pid)) = fork();
	if ((*pid) < 0)
	{
		perror(str);
		free(str);
		return (2);
	}
	return (0);
}

int	ft_openpipe(int *fd, char *str)
{
	if (pipe(fd) < 0)
	{
		perror(str);
		free(str);
		return (1);
	}
	return (0);
}
