/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:48:59 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/05 14:12:42 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_var(t_shell *m)
{
	m->input = NULL;
	m->lexer = NULL;
	m->path = getenv("PATH");
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

void	prompt_loop(t_shell *m)
{
	int	count;
	int	status;

	count = 0;
	while (count < 1)
	{
		m->input = readline(PROMPT);
		add_history(m->input);
		m->lexer = init_lexer(m->input);
		check_dir(m);
		free(m->input);
		free_tokens(m->lexer);
		count++;
	}
	rl_clear_history();
}

int	main(void)
{
	t_shell	m;

	init_var(&m);
	prompt_loop(&m);
	// excecute();
	return (0);
}
