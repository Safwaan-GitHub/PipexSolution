/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:52 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/06 20:19:20 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct	s_list
{
	void	*data;
	struct s_list	*next;
}	t_list;

typedef struct	s_cmd_data
{
	int		infd;
	int		outfd;
	int		here_doc;
	t_list	*cmds;
	char	**envp;
}	t_cmd_data;

typedef struct	s_cmd_node
{
	char	*full_line;
	char	**cmds;
}	t_cmd_node;

int     get_line(char *cmd, char **full_line, t_cmd_data *d);
t_list  *parse_command(t_cmd_data *d, int ac, char **av);
t_cmd_data      *pop_data(int ac, char **av, int here_doc, char **env);
t_cmd_node      *cmd_data(char *full_line, char **cmd);
t_list  *add_node(char *full_line, char **cmd);
void    pipex(t_cmd_data *d, char **env);
void    child_process(t_cmd_data *d, int fd[2], t_list *lst, char **env);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *newnode);

#endif
