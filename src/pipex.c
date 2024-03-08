/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:50:29 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/08 18:56:13 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd_data	*pop_data(int ac, char **av, int here_doc, char **env)
{
	t_cmd_data	*d;
	int			i;

	i = 0;
	d = malloc(sizeof(t_cmd_data));
	if (!d)
		return ((t_cmd_data *)pipex_exit(d, NULL, NO_MEMORY, NULL));
	d->envp = NULL;
	d->cmds = NULL;
	d->infd = open(av[1], O_RDONLY);
	if (d->infd == -1)
		return ((t_cmd_data *)pipex_exit(d, av[1], NO_FILE, NULL));
	if (!here_doc)
		d->outfd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (access(av[ac - 1], F_OK) == -1)
		return ((t_cmd_data *)pipex_exit(d, av[ac - 1], NO_FILE, NULL));
	if (access(av[ac - 1], R_OK) == -1)
		return ((t_cmd_data *)pipex_exit(d, av[ac - 1], NO_PERM, NULL));
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	d->envp = ft_split(env[i], ':');
	if (!d->envp)
		return ((t_cmd_data *)pipex_exit(d, NULL, NO_PATH, NULL));
	return (d);
}

void	*pipex(t_cmd_data *d, char **env)
{
	int		fd[2];
	pid_t	pid;
	t_list	*lst;

	lst = d->cmds;
	if (dup2(d->infd, STDIN_FILENO) == -1)
		return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
	close(d->infd);
	while (lst)
	{
		if (pipe(fd) == -1)
			return (pipex_exit(d, NULL, PIPE_ERROR, NULL));
		pid = fork();
		if (pid == -1)
			return (pipex_exit(d, NULL, FORK_ERROR, NULL));
		if (!pid)
			child_process(d, fd, lst, env);
		close(fd[1]);
		if (lst->next && dup2(fd[0], STDIN_FILENO) == -1)
			return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
		waitpid(pid, NULL, 0);
		close(fd[0]);
		lst = lst->next;
	}
	return (NULL);
}

void	*child_process(t_cmd_data *d, int fd[2], t_list *lst, char **env)
{
	t_cmd_node	*node;

	node = lst->data;
	if (lst->next && dup2(fd[1], STDOUT_FILENO) == -1)
		return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
	if (!lst->next && dup2(d->outfd, STDOUT_FILENO) == -1)
		return (pipex_exit(d, NULL, DUP2_ERROR, NULL));
	close(fd[1]);
	close(d->outfd);
	close(d->infd);
	execve(node->full_line, node->cmds, env);
	return (pipex_exit(d, NULL, EXECVE_ERROR, NULL));
}
