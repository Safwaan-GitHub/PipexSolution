/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanoor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:57:52 by sanoor            #+#    #+#             */
/*   Updated: 2024/03/13 16:37:18 by sanoor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>

enum e_pipex_error
{
	END = 1,
	NO_FILE = 0,
	NO_PERM = -1,
	INV_ARGS = -2,
	NO_MEMORY = -3,
	NO_PATH = -4,
	DUP2_ERROR = -5,
	EXECVE_ERROR = -6,
	PIPE_ERROR = -7,
	FORK_ERROR = -8,
	NO_CMD = -9
};

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

t_list  *parse_command(t_cmd_data *d, int ac, char **av);
t_cmd_data      *pop_data(int ac, char **av, int here_doc, char **env);
t_cmd_node      *cmd_data(char *full_line, char **cmd);
t_list  *add_node(char *full_line, char **cmd);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

int     get_line(char *cmd, char **full_line, t_cmd_data *d);
int     fd_putstr_fd(char *str, int fd);
int     ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

void    *pipex(t_cmd_data *d, char **env);
void    *child_process(t_cmd_data *d, int fd[2], t_list *lst, char **env);
void	ft_lstadd_back(t_list **lst, t_list *newnode);
void    ft_lstclear(t_list **cmds, void (*del)(void *));
void    *pipex_exit(t_cmd_data *d, char *av, int err, char ***cmd);
void    pipex_perror(char *param, int err);
void    pipex_freecmd(void *node);
void    ft_free_matrix(char ***cmd);

#endif
