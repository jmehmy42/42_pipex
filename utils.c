/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:54:13 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/10 18:57:44 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup_pipex(t_pipex *pipex, char **commands)
{
	free_string(pipex->paths);
	free_string(commands);
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
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}

void	print_error(char *str)
{
	perror(str);
	exit(1);
}
void	execute_command_if_valid(t_pipex *pipex, char **commands, const char *envp[], char *full_path)
{
	if (access(full_path, F_OK | X_OK) == 0)
		{
			if (execve(full_path, commands, (char *const *)envp) == -1)
			{
				free(full_path);
				cleanup_pipex(pipex, commands);
				print_error(ERR_W);
			}
		}
}
void	exit_command(t_pipex *pipex, char **commands)
{
	perror("command not found");
	free(pipex->path);
	cleanup_pipex(pipex, commands);
	exit(127);
}