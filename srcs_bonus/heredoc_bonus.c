/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:59:55 by chaidel           #+#    #+#             */
/*   Updated: 2022/02/09 11:25:20 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_close_pipe(t_data *pip)
{
	close(pip->pipefd[0]);
	close(pip->pipefd[1]);
}

void	ft_err_cmd(char *msg, char *path, char **cmd)
{
	char	*err;

	err = ft_strjoin("command not found: ", msg);
	ft_putendl_fd(err, STDERR_FILENO);
	free(path);
	ft_double_free(cmd);
	exit(EXIT_FAILURE);
}

/*
	Copy the heredoc redirection,
	takes multiple lines of input until the limiter is identified.
	The function generates a pipe from which she passes all inputs
	to the current process.
	(Display the pipes)
*/
void	ft_here_doc(char **av)
{
	char	*line;
	char	*end;
	char	*new_line;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_err("Pipe");
	line = "\0";
	new_line = line;
	end = av[2];
	end = ft_strjoin(end, "\n");
	while (ft_strcmp(line, end) != 0)
	{
		ft_display_here(av);
		line = get_next_line(STDIN_FILENO);
		new_line = ft_join(new_line, line);
	}
	free(line);
	if (write(fd[1], new_line, ft_strlen(new_line)) == -1)
		ft_err("Write");
	free(new_line);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_err("Dup2");
	close(fd[0]);
	close(fd[1]);
}

void	ft_display_here(char **av)
{
	size_t	num;
	char	*msg;

	num = 0;
	msg = "heredoc> ";
	while (av[num])
		num++;
	num -= 4;
	if (num == 1)
	{
		ft_putstr_fd(msg, STDIN_FILENO);
		return ;
	}
	while (--num)
		msg = ft_strjoin("pipe ", msg);
	ft_putstr_fd(msg, STDIN_FILENO);
}
