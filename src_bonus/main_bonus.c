/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:14:43 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/13 16:18:56 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_str(char *delim, char *buff, char *ret)
{
	char	c[2];
	char	*temp;

	c[1] = '\0';
	while (!buff || ft_strlen(buff) - 1 != ft_strlen(delim) ||
			ft_strncmp(delim, buff, ft_strlen(buff) - 1))
	{
		temp = ret;
		ret = ft_strjoin(ret, buff);
		free(temp);
		free(buff);
		buff = NULL;
		*c = 0;
		while (*c != '\n')
		{
			read(0, c, 1);
			temp = buff;
			ft_strjoin(buff, c);
			free(temp);
		}
	}
	free(buff);
	return (ret);
}

int	get_infd(t_cmd_data *d, char *str)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		pipex_exit(d, NULL, PIPE_ERROR, NULL);
	pid = fork();
	if (pid == -1)
		pipex_exit(d, NULL, FORK_ERROR, NULL);
	if (!pid)
	{
		close(fd[0]);
		write(fd[1], str, ft_strlen(str));
		close(fd[1]);
		free(str);
		return(*(int *)pipex_exit(d, NULL, END, NULL));
	}
	close(fd[1]);
	free(str);
	return (fd[0]);
}

int	get_line(char *cmd, char **full_line, t_cmd_data *d)
{
	int	i;
	char	*temp;

	i = -1;
	while (d->envp[i] && d->envp[++i])
	{
		free(*full_line);
		temp = ft_strjoin(d->envp[i], "/");
		if (!temp)
			return (-2);
		*full_line = ft_strjoin(temp, cmd);
		if (!full_line)
			return (-2);
		free(temp);
		if (access(*full_line, R_OK) == 0)
			break ;
	}
	if (!d->envp && !d->envp[i])
	{
		free(*full_line);
		return (-1);
	}
	return (0);
}

t_list	*parse_commands(t_cmd_data *d, int ac, char **av)
{
	char	*full_line;
	char	**cmd;
	t_list	*cmds;
	int		temp;
	int		i;

	i = 1;
	cmds = NULL;
	full_line = NULL;
	while (++i < ac - 1)
	{
		d->cmds = cmds;
		cmd = ft_split(av[i], ' ');
		if (!cmd && !d->cmds)
			return ((t_list *)pipex_exit(d, NULL, NO_CMD, &cmd));
		temp = get_line(*cmd, &full_line, d);
		if (temp == -2)
			return (pipex_exit(d, NULL, NO_MEMORY, &cmd));
		if (temp == -1)
			return (pipex_exit(d, *cmd, NO_CMD, &cmd));
		ft_lstadd_back(&cmds, add_node(full_line, cmd));
		free(full_line);
	}
	return (cmds);
}

int	main(int ac, char **av, char **env)
{
	t_cmd_data	*d;
	int	here_doc;
	
	if (ac < 5)
		return (*(int *)pipex_exit(NULL, NULL, INV_ARGS, NULL));
	here_doc = !ft_strncmp(av[1], "here_doc", ft_strlen(av[1]));
	if (!here_doc && access(av[1], F_OK) == -1)
		return (*(int *)pipex_exit(NULL, av[1], NO_FILE, NULL));
	if (!here_doc && access(av[1], R_OK) == -1)
		return (*(int *)pipex_exit(NULL, av[1], NO_PERM, NULL));
	d = pop_data(ac, av, here_doc, env);
	d->here_doc = here_doc;
	if (here_doc)
	{
		if (ac-- < 6)
			return (*(int *)pipex_exit(d, NULL, INV_ARGS, NULL));
		d->infd = get_infd(d, get_str(av[2], NULL, NULL));
	}
	else
		d->infd = open(av[1], O_RDONLY);
	d->cmds = parse_commands(d, ac, av);
	pipex(d, env);
	return (*(int *)pipex_exit(d, NULL, END, NULL));
}
