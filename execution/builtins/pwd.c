/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 04:18:38 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 00:55:55 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	ft_pwd(t_parser *prog)
{
	char	*buff;

	prog = NULL;
	buff = getcwd(0, 0);
	if (!buff)
		buff = get_envc(g_var->envc, "PWD");
	write(g_var->fd_out, buff, ft_strlen(buff));
	write(g_var->fd_out, "\n", 1);
	free(buff);
	if (g_var->fd_out > 1)
		close(g_var->fd_out);
	g_var->status = 0;
}
