/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:01:36 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 00:55:55 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	lines_counter(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	printable(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env(t_parser *prog)
{
	t_env	*tmp;

	prog = NULL;
	tmp = g_var->envc;
	while (tmp)
	{
		if (printable(tmp->line))
		{
			ft_putstr_fd(tmp->line, g_var->fd_out);
			ft_putstr_fd("\n", g_var->fd_out);
		}
		tmp = tmp->next;
	}
	if (g_var->fd_out > 1)
		close(g_var->fd_out);
	g_var->status = 0;
}
