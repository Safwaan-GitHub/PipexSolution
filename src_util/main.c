/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:47:18 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/08 17:05:31 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*parse_command(t_cmd_data *d, int ac, char **av)
{
	char	**cmd;
	char	*full_line;
	int	i;
	int	temp;
	t_list	*cmds;

	i = 1;
	cmds = NULL;
	full_line = NULL;
	while (++i < ac - 1)
	{
		d->cmds = cmds;
		cmd = ft_split(av[i], ' ');
		if (!cmd || !*cmd)
			return ((t_list *)pipex_exit(d, NULL, NO_CMD, &cmd));
		temp = get_line(*cmd, &full_line, d);
		if (!*cmd || temp == -1)
			return (pipex_exit(d, *cmd, NO_CMD, &cmd));
		if (temp == -2)
			return (pipex_exit(d, NULL, NO_MEMORY, &cmd));
		ft_lstadd_back(&cmds, add_node(full_line, cmd));
		free(full_line);
	}
	return (cmds);
}

int	get_line(char *cmd, char **full_line, t_cmd_data *d)
{
	int	i;
	char	*temp;

	i = -1;
	*full_line = NULL;
	while (d->envp && d->envp[++i])
	{
		free(*full_line);
		temp = ft_strjoin(d->envp[i], "/");
		if (!temp)
			return (-2);
		*full_line = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_line)
			return (-2);
		if (access(*full_line, F_OK) == 0)
			break ;
	}
	if (!d->envp && !d->envp[i])
	{
		free(*full_line);
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_cmd_data	*d;

	if (ac != 5)
		return (*(int *)pipex_exit(NULL, NULL, INV_ARGS, NULL));
	if (access(av[1], F_OK) == -1)
		return (*(int *)pipex_exit(NULL, av[1], NO_FILE, NULL));
	if (access(av[1], R_OK) == -1)
		return (*(int *)pipex_exit(NULL, av[1], NO_PERM, NULL));
	d = pop_data(ac, av, 0, env);
	d->cmds = parse_command(d, ac, av);
	pipex(d, env);
	return (*(int *)pipex_exit(d, NULL, END, NULL));
}
