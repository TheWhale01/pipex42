/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/09 22:04:31 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"
#include "pipex.h"

void	child_p(char **av, char **path, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY, 0644);
	if (infile == -1)
		exit_with_msg(NULL);
	dup2(fd[1], STDOUT);
	dup2(infile, STDOUT);
	close(fd[0]);
	exec_cmd(av[2], path);
}

void	main_p(char **av, char **path, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		exit_with_msg(NULL);
	dup2(fd[0], STDIN);
	dup2(outfile, STDIN);
	close(fd[1]);
	exec_cmd(av[3], path);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pid;
	char	**path;

	if (ac < 5)
		exit_with_msg(NULL);
	if (pipe(fd))
		exit_with_msg(NULL);
	pid = fork();
	path = get_path_env(env);
	if (pid == -1)
		exit_with_msg(NULL);
	else if (!pid)
		child_p(av, path, fd);
	waitpid(pid, NULL, 0);
	free_tab(path);
	return (0);
}
