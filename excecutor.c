/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:06:18 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/05 14:02:23 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_dir(t_shell *m)
{
	char			*path;
	DIR				*directory;
	struct dirent	*entry;
	bool 			exists;

	path = "/bin";
	directory = opendir(path);
	while (1)
	{
		entry = readdir(directory);
		if (!entry)
			break ;
		if (!ft_strncmp(m->input, entry->d_name, ft_strlen(m->input)))
		{
			exists = true;
			break;
		}
	}
	if (!exists)
		printf("%s: command not found\n", m->input);
	//else
	//	excecute(m);
}

void	excecute(t_shell *m)
{
	pid_t pid;
	const char *pathname = "/bin/echo";

	char *const argv[] = {
		"echo",        // argv[0]: The name of the program (conventionally)
		"-n",          // argv[1]: Argument to the program
		"hello world", // argv[2]: Argument to the program
		NULL           // Must be terminated by NULL
	};

	pid = fork();
	if (pid == 0)
		execve(pathname, argv, NULL);
}