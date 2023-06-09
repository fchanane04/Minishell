/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:05:49 by fchanane          #+#    #+#             */
/*   Updated: 2022/12/05 03:13:57 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

char	*create_heredoc_name(int i)
{
	char	*tty;
	char	*name;
	char	**split;
	char	*heredoc;
	char	*t;

	tty = ft_strdup(ttyname(0));
	split = ft_split_exec(tty, 'v');
	name = ft_strjoin_exec("/tmp", split[1]);
	t = ft_itoa(i);
	heredoc = ft_strjoin_exec(name, t);
	free(t);
	leaks_hunter(&split);
	free(name);
	free(tty);
	return (heredoc);
}

int	open_and_write(char *filename, char *name)
{
	int		fd;
	pid_t	pid;
	char	*line;

	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (!line)
				exit(1);
			if (!ft_strcmp(line, filename))
			{
				free (line);
				exit(1);
			}
			print_line_expanded(line, fd);
		}
	}
	exit_status(pid);
	return (fd);
}

char	*save_in(char *name)
{
	if (!name)
		return (ft_strdup("NO"));
	else
		return (name);
}

char	*loop_heredoc(t_files *file, int i)
{
	int		fd;
	char	*name;

	name = NULL;
	while (file)
	{
		if (file->type == DEL)
		{
			g_var->check = 1;
			name = create_heredoc_name(i);
			fd = open_and_write(file->filename, name);
			if (g_var->flag == -3)
				return (NULL);
			close(fd);
			if (check_other_heredoc(file->next))
			{
				unlink(name);
				free(name);
			}
		}
		file = file->next;
	}
	if (!name)
		name = ft_strdup("NO");
	return (name);
}

char	**ft_heredoc(t_parser *prog)
{
	t_parser	*tmp;
	t_files		*file;
	char		*name;
	char		**save;
	int			i;

	tmp = prog;
	i = 0;
	save = malloc(sizeof(char *) * (list_counter(prog) + 1));
	while (tmp)
	{
		file = tmp->files;
		name = loop_heredoc(file, i);
		if (file && !name)
			return (NULL);
		if (g_var->check)
			save[i] = save_in(name);
		else
			save[i] = ft_strdup("NO");
		tmp = tmp->next;
		g_var->check = 0;
		i++;
	}
	save[i] = NULL;
	return (save);
}
