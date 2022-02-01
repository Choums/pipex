/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_management_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:59:55 by chaidel           #+#    #+#             */
/*   Updated: 2022/02/01 18:57:50 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_close_pipe(t_data *pip)
{
	close(pip->pipefd[0]);
	close(pip->pipefd[1]);
}

void	ft_here_doc(char **av)
{
	char	*line;
	char	*end;
	char	*new_line;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_err("Pipe");
	end = av[2];
	end = ft_strjoin(end, "\n");
	while (ft_strcmp(line, end) != 0)
	{
		ft_display_here(av);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, end))
			new_line = ft_join(new_line, line);
	}
	free(line);
	write(fd[1], new_line, ft_strlen(new_line));
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
