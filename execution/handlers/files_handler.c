/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:18:13 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 00:55:17 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	infile_handler(char *filename)
{
	if (g_var->fd_in > 2)
		close(g_var->fd_in);
	g_var->fd_in = open(filename, O_RDONLY, 0777);
	if (g_var->fd_in == -1)
	{
		error_printer(BASH_ERR, ": ", filename);
		perror("");
		g_var->status = 1;
		return (-1);
	}
	return (1);
}

int	outfile_handler(char *filename)
{
	if (g_var->fd_out > 2)
		close(g_var->fd_out);
	g_var->fd_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (g_var->fd_out == -1)
	{
		error_printer(BASH_ERR, ": ", filename);
		perror("");
		g_var->status = 1;
		return (-1);
	}
	return (1);
}

int	append_handler(char *filename)
{
	if (g_var->fd_out > 2)
		close(g_var->fd_out);
	g_var->fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (g_var->fd_out == -1)
	{
		error_printer(BASH_ERR, ": ", filename);
		perror("");
		g_var->status = 1;
		return (-1);
	}
	return (1);
}

void	heredoc_handler(void)
{
	if (g_var->fd_in > 2)
		close(g_var->fd_in);
	g_var->fd_in = -404;
}

int	file_prep(t_parser *prog, char *heredoc)
{
	t_files	*tmp;
	int		err;

	tmp = prog->files;
	err = 1;
	while (tmp && err != -1)
	{
		if (tmp->type == AMB)
			err = amb_red_handler(tmp->filename);
		if (tmp->type == L_RED)
			err = infile_handler(tmp->filename);
		if (tmp->type == DEL)
			heredoc_handler();
		if (tmp->type == R_RED)
			err = outfile_handler(tmp->filename);
		if (tmp->type == APP)
			err = append_handler(tmp->filename);
		tmp = tmp->next;
	}
	err = re_init_heredoc(heredoc, g_var->fd_in, err);
	return (err);
}
