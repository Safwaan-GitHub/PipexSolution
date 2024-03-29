/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:24:41 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/13 16:29:02 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_lstclear(t_list **cmds, void (*del)(void *))
{
	t_list	*start;
	t_list	*temp;

	start = *cmds;
	temp = NULL;
	while (start)
	{
		temp = start;
		start = start->next;
		del(temp->data);
		free(temp);
	}
	*cmds = NULL;
}
