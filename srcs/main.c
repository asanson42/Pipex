#include "pipex.h"

void	init_data(t_data *data)
{
	data->fd1 = 0;
	data->acr_fd1 = 0;
	data->fd2 = 0;
	data->cmds1 = NULL;
	data->acces_cmd1 = 0;
	data->s_cmds1 = 0;
	data->cmds2 = NULL;
	data->acces_cmd2 = 0;
	data->s_cmds2 = 0;
	data->path = NULL;
	data->pathname1 = NULL;
	data->pathname2 = NULL;
	data->env = NULL;
	data->line_zero = NULL;
	data->len_path = 0;
	data->exc1 = 0;
	data->abs1 = 0;
	data->exc2 = 0;
	data->abs2 = 0;
}

void	exc_or_abs(t_data *data)
{
	if (ft_strncmp(data->cmds1[0], "/", 1) == 0)
		data->abs1 = 1;
	if (ft_strncmp(data->cmds1[0], "./", 2) == 0)
		data->exc1 = 1;
	if (ft_strncmp(data->cmds2[0], "/", 1) == 0)
		data->abs2 = 1;
	if (ft_strncmp(data->cmds2[0], "./", 2) == 0)
		data->exc2 = 1;
}

void	pipex_utils(t_data *data, char **av)
{
	data->acr_fd1 = ft_readaccess(av[1]);
	ft_pathfound(data);
	ft_pathdup(data);
	ft_split_cmds(data, av);
	ft_cmdpathname(data);
	exc_or_abs(data);
	if (data->abs1 == 0 && data->exc1 == 0 && data->fd1 > -1)
		data->acces_cmd1 = ft_accessfound(data->pathname1, data->cmds1[0], data);
	if (data->abs2 == 0 && data->exc2 == 0)
		data->acces_cmd2 = ft_accessfound(data->pathname2, data->cmds2[0], data);
}

void	ft_pipex(t_data *data, char **av)
{
	int		pipefd[2];
	pid_t	child1;
	pid_t	child2;
	int		status;

	pipex_utils(data, av);
	if (pipe(pipefd) == -1)
		exit(1);
	child1 = fork();
	if (child1 < 0)
		exit(1);
	else if (child1 == 0)
		process_child1(data->fd1, data, pipefd);
	child2 = fork();
	if (child2 < 0)
		exit(1);
	else if (child2 == 0)
		process_child2(data->fd2, data, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	ft_close(data, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data);
	if (argc != 5)
	{
		ft_putstr_fd("Should be executed: ./pipex file1 cmd1 cmd2 file2\n", 1);
		exit(1);
	}
	data.fd1 = open(argv[1], O_RDONLY);
	data.fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (data.fd2 < 3)
	{
		perror(argv[4]);
		exit(1);
	}
	data.env = envp;
	ft_pipex(&data, argv);
	return (0);
}
