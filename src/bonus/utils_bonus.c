/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:39:05 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/12 13:59:24 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	exit_with_msg(char *str)
{
	perror(str);
	exit(0);
}

void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

void	write_pipe(int	*fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(STDIN);
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
	}
}
