#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct	s_data
{
	int		fd1;
	int		acr_fd1;
	int		fd2;
	char	**cmds1;
	int		acces_cmd1;
	int		s_cmds1;
	char	**cmds2;
	int		acces_cmd2;
	int		s_cmds2;
	char	**path;
	char	**pathname1;
	char	**pathname2;
	char	**env;
	char	*line_zero;
	int		len_path;
	int		exc1;
	int		abs1;
	int		exc2;
	int		abs2;
}	t_data;


// LIBFT
size_t	ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);

// PIPEX UTILS 1
int		ft_readaccess(char *file);
void	ft_pathdup(t_data *data);
void	ft_pathfound(t_data *data);
int		ft_accessfound(char **pathname, char *cmd, t_data *data);

// PIPEX UTILS 2
void	ft_cmdpathname(t_data *data);
void	ft_split_cmds(t_data *data, char **av);

// CHILDREN PROCESS
void	process_child1(int fd, t_data *data, int pipefd[2]);
void	process_child2(int fd, t_data *data, int pipefd[2]);

// FREE
void	ft_free_strs(char **strs, int index);
void	ft_close(t_data *data, int exit_code);

// MAIN
void	init_data(t_data *data);
void	exc_or_abs(t_data *data);
void	pipex_utils(t_data *data, char **av);
void	ft_pipex(t_data *data, char **av);

#endif
