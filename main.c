/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:18:49 by corellan          #+#    #+#             */
/*   Updated: 2022/12/29 17:34:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_get_shell(t_pipex *data, char **envp)
{
	char	**temp;
	int		i;

	i = 0;
	while (envp[i] != '\0')
	{
		if (ft_strnstr(envp[i], "SHELL", ft_strlen(envp[i])) != NULL)
			break ;
		i++;
	}
	temp = ft_split(envp[i], '/');
	i = 0;
	while (temp[i] != NULL)
		i++;
	data->shell = ft_strdup(temp[i - 1]);
	ft_free_split(temp);
}

static int	main_aux(int argc, char **argv, char **envp, t_pipex data)
{
	data.fdinput = open(argv[1], O_RDONLY);
	data.fdoutput = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data.fdinput < 0)
		ft_printf("%s: %s: %s\n", data.shell, strerror(errno), argv[1]);
	if (data.fdoutput < 0)
	{
		ft_printf("%s: %s: %s\n", data.shell, strerror(errno), argv[argc - 1]);
		free(data.shell);
		close(data.fdinput);
		return (3);
	}
	if (data.fdinput < 0)
		return (ft_error_message(argv, envp, &data));
	return (ft_pipex(argv, envp, &data));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	ft_get_shell(&data, envp);
	if (argc < 5 || argc > 5)
	{
		if (argc < 5)
			ft_printf("%s: Not enough parameters.\n", data.shell);
		else
			ft_printf("%s: Too many parameters.\n", data.shell);
		free(data.shell);
		return (1);
	}
	return (main_aux(argc, argv, envp, data));
}
