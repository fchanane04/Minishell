/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:46:26 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 02:42:01 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	builtin_check(char *cmd)
{
	int	check;

	check = 0;
	if (!ft_strcmp(cmd, "echo"))
		check = 1;
	if (!ft_strcmp(cmd, "cd"))
		check = 1;
	if (!ft_strcmp(cmd, "pwd"))
		check = 1;
	if (!ft_strcmp(cmd, "env"))
		check = 1;
	if (!ft_strcmp(cmd, "unset"))
		check = 1;
	if (!ft_strcmp(cmd, "export"))
		check = 1;
	if (!ft_strcmp(cmd, "exit"))
		check = 1;
	return (check);
}

int	exec_type_check(t_parser *prog)
{
	int			count;
	int			check;

	count = list_counter(prog);
	if (count == 1)
	{
		check = 1;
		if (prog->args && builtin_check(prog->args[0]))
			check = 0;
	}
	else
		check = 2;
	return (check);
}

int	amb_red_handler(char *filename)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	if (g_var->fd_in > 2)
		close(g_var->fd_in);
	if (g_var->fd_out > 2)
		close(g_var->fd_out);
	g_var->status = 1;
	return (-1);
}
