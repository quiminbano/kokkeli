/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:19:11 by corellan          #+#    #+#             */
/*   Updated: 2022/12/18 16:06:21 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	ft_forking(int *pid)
{
	((*pid)) = fork();
	if ((*pid) < 0)
	{
		perror("Pipex");
		return (2);
	}
	return (0);
}

int	ft_openpipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		perror("Pipex");
		return (1);
	}
	return (0);
}