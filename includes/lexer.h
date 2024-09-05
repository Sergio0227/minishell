/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:23:35 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/05 13:19:23 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
**     WORD,        	Represents commands and arguments (grep, cat, echo)
**     PIPE,          Represents the pipe operator (|)
**     REDIR_IN,      Represents input redirection (<)
**     REDIR_OUT,     Represents output redirection (>)
**     REDIR_APPEND,  Represents append redirection (>>)
**     REDIR_HEREDOC, Represents heredoc redirection (<<)
**     ENV_VAR,		Represents environment variable (VAR=value)
*/

typedef enum e_token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	ENV_VAR,
}					t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

t_lexer				*get_last_token(t_lexer *lexer);
t_lexer				*init_lexer(char *input);

#endif