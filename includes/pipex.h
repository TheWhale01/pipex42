/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:19:54 by hubretec          #+#    #+#             */
/*   Updated: 2022/02/17 12:15:15 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define MAX_FD 254

int		ft_putstr(char const *s);
int		ft_putstr_fd(char const *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	exit_with_msg(char *str);
void	exec_cmd(char *cmd, char **env);
void	ft_putendl_fd(char const *s, int fd);

char	*ft_strdup(char *src);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*get_path_cmd(char *cmd, char **env);
char	*ft_strjoin(char const *s1, char const *s2);

void	*free_tab(char **tab);

char	**get_path_env(char **env);
char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *str);

#endif