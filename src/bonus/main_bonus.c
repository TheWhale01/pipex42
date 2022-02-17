/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/17 11:18:47 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"
#include "pipex_bonus.h"

void	child_p(char *cmd, char **env)
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
		dup2(fd[1], STDOUT_FILENO);
		exec_cmd(cmd, get_path_env(env));
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	main_p(char **av, char **env, int outfile)
{
	while (*(av + 2))
		child_p(*(av++), env);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(*av, get_path_env(env));
	close(outfile);
}

void	here_doc(char *limiter, int ac)
{
	int		pid;
	int		fd[2];

	if (ac < 6)
	{
		ft_putendl_fd("Wrong number of args.", STDERR);
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
	int		infile;
	int		outfile;

	if (ac < 5)
		return (0);
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		i = 3;
		outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (outfile == -1)
			exit_with_msg(av[ac - 1]);
		here_doc(av[2], ac);
	}
	else
	{
		i = 2;
		outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		infile = open(av[1], O_RDONLY, 0644);
		if (outfile == -1 || infile == -1)
			exit_with_msg("Opening files");
		dup2(infile, STDIN_FILENO);
	}
	main_p(&av[i], env, outfile);
	return (0);
}
