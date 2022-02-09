/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:26:09 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/09 15:37:06 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

char	**get_path_env(char **env)
{

	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			return (ft_split(&((*env)[5]), ':'));
		env++;
	}
	return (NULL);
}

char	*get_path_cmd(char *cmd, char **env)
{
	char	*tmp;
	char	*path_cmd;

	while (*env)
	{
		tmp = ft_strdup(*env);
		path_cmd = ft_strjoin(tmp, "/");
		path_cmd = ft_strjoin(path_cmd, cmd);
		if (!access(path_cmd, F_OK))
			return (path_cmd);
		free(path_cmd);
		env++;
	}
	return (NULL);
}

void	exec_cmd(char *cmd, char **env)
{
	char	*path_cmd;
	char	**tmp;

	tmp = ft_split(cmd, ' ');
	path_cmd = get_path_cmd(tmp[0], env);
	if (!path_cmd)
	{
		perror(tmp[0]);
		free_tab(tmp);
		return ;
	}
	if (execve(path_cmd, tmp, env) == -1)
		perror(strerror(errno));
	free_tab(tmp);
}
