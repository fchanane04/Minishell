/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 04:15:29 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 01:30:10 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	change_pwd(t_env **env, char *pwd, char *type)
{
	t_env	*tmp;
	char	*new_line;
	char	*typ;
	int		i;

	tmp = *env;
	i = 0;
	new_line = NULL;
	typ = ft_strjoin_exec(type, "=");
	new_line = ft_strjoin_exec(typ, pwd);
	free(typ);
	while (tmp)
	{
		if (!ft_strncmp(tmp->line, type, ft_strlen(type)))
		{
			free(tmp->line);
			tmp->line = new_line;
			return ;
		}
		tmp = tmp->next;
	}
	free(new_line);
}

void	cd_error(char *dir)
{
	ft_putstr_fd("bash: cd: ", 1);
	ft_putstr_fd(dir, 1);
	ft_putstr_fd(": ", 1);
	perror("");
	g_var->status = -101;
}

void	var_not_set(void)
{
	ft_putstr_fd("bash: cd: HOME not set\n", 2);
	g_var->status = 1;
}

void	reset_cd_status(int stat)
{
	if (stat == -101)
		g_var->status = 1;
	else
		g_var->status = 0;
}

void	ft_cd(t_parser	*prog)
{
	char	*line;
	char	*cwd;

	line = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		chdir(prog->args[1]);
	else
	{
		change_pwd(&g_var->envc, cwd, "OLDPWD");
		if (prog->args[1])
			chdir_stat(prog->args[1]);
		else
		{
			line = get_envc(g_var->envc, "HOME");
			if (!line)
				var_not_set();
			else
				chdir(line);
		}
		reset_pwd_status(cwd);
	}
	free_cd(&cwd, &line);
}
