/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:24:10 by chaidel           #+#    #+#             */
/*   Updated: 2022/01/29 19:10:55 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_fst_process(int in_fd, int *pipefd, char *command, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(command, ' ');
	path = ft_get_path(cmd[0], envp);
	dup2(in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	if (execve(path, cmd, envp) < 0)
	{
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

void	ft_snd_process(int out_fd, int *pipefd, char *command, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(command, ' ');
	path = ft_get_path(cmd[0], envp);
	dup2(out_fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	if (execve(path, cmd, envp) < 0)
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

void	ft_pipex(int in_fd, int out_fd, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	fst_child;
	pid_t	snd_child;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	fst_child = fork();
	if (fst_child < 0)
		ft_err();
	else if (fst_child == 0)
		ft_fst_process(in_fd, pipefd, av[2], envp);
	snd_child = fork();
	if (snd_child < 0)
		ft_err();
	else if (snd_child == 0)
		ft_snd_process(out_fd, pipefd, av[3], envp);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(fst_child, NULL, 0);
	waitpid(snd_child, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int	in_fd;
	int	out_fd;

	in_fd = open(av[1], O_RDONLY);
	out_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_fd < 0 || out_fd < 0)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}
	if (ac != 5)
		exit(EXIT_FAILURE);
	ft_pipex(in_fd, out_fd, av, envp);
	close(in_fd);
	close(out_fd);
	return (0);
}
