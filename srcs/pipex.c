/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:24:10 by chaidel           #+#    #+#             */
/*   Updated: 2022/03/24 17:12:06 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_fst_process(char *file, int *pipefd, char *command, char **envp)
{
	char	**cmd;
	char	*path;
	int		in_fd;

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
	in_fd = open(file, O_RDONLY);
	if (in_fd < 0)
		ft_err("Open");
	dup2(in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (execve(path, cmd, NULL) < 0)
		ft_err_cmd(cmd[0], path, cmd);
}

void	ft_snd_process(int out_fd, int *pipefd, char *command, char **envp)
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
	dup2(out_fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	if (execve(path, cmd, NULL) < 0)
		ft_err_cmd(cmd[0], path, cmd);
}

void	ft_pipex(int out_fd, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	fst_child;
	pid_t	snd_child;

	if (pipe(pipefd) == -1)
		ft_err("Pipe");
	fst_child = fork();
	if (fst_child < 0)
		ft_err("Fork");
	else if (fst_child == 0)
		ft_fst_process(av[1], pipefd, av[2], envp);
	snd_child = fork();
	if (snd_child < 0)
		ft_err("Fork");
	else if (snd_child == 0)
		ft_snd_process(out_fd, pipefd, av[3], envp);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(fst_child, NULL, 0);
	waitpid(snd_child, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int	out_fd;

	if (!*envp)
	{
		perror("Empty envp");
		exit(EXIT_FAILURE);
	}
	out_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
		ft_err("Open");
	if (ac != 5)
	{
		ft_putendl_fd("Invalid number of arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_pipex(out_fd, av, envp);
	exit(EXIT_SUCCESS);
}
