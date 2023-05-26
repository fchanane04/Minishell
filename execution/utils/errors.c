/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:56:50 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 00:55:17 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	directory_error(char *arg)
{
	g_var->status = 126;
	printf("bash: %s: is a directory\n", arg);
	exit(g_var->status);
}

void	permission_error(char *arg)
{
	printf("bash: %s: Permission denied\n", arg);
	g_var->status = 126;
	exit(g_var->status);
}

void	not_found_error(char *arg)
{
	g_var->status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" command not found\n", 2);
	exit(g_var->status);
}

void	no_directory(char *arg)
{
	if (is_file(arg))
		file_error(arg);
	else
	{
		g_var->status = 127;
		printf("bash: %s: No such file or directory\n", arg);
		exit(g_var->status);
	}	
}

void	file_error(char *arg)
{
	g_var->status = 126;
	printf("bash: %s: Not a directory\n", arg);
	exit(g_var->status);
}
