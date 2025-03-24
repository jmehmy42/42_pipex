/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:48:50 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/24 14:01:05 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error_infile(t_pipex *pipex, int *fd)
{
	perror("Problems with infile files");
	close(fd[1]);
	pipex->infile = open("/dev/null", O_RDONLY);
	if (pipex->infile < 0)
	{
		perror("Error opening /dev/null");
		free(pipex->path);
		exit(EXIT_FAILURE);
	}
}

void	handle_files(t_pipex *pipex, char *argv[], int *fd)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		print_error_infile(pipex, fd);
	pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		if (pipex->infile >= 0)
			close(pipex->infile);
		close(fd[0]);
		close(fd[1]);
		print_error(ERR_FILE);
		close(pipex->infile);
		free(pipex->path);
		exit(EXIT_FAILURE);
	}
}

void	ft_pipex(t_pipex *pipex, int *fd, char *argv[], const char *envp[])
{
	handle_files(pipex, argv, fd);
	find_path(pipex, envp);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		print_error(ERR_W);
	else if (pipex->pid1 == 0)
	{
		close(fd[0]);
		input_processor(pipex, argv[2], envp, fd);
		exit(0);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		print_error(ERR_W);
	else if (pipex->pid2 == 0)
	{
		close(fd[1]);
		output_processor(pipex, argv[3], envp, fd);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	close_and_wait(pipex);
}

int	main(int argc, char *argv[], const char *envp[])
{
	int		fd[2];
	t_pipex	pipex;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror("Pipe failed");
			exit(EXIT_FAILURE);
		}
		ft_pipex(&pipex, fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	return (0);
}
