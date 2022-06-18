/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:24:12 by chaidel           #+#    #+#             */
/*   Updated: 2022/01/21 18:12:48 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

char	*ft_get_path(char *cmd, char **envp);
char	**ft_get_env(char **envp);
void	ft_double_free(char **tab);
void	ft_err(char *msg);
void	ft_err_cmd(char *msg, char *path, char **cmd);

void	ft_pipex(char **av, char **envp);
void	ft_fst_process(char *file, int *pipefd, char *command, char **envp);
void	ft_snd_process(char *file, int *pipefd, char *command, char **envp);

// size_t	ft_strlen(const char *str);
// size_t	ft_putstr_fd(char *s, int fd);
// size_t	ft_putendl_fd(char *s, int fd);
// char	*ft_strcat(char *dest, const char *src);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strnstr(const char *str, const char *to_find, size_t len);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	**ft_split(char const *s, char sep);
// void	*ft_memcpy(void *dest, const void *src, size_t n);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
