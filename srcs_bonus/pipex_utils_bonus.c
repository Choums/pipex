/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:44:09 by chaidel           #+#    #+#             */
/*   Updated: 2022/02/09 11:16:21 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	**ft_get_env(char **envp)
{
	char	**split;
	char	*dir;
	size_t	i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	dir = envp[i];
	dir = ft_substr(dir, 5, ft_strlen(dir) - 6);
	split = ft_split(dir, ':');
	free(dir);
	return (split);
}

/*
	Get value of PATH variable and check in which the cmd's file is in
	----------
	cmd -> command's file
	envp -> environment variable
	----------
	Return -> path to the command's file
*/
char	*ft_get_path(char *cmd, char **envp)
{
	char	*dir;
	char	*path;
	char	**split;
	size_t	i;

	split = ft_get_env(envp);
	i = 0;
	while (split[i])
	{
		dir = ft_strjoin("/", cmd);
		path = ft_strjoin(split[i], dir);
		free(dir);
		if (access(path, F_OK) == 0)
		{
			ft_double_free(split);
			return (path);
		}
		free(path);
		i++;
	}
	ft_double_free(split);
	return (NULL);
}

/*
	Opens files and/or get input for here_doc and check the opening
	and set n_arg var
	----------
	Case of infile -> opens infile and outfiles as usual
	Case of here_doc -> get inputs via gnl and opens outfile with O_APPEND
						istead of O_TRUNC
*/
int	ft_open_mode(t_data *pip, char **av)
{
	if (!ft_strcmp(av[1], "here_doc"))
	{
		ft_here_doc(av);
		pip->out_fd = open(av[pip->ac - 1], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (pip->out_fd < 0)
			ft_err("Open");
		return (2);
	}
	else
	{
		pip->in_fd = open(av[1], O_RDONLY);
		pip->out_fd = open(av[pip->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pip->in_fd < 0 || pip->out_fd < 0)
			ft_err("Open");
		if (dup2(pip->in_fd, STDIN_FILENO) == -1)
			ft_err("Dup2 1");
		return (1);
	}
}

void	ft_double_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	while (i)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	ft_err(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
