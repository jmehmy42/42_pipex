/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:54:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/10 18:58:02 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_path(t_pipex *pipex, char **commands, const char *envp[])
{
	int		i;

	i = 0;
	pipex->path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pipex->path = ft_strdup(&envp[i][5]);
			break;
		}
		i++;
	}
	if (!pipex->path)
		print_error(ERR_C);
	split_path(pipex, commands, envp);
}

void	split_path(t_pipex *pipex, char **commands, const char *envp[])
{
	int		i;
	char	*temp_path;
	char	*full_path;

	pipex->paths = ft_split(pipex->path, ':');
	if (!pipex->paths)
		exit_command(pipex, commands);
	i = 0;
	while (pipex->paths[i] != NULL)
	{
		temp_path = ft_strjoin(pipex->paths[i], "/");
		full_path = ft_strjoin(temp_path, commands[0]);
		free(temp_path);
		execute_command_if_valid(pipex, commands, envp, full_path);
		free(full_path);
		i++;
	}
	exit_command(pipex, commands);
}
