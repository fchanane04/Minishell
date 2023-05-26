/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:10:54 by nel-brig          #+#    #+#             */
/*   Updated: 2022/12/05 00:55:55 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	reset_pwd_status(char *cwd)
{
	free(cwd);
	cwd = getcwd(NULL, 0);
	change_pwd(&g_var->envc, cwd, "PWD");
	reset_cd_status(g_var->status);
}

void	free_cd(char **cwd, char **line)
{
	char	*cwdd;
	char	*linee;

	cwdd = *cwd;
	linee = *line;
	free(cwdd);
	free(linee);
}

void	chdir_stat(char *arg)
{
	int	stat;

	stat = chdir(arg);
	if (stat != 0)
		cd_error(arg);
}
