/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/21 16:17:14 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "pipex.h"

void	child_p(char *cmd, char **env, int infile)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		exit_with_msg("pipe");
	pid = fork();
	if (pid == -1)
		exit_with_msg("fork");
	else if (!pid)
	{
		close(fd[0]);
		if (!infile)
			exit_with_msg("infile");
		dup2(fd[1], STDOUT_FILENO);
		exec_cmd(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	main_p(char **av, char **env, int *files)
{
	while (*(av + 2))
		child_p(*(av++), env, files[0]);
	dup2(files[1], STDOUT_FILENO);
	exec_cmd(*av, env);
	close(files[0]);
	close(files[1]);
}

void	here_doc(char *limiter, int ac)
{
	int		pid;
	int		fd[2];

	if (ac < 6)
	{
		ft_putendl_fd("Wrong number of args.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		exit_with_msg("pipe");
	pid = fork();
	if (!pid)
		write_pipe(fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		files[2];

	if (ac < 5)
		return (0);
	i = 3;
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		files[1] = safe_open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		here_doc(av[2], ac);
	}
	else
	{
		i = 2;
		files[0] = open(av[1], O_RDONLY, 0644);
		if (files[0] == -1)
			files[0] = 0;
		files[1] = safe_open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(files[0], STDIN_FILENO);
	}
	main_p(&av[i], env, files);
	return (0);
}
