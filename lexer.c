/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandre-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:20:24 by sandre-a          #+#    #+#             */
/*   Updated: 2024/09/11 20:24:05 by sandre-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"

t_tokens	token_type(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (PIPE);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (REDIR_APPEND);
	else
		return (WORD);
}

t_lexer	*get_last_token(t_lexer *lexer)
{
	while (lexer->next)
		lexer = lexer->next;
	return (lexer);
}

t_lexer	*get_first_token(t_lexer *lexer)
{
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

void	add_to_token_list(t_lexer **lexer, char *str)
{
	t_lexer	*new_token;
	t_lexer	*temp;

	if (!*str)
		return ;
	new_token = malloc(sizeof(t_lexer));
	new_token->str = str;
	new_token->token = token_type(str);
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

char	*ft_strpbrk(const char *s, const char *c)
{
	const char	*str = s;
	int			i;

	while (*str)
	{
		i = 0;
		while (c[i])
		{
			if (*str == c[i])
				return ((char *)str);
			i++;
		}
		str++;
	}
	return (NULL);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*t_s;
	char	*new_str;
	char	*start;

	t_s = (char *)s;
	i = 0;
	new_str = malloc((n + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*t_s && i < n)
	{
		*new_str = *t_s;
		new_str++;
		t_s++;
		i++;
	}
	*new_str = 0;
	return (start);
}

int	count_quotes(char *input, char quote_type)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == quote_type)
			count++;
		input++;
	}
	if (count % 2 == 1)
	{
		printf("Invalid quote usage\n");
		exit(EXIT_FAILURE);
	}
	return (count);
}

char	*handle_quotes(char *input)
{
	int		count;
	char	quote_type;

	if (*input == '\'')
		quote_type = '\'';
	else
		quote_type = '\"';
	count = count_quotes(input, quote_type);
	while (count - 1)
	{
		input++;
		input = ft_strchr(input, quote_type);
		count--;
	}
	return (input);
}

char	*tokenize_input(char **input)
{
	char	*str;
	char	*start;
	int		length;

	start = *input;
	*input = ft_strpbrk(*input, " >|<\'\"");
	if (*input)
	{
		if (**input == '\'' || **input == '\"')
		{
			*input = handle_quotes(*input);
			start++;
		}
	}
	if (*input)
		length = (start - (*input)++) * -1;
	else
		length = ft_strlen(start);
	str = malloc(sizeof(char) * length + 1);
	ft_strlcpy(str, start, length + 1);
	return (str);
}

void	analyse_tokens(t_lexer **lexer)
{
	t_lexer	*temp;

	temp = *lexer;
	while (*lexer)
	{
		if (((*lexer)->token == REDIR_IN && (*lexer)->next->token == REDIR_IN)
			|| ((*lexer)->token == REDIR_OUT
				&& (*lexer)->next->token == REDIR_OUT))
		{
			free((*lexer)->str);
			if ((*lexer)->next->token == REDIR_IN)
				(*lexer)->str = ft_strdup("<<");
			else
				(*lexer)->str = ft_strdup(">>");
			temp = (*lexer)->next->next;
			free((*lexer)->next->str);
			free((*lexer)->next);
			(*lexer)->next = temp;
			(*lexer)->token = token_type((*lexer)->str);
			temp->prev = *lexer;
			return ;
		}
		*lexer = (*lexer)->next;
	}
}

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;
	char	*token;

	lexer = NULL;
	while (input)
	{
		token = tokenize_input(&input);
		add_to_token_list(&lexer, token);
		if (input)
			if (ft_strchr("><|", *(input - 1)))
				add_to_token_list(&lexer, ft_strndup((input - 1), 1));
	}
	analyse_tokens(&lexer);
	lexer = get_first_token(lexer);
	return (lexer);
}
