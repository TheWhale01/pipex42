/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:02:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/09 15:27:55 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	char	**path;

	if (ac < 4)
		return (0);
	path = get_path_env(env);
	exec_cmd(av[2], path);
	free_tab(path);
	return (0);
}
