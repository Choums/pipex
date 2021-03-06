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
# include <errno.h>
# include <sys/wait.h>
# include "../libft/libft.h"

char	*ft_get_path(char *cmd, char **envp);
char	**ft_get_env(char **envp);
void	ft_double_free(char **tab);
void	ft_err(char *cmd);
void	ft_err_cmd(char *msg, char *path, char **cmd);

void	ft_pipex(char **av, char **envp);
void	ft_fst_process(char *file, int *pipefd, char *command, char **envp);
void	ft_snd_process(char *file, int *pipefd, char *command, char **envp);

#endif
