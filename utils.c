/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:54:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/13 14:06:47 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_pipex(t_pipex *pipex, char **commands)
{
	free_string(pipex->paths);
	free_string(commands);
}

void	clean_and_exit(t_pipex *pipex, char **commands)
{
	perror("command not found");
	free(pipex->path);
	clean_pipex(pipex, commands);
	exit(127);
}

void	close_and_wait(t_pipex *pipex, int *fd)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &status, 0);
	if (status >= 0)
		exit(status >> 8);
	else
		exit(1);
}

void	print_error(char *str)
{
	perror(str);
	exit(1);
}
