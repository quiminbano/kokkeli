/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:18:49 by corellan          #+#    #+#             */
/*   Updated: 2022/12/18 17:02:26 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int			returned;
	t_pipex		data;

	data.fdinput = open(argv[1], O_RDONLY);
	returned = ft_pipex(argv, envp, &data);
	return (returned);
}