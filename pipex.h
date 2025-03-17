/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehmy <jmehmy@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:50:35 by jmehmy            #+#    #+#             */
/*   Updated: 2025/03/16 21:49:58 by jmehmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "includes/libft/libft.h"
# include "stdio.h"
# include "stdlib.h"
# include "sys/wait.h"
# include "unistd.h"

# define ERR_FILE "Problems with file"
# define ERR_C "Problems with commands"
# define ERR_W "Something went wrong"

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	char	*path;
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
}			t_pipex;

void		ft_pipex(t_pipex *pipex, int *fd, char *argv[], const char *envp[]);
void		input_processor(t_pipex *pipex, char *comm_input,
				const char *envp[], int *fd);
void		output_processor(t_pipex *pipex, char *comm_input,
				const char *envp[], int *fd);
void		find_path(t_pipex *pipex, const char *envp[]);
void		split_path(t_pipex *pipex, char **commands, const char *envp[]);
void		print_error(char *str);
void		handle_files(t_pipex *pipex, char *argv[]);
void		execute_command_if_valid(t_pipex *pipex, char **commands,
				const char *envp[], char *full_path);
void		clean_pipex(t_pipex *pipex, char **commands);
void		close_and_wait(t_pipex *pipex, int *fd);
void		clean_and_exit(t_pipex *pipex, char **commands);
#endif
