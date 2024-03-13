/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:21:16 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/13 17:14:52 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd_data	*pop_data(int ac, char **av, int here_doc, char **env)
{
	t_cmd_data	*d;
	int			i;

	i = 0;
	d = malloc(sizeof(t_cmd_data));
	if (!d)
		return ((t_cmd_data *)pipex_exit(d, NULL, NO_MEMORY, NULL));
	d->cmds = NULL;
	d->envp = NULL;
	if (!here_doc)
		d->outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else
		d->outfd = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (access(av[ac - 1], F_OK) == -1)
		return ((t_cmd_data *)pipex_exit(d, av[ac - 1], NO_FILE, NULL));
	if (access(av[ac - 1], W_OK) == -1)
		return ((t_cmd_data *)pipex_exit(d, av[ac - 1], NO_PERM, NULL));
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	d->envp = ft_split(env[i], ':');
	if (!d->envp)
		return ((t_cmd_data *)pipex_exit(d, NULL, NO_PATH, NULL));
	return (d);
}

void	*child_process(t_cmd_data *d, int fd[2], t_list *lst, char **env)
{
	t_cmd_node	*node;

	node = lst->data;
	close(fd[0]);
	if (lst->next && dup2(fd[1], STDOUT_FILENO) == -1)
		return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
	if (!lst->next && dup2(d->outfd, STDOUT_FILENO) == -1)
		return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
	close(d->infd);
	close(d->outfd);
	close(fd[1]);
	execve(node->full_line, node->cmds, env);
	return (pipex_exit(d, NULL, EXECVE_ERROR, NULL));
}

void	*pipex(t_cmd_data *d, char **env)
{
	t_list	*cmd;
	int	fd[2];
	pid_t	pid;

	cmd = d->cmds;
	if (dup2(d->infd, STDIN_FILENO) == -1)
		return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
	close(d->infd);
	while (cmd)
	{
		if (pipe(fd) == -1)
			return (pipex_exit(d, NULL, PIPE_ERROR, NULL));
		pid = fork();
		if (pid == -1)
			return (pipex_exit(d, NULL, FORK_ERROR, NULL));
		if (!pid)
			child_process(d, fd, cmd, env);
		close(fd[1]);
		if (cmd->next && dup2(fd[0], STDIN_FILENO) == -1)
			return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
		waitpid(pid, NULL, 0);
		close(fd[0]);
		cmd = cmd->next;
	}
	return (NULL);
}
