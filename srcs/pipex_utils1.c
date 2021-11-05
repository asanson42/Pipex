#include "pipex.h"

int	ft_readaccess(char *file)
{
	int	access_file;

	access_file = 0;
	if (access(file, R_OK) < 0)
	{
		access_file = -1;
		perror(file);
	}
	return (access_file);
}

static int	ft_sizepath(char **path)
{
	int	i;

	i = 0;
	while (path[i] && path[i][0] != '\0')
		i++;
	return (i);
}

void	ft_pathdup(t_data *data)
{
	int	i;
	
	i = 0;
	data->pathname2 = malloc(sizeof(char *) * (data->len_path + 1));
	while (i < data->len_path)
	{
		data->pathname2[i] = ft_strdup(data->pathname1[i]);
		i++;
	}
}

void	ft_pathfound(t_data *data)
{
	int	i;

	i = 0;
	while (!(ft_strncmp(data->env[i], "PATH=", 5) == 0))
		i++;
	data->path = ft_split(data->env[i], ':');
	data->line_zero = ft_substr(data->path[0], 5, ft_strlen(data->path[0]));
	data->len_path = ft_sizepath(data->path);
	data->pathname1 = malloc(sizeof(char * ) * (data->len_path + 1));
	i = 0;
	while (data->path[i])
	{
		if (i == 0)
		{
			data->pathname1[i] = ft_strdup(data->line_zero);
			data->pathname1[i] = ft_strjoin(data->pathname1[i], "/");
			i++;
		}
		data->pathname1[i] = ft_strdup(data->path[i]);
		data->pathname1[i] = ft_strjoin(data->pathname1[i], "/");
		i++;
	}
}

int	ft_accessfound(char **pathname, char *cmd, t_data *data)
{
	int	access_f;
	int	i;

	access_f = 0;
	i = 0;
	if (access(cmd, X_OK) == 0)
		access_f = 0;
	else
	{
		while (i < data->len_path)
		{
			if (access(pathname[i], X_OK) == 0)
			{
				access_f = 0;
				return (access_f);
			}
			i++;
		}
		access_f = -1;
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (access_f);
}
