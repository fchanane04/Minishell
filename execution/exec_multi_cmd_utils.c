/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 07:54:57 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/05 01:11:07 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_path_and_check(t_parser *prog)
{
	char	*path;

	path = NULL;
	if (access(prog->args[0], X_OK))
	{
		if (isdir(prog->args[0]))
			directory_error(prog->args[0]);
		else
		{
			path = find_path(create_paths(g_var->envc), prog->args[0]);
			cmd_error_check(prog->args[0], path);
		}
	}
	else
		path = ft_strdup(prog->args[0]);
	return (path);
}

void	reset_files(int *i)
{
	g_var->fd_in = 0;
	g_var->fd_out = 1;
	*i += 1;
}

void	init_vars(int *save, int *i)
{
	*save = -1;
	*i = 0;
	g_var->flag_here = 0;
}

void	skip_to_another_cmd(t_parser *tmp, int *i)
{
	tmp = tmp->next;
	*i += 1;
}

void	handle_files(int *save, int fd[2])
{
	if (*save != -1)
		close(*save);
	*save = fd[0];
	close (fd[1]);
}
