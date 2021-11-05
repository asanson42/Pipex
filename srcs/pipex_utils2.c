#include "pipex.h"

static int	cmd_size(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

void	ft_cmdpathname(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->len_path)
	{
		data->pathname1[i] = ft_strjoin(data->pathname1[i], data->cmds1[0]);
		data->pathname2[i] = ft_strjoin(data->pathname2[i], data->cmds2[0]);
		i++;
	}
}

void	ft_split_cmds(t_data *data, char **av)
{
	data->cmds1 = ft_split(av[2], ' ');
	data->s_cmds1 = cmd_size(data->cmds1);
	if (data->s_cmds1 == 0)
		ft_close(data, 1);
	data->cmds2 = ft_split(av[3], ' ');
	data->s_cmds2 = cmd_size(data->cmds2);
	if (data->s_cmds2 == 0)
		ft_close(data, 1);
}
