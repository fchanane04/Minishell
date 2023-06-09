/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:13:36 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 00:55:17 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	re_init_heredoc(char *heredoc, int fd_in, int err)
{
	if (fd_in == -404)
	{
		g_var->fd_in = open(heredoc, O_RDONLY, 0644);
		if (g_var->fd_in == -1)
		{
			error_printer(BASH_ERR, ": ", heredoc);
			perror("");
			g_var->status = 1;
			return (-1);
		}
	}
	return (err);
}

void	exit_status(pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) == 0)
		g_var->status = 0;
	else if (WIFSIGNALED(status) == 1)
		g_var->status = 1;
	if (WIFSIGNALED(status) == 1)
		g_var->flag = -3;
	if (WIFSIGNALED(status) == 0)
		g_var->flag = -6;
	signal(SIGINT, signal_handler);
}

int	check_other_heredoc(t_files *file)
{
	t_files	*tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->type == DEL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
