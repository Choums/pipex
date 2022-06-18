/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:11:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/06/18 14:34:29 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"
# include "get_next_line.h"

typedef struct s_data
{
	int		in_fd;
	int		out_fd;
	int		pipefd[2];
	int		ac;
}	t_data;

char	*ft_get_path(char *cmd, char **envp);
char	**ft_get_env(char **envp);
void	ft_double_free(char **tab);
int		ft_open_mode(t_data *pip, char **av);
void	ft_err(char *msg);
void	ft_err_cmd(char *msg, char *path, char **cmd);

void	ft_pipex(t_data *pip, char **av, char **envp);
void	ft_process(char *command, char **envp);

void	ft_display_here(char **av);
void	ft_here_doc(char **av);
void	ft_close_pipe(t_data *pip);

size_t	ft_strlen(const char *str);
size_t	ft_putstr_fd(char *s, int fd);
size_t	ft_putendl_fd(char *s, int fd);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char sep);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strcmp(const char *s1, const char *s2);

#endif
