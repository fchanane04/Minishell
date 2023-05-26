/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 05:08:51 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 01:43:21 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	leaks_hunter(char ***str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = *str;
	if (tmp)
	{
		while (tmp[i])
		{
			free(tmp[i]);
			tmp[i] = NULL;
			i++;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	export_free(char **arr, char ***split)
{
	char	*ar;

	ar = *arr;
	free(ar);
	arr = NULL;
	leaks_hunter(split);
	split = NULL;
}
