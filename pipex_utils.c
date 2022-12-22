/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:19:11 by corellan          #+#    #+#             */
/*   Updated: 2022/12/22 17:25:49 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_identify_route(char **argv, int prog, char ***cmd, char ***temp)
{
	char	*t;

	if (ft_strnstr(argv[prog], "awk", ft_strlen(argv[0])) == NULL)
	{
		(*cmd) = ft_split(argv[prog], ' ');
		t = ft_strjoin("which ", (*cmd[0]));
		(*temp) = ft_split(t, ' ');
		free(t);
	}
	else
	{
		(*cmd) = ft_split(argv[prog], 39);
		t = ft_strjoin("which ", "awk");
		(*temp) = ft_split(t, ' ');
		free(t);
	}
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
