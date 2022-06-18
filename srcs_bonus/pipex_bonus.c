/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:13:30 by chaidel           #+#    #+#             */
/*   Updated: 2022/03/24 17:25:10 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_process(char *command, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(command, ' ');
	if (!cmd[0])
	{
		ft_double_free(cmd);
		perror("");
		exit(EXIT_FAILURE);
	}
	path = ft_get_path(cmd[0], envp);
	if (!path)
		ft_err_cmd(cmd[0], path, cmd);
	if (execve(path, cmd, envp) < 0)
		ft_err_cmd(cmd[0], path, cmd);
}

void	ft_case_parent(pid_t child, t_data *pip)
{
	if (dup2(pip->pipefd[0], STDIN_FILENO) == -1)
		ft_err("Dup2");
	ft_close_pipe(pip);
	waitpid(child, NULL, 0);
}

void	ft_pipex(t_data *pip, char **av, char **envp)
{
	pid_t	child;
	int		n_arg;

	n_arg = ft_open_mode(pip, av);
	while (++n_arg < pip->ac - 2)
	{
		if (pipe(pip->pipefd) == -1)
			ft_err("Pipe");
		child = fork();
		if (child == -1)
			ft_err("Fork");
		if (child == 0)
		{
			if (dup2(pip->pipefd[1], STDOUT_FILENO) == -1)
				ft_err("Dup2");
			ft_close_pipe(pip);
			ft_process(av[n_arg], envp);
		}
		else
			ft_case_parent(child, pip);
	}
	if (dup2(pip->out_fd, STDOUT_FILENO) == -1)
		ft_err("Dup2");
	ft_process(av[n_arg], envp);
}

int	main(int ac, char **av, char **envp)
{
	t_data	pip;

	if (!*envp)
	{
		perror("Empty envp");
		exit(EXIT_FAILURE);
	}
	if (ac >= 5)
	{
		pip.ac = ac;
		ft_pipex(&pip, av, envp);
		close(pip.in_fd);
		close(pip.out_fd);
	}
	else
	{
		ft_putendl_fd("Invalid number of arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
