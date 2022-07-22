/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:24:05 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/22 14:21:59 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**ft_get_env(char **envp)
{
	char	**split;
	char	*dir;
	size_t	i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
		return (NULL);
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
	if (!split || !cmd)
		return (NULL);
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

void	ft_double_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	ft_err(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(127);
}

void	ft_err_cmd(char *msg, char *path, char **cmd)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("command not found", STDERR_FILENO);
	ft_double_free(cmd);
	free(path);
	exit(127);
}
