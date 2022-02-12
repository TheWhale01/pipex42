/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/12 11:28:34 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"
#include "pipex.h"

void	open_files(int ac, char **av, int *outfile)
{
	*outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
		exit_with_msg(av[ac - 1]);
}

void	child_p(char **av, char **path, int *fd, char *filename)
{
	int	infile;

	infile = open(filename, O_RDONLY, 0644);
	if (infile == -1)
		exit_with_msg(av[1]);
	dup2(fd[1], STDOUT);
	dup2(infile, STDIN_FILENO);
	exec_cmd(av[0], path);
	close(infile);
}

void	main_p(char **av, char **path, int *fd, int outfile)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT);
	exec_cmd(av[0], path);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pid;
	int		outfile;
	char	*filename;
	char	**path;

	if (ac < 5)
		exit_with_msg(NULL);
	filename = av[1];
	open_files(ac, av, &outfile);
	if (pipe(fd))
		exit_with_msg(NULL);
	av++;
	pid = fork();
	path = get_path_env(env);
	if (pid == -1)
		exit_with_msg(NULL);
	else if (!pid)
		while (*(++av + 1))
			child_p(av, path, fd, filename);
	waitpid(pid, NULL, 0);
	main_p(av, path, fd, outfile);
	free_tab(path);
	close(outfile);
	return (0);
}
