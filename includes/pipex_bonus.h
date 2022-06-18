/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:11:16 by chaidel           #+#    #+#             */
/*   Updated: 2022/02/11 16:02:42 by chaidel          ###   ########.fr       */
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

#endif
