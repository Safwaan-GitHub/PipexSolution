/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:43:02 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/13 16:28:05 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	fd_putstr_fd(char *str, int fd)
{
	if (str != NULL)
		return (write(fd, str, ft_strlen(str)));
	return (0);
}
