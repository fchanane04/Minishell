/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:02:24 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 00:55:55 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

int	valid_name(char *str)
{
	int		i;
	char	*name;

	name = var_name(str);
	i = 0;
	if (name[i] != '_' && !ft_isalpha(name[i]))
	{
		free(name);
		return (0);
	}
	i++;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
		{
			free(name);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

void	identifier_error(char *str, char *builtin)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(builtin, 1);
	ft_putstr_fd(": `", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\': not a valid identifier\n", 1);
	g_var->status = 1;
}

void	remove_inside(char *arg)
{
	t_env	*tmp;
	t_env	*freeit;

	tmp = g_var->envc;
	while (tmp->next)
	{
		if (!ft_strcmp_export(arg, tmp->next->line))
		{
			freeit = tmp->next;
			tmp->next = tmp->next->next;
			freeit->next = NULL;
			free(freeit->line);
			free(freeit);
			break ;
		}
		tmp = tmp->next;
	}
}

void	remove_var(char *arg)
{
	t_env	*tmp;

	if (!ft_strcmp_export(arg, g_var->envc->line))
	{
		tmp = g_var->envc;
		g_var->envc = g_var->envc->next;
		tmp->next = NULL;
		free(tmp->line);
		free(tmp);
	}
	else
		remove_inside(arg);
}

void	ft_unset(t_parser *prog)
{
	int		i;

	i = 1;
	g_var->status = 0;
	if (!g_var->envc || !prog->args[i])
		return ;
	while (prog->args[i])
	{
		if (prog->args[i][0] == '#')
			return ;
		if (!valid_name(prog->args[i]))
			identifier_error(prog->args[i], "unset");
		else
			remove_var(prog->args[i]);
		i++;
	}
}
