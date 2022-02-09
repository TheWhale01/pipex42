/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/09 16:50:57 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

void	init(int fd[2], int *pid1, int *pid2)
{
	if (pipe(fd))
		exit_with_msg(NULL);
	*pid1 = fork();
	*pid2 = fork();
	if (*pid1 == -1 || *pid2 == -1)
	{
		close(fd[0]);
		close(fd[1]);
		exit_with_msg(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	int		fd_infile;
	int		fd_outfile;

	if (ac < 4)
		return (0);
	fd_infile = open(av[1], O_RDONLY, 0644);
	fd_outfile = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (fd_infile == -1 || fd_outfile == -1)
		exit_with_msg(NULL);
	init(fd, &pid1, &pid2);
	if (!pid1)
	{
		exec_cmd(av[2], get_path_env(env));
	}
	ft_printf("lol\n");
	close(fd[0]);
	close(fd[1]);
	return (0);
}
