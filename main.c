/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/11 17:12:15 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_var(t_shell *m)
{
	m->input = NULL;
	m->lexer = NULL;
	m->exec.env_path = ft_split(getenv("PATH"), ':');
	m->exec.pathname = NULL;
}

void	free_tokens(t_lexer *lexer)
{
	t_lexer	*temp;

	while (lexer)
	{
		temp = lexer;
		lexer = lexer->next;
		free(temp->str);
		free(temp);
	}
}

void	free_env_path(t_exec *exec)
{
	int	x;

	x = 0;
	while (exec->env_path[x])
	{
		free(exec->env_path[x]);
		x++;
	}
	free(exec->env_path);
}

void	prompt_loop(t_shell *m)
{
	int	count;
	int	status;

	count = 0;
	while (count < 3)
	{
		m->input = readline(PROMPT);
		add_history(m->input);
		m->lexer = init_lexer(m->input);
		command_exists(&m->exec);
		free(m->input);
		free_tokens(m->lexer);
		if (m->exec.pathname)       ////TEST
			free(m->exec.pathname); ////TEST
		free(m->exec.argv[0]);      ////TEST
		free(m->exec.argv);         ////TEST
		count++;
	}
	free_env_path(&m->exec); ////TEST
	rl_clear_history();
}

int	main(void)
{
	t_shell	m;

	init_var(&m);
	prompt_loop(&m);
	return (0);
}
