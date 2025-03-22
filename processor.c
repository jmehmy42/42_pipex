/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:22:40 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/22 13:05:57 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_processor(t_pipex *pipex, char *comm_input, const char *envp[],
		int *fd)
{
	char	**commands;

	if (dup2(fd[1], STDOUT_FILENO) < 0)
		print_error(ERR_FILE);
	if (dup2(pipex->infile, STDIN_FILENO) < 0)
	{
		free(pipex->path);
		close(fd[1]);
		print_error(ERR_W);
	}
	close(fd[1]);
	close(pipex->infile);
	commands = ft_splits(comm_input, ' ');
	if (!commands || !commands[0])
	{
		free(pipex->path);
		free_string(commands);
		close(pipex->infile);
		close(pipex->outfile);
		ft_putstr_fd("empty command\n", 2);
		exit(EXIT_FAILURE);
	}
	make_path(pipex, commands, envp);
	free_string(commands);
}

void	output_processor(t_pipex *pipex, char *comm_input, const char *envp[],
		int *fd)
{
	char	**commands;

	if (dup2(fd[0], STDIN_FILENO) < 0)
		print_error(ERR_FILE);
	if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
	{
		free(pipex->path);
		close(pipex->infile);
		close(fd[0]);
		print_error(ERR_W);
	}
	close(fd[0]);
	close(pipex->outfile);
	commands = ft_splits(comm_input, ' ');
	if (!commands || !commands[0])
	{
		free(pipex->path);
		free_string(commands);
		close(pipex->outfile);
		close(pipex->infile);
		ft_putstr_fd("empty command\n", 2);
		exit(EXIT_FAILURE);
	}
	make_path(pipex, commands, envp);
	free_string(commands);
}
