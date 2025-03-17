/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:48:50 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/16 21:56:31 by jmehmy           ###   ########.fr       */
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
		print_error(ERR_FILE);
	close(pipex->infile);
	close(fd[1]);
	commands = ft_arg_split(comm_input, ' ');
	if (!commands || !commands[0])
	{
		free(pipex->path);
		free_string(commands);
		print_error(ERR_C);
	}
	split_path(pipex, commands, envp);
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
		print_error(ERR_FILE);
	}
	close(pipex->outfile);
	close(fd[0]);
	commands = ft_arg_split(comm_input, ' ');
	if (!commands || !commands[0])
	{
		free(pipex->path);
		free_string(commands);
		print_error(ERR_C);
	}
	split_path(pipex, commands, envp);
	free_string(commands);
}

void	handle_files(t_pipex *pipex, char *argv[])
{
	int	n;

	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		perror("Problems with files");
		pipex->infile = open("/dev/null", O_RDONLY);
		if (pipex->infile < 0)
			print_error(ERR_FILE);
	}
	pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		if (ft_strncmp(argv[2], "sleep ", 6) == 0)
		{
			n = ft_atoi(argv[2] + 6);
			if (n > 0)
				sleep(n);
		}
		print_error(ERR_FILE);
		free(pipex->path);
		exit(EXIT_FAILURE);
	}
}

void	ft_pipex(t_pipex *pipex, int *fd, char *argv[], const char *envp[])
{
	handle_files(pipex, argv);
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
	close_and_wait(pipex, fd);
}

int	main(int argc, char *argv[], const char *envp[])
{
	int		fd[2];
	t_pipex	pipex;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			print_error(ERR_C);
		ft_pipex(&pipex, fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	return (0);
}
