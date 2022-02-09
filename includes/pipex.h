/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:19:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/09 15:27:26 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	exec_cmd(char *cmd, char **env);

char	*get_path_cmd(char *cmd, char **env);

void	*free_tab(char **tab);

char	**get_path_env(char **env);

#endif