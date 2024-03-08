/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:24:56 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/08 18:58:23 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*add_node(char *full_line, char **cmd)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->data = cmd_data(full_line, cmd);
	if (!new_node->data)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_cmd_node	*cmd_data(char *full_line, char **cmd)
{
	t_cmd_node	*new_node;

	new_node = malloc(sizeof(t_cmd_node));
	if (!new_node)
		return (NULL);
	new_node->full_line = ft_strdup(full_line);
	if (!new_node->full_line)
	{
		free(new_node);
		return (NULL);
	}
	new_node->cmds = cmd;
	return (new_node);
}

void	pipex_freecmd(void *node)
{
	t_cmd_node	*d;

	d = (struct s_cmd_node *)node;
	free(d->full_line);
	ft_free_matrix(&d->cmds);
	free(d);
}

void	*pipex_exit(t_cmd_data *d, char *av, int err, char ***cmd)
{
	if (err < 1 || av)
		pipex_perror(av, err);
	if (cmd)
		ft_free_matrix(cmd);
	if (d)
	{
		close(d->infd);
		close(d->outfd);
		close(STDIN_FILENO);
		if (d->cmds)
			ft_lstclear(&d->cmds, pipex_freecmd);
		if (d->envp)
			ft_free_matrix(&d->envp);
		free(d);
	}
	exit(0);
	return (0);
}

void	pipex_perror(char *param, int err)
{
	if (err == NO_FILE)
		fd_putstr_fd("No_file_Error", 2);
	if (err == NO_PERM)
		fd_putstr_fd("No_permission_access_Error", 2);
	if (err == INV_ARGS)
		fd_putstr_fd("Invalid_argument_number_Error", 2);
	if (err == NO_MEMORY)
		fd_putstr_fd("Memory_assignment_Error", 2);
	if (err == NO_PATH)
		fd_putstr_fd("Path_inaccessible_Error", 2);
	if (err == DUP2_ERROR)
		fd_putstr_fd("DUP2_Error", 2);
	if (err == EXECVE_ERROR)
		fd_putstr_fd("EXECVE_CMD_Error", 2);
	if (err == PIPE_ERROR)
		fd_putstr_fd("PIPE_Error", 2);
	if (err == FORK_ERROR)
		fd_putstr_fd("FORK_Error", 2);
	if (err == NO_CMD)
		fd_putstr_fd("CMD_Error", 2);
	if ((param && NO_FILE) || NO_PERM || EXECVE_ERROR || NO_CMD)
		fd_putstr_fd(param, 2);
	fd_putstr_fd("\n", 2);
}
