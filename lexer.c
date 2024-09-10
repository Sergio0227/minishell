/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/10 19:57:50 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

t_tokens	analyse_token(char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
	{
		while (*str != '=')
		{
			if (!ft_isalnum(*str) && *str != '_')
				return (WORD);
			str++;
		}
		return (ENV_VAR);
	}
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (REDIR_IN);
	else
		return (WORD);
}

t_lexer	*get_last_token(t_lexer *lexer)
{
	while (lexer->next)
		lexer = lexer->next;
	return (lexer);
}

void	add_to_token_list(t_lexer **lexer, char *str)
{
	t_lexer	*new_token;
	t_lexer	*temp;

	new_token = malloc(sizeof(t_lexer));
	new_token->str = str;
	new_token->token = analyse_token(str);
	new_token->next = NULL;
	new_token->prev = NULL;
	if (*lexer == NULL)
		*lexer = new_token;
	else
	{
		temp = *lexer;
		temp = get_last_token(*lexer);
		temp->next = new_token;
		new_token->prev = temp;
	}
}

void	create_token(t_lexer **lexer, char *str, int len)
{
	char	*token;

	token = malloc(sizeof(char) * len + 1);
	ft_strlcpy(token, str, len);
	add_to_token_list(lexer, token);
}

int	check_token_in_str(t_lexer **lexer, char *str)
{
	int		i;
	int		x;
	char	*charset;
	char	*start;

	i = 1;
	charset = "<>|";
	start = str;
	while (*str)
	{
		x = -1;
		while (charset[++x])
		{
			if (*str == charset[x])
			{
				create_token(lexer, start, i);
				i = 1;
				start = str;
				continue;
			}
		}
		i++;
		str++;
	}
	return (0);
}

t_lexer	*init_lexer(char *input)
{
	t_lexer *lexer;
	char *str;
	char *start;
	int length;

	lexer = NULL;
	while (input)
	{
		start = input;
		input = ft_strchr(input, ' ');
		if (input)
			length = (start - input++) * -1;
		else
			length = ft_strlen(start);
		str = malloc(sizeof(char) * length + 1);
		ft_strlcpy(str, start, length + 1);
		if (!check_token_in_str(&lexer, str))
			add_to_token_list(&lexer, str);
	}
	return (lexer);
}