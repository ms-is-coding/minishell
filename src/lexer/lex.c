/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:02:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 16:59:18 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "token.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

bool	is_operator(unsigned char c)
{
	return (ft_isspace(c) || c == '|' || c == '&'
		|| c == '<' || c == '>' || c == ';'
		|| c == '`' || c == '(' || c == ')'
		|| c == '\'' || c == '"' || c == '\\'
		|| c == '\0' || c == 0x7fu);
}

char	lexer_next(t_lexer *lexer)
{
	if (lexer->input[lexer->i] == '\0')
		return ('\0');
	lexer->col++;
	lexer->i++;
	lexer->len++;
	if (lexer->input[lexer->i - 1] == '\n')
	{
		lexer->row++;
		lexer->col = 1;
	}
	return (lexer->input[lexer->i - 1]);
}

bool	lexer_match(t_lexer *lexer, char c)
{
	if (lexer->input[lexer->i] == c)
	{
		lexer_next(lexer);
		return (true);
	}
	return (false);
}

t_token	lexer_emit(t_lexer *lexer, t_token_type type)
{
	t_token	tok;

	tok.type = type;
	tok.fd = lexer->fd;
	tok.pos.start = lexer->i - lexer->len;
	tok.pos.col = lexer->col - lexer->len;
	tok.pos.row = lexer->row;
	tok.pos.len = lexer->len;
	return (tok);
}

t_token	lex_error(t_lexer *lexer)
{
	return (lexer_emit(lexer, TOK_ERROR));
}

t_token	lex_delim(t_lexer *lexer)
{
	if (lexer_match(lexer, ';'))
		return (lexer_emit(lexer, TOK_DOUBLE_SEMI));
	return (lexer_emit(lexer, TOK_SEMI));
}

t_token	lex_eof(t_lexer *lexer)
{
	return (lexer_emit(lexer, TOK_EOF));
}

t_token	lex_pipe(t_lexer *lexer)
{
	if (lexer_match(lexer, '|'))
		return (lexer_emit(lexer, TOK_OR));
	return (lexer_emit(lexer, TOK_PIPE));
}

t_token	lex_group(t_lexer *lexer)
{
	if (lexer->input[lexer->i - 1] == '(')
		return (lexer_emit(lexer, TOK_PAREN_OPEN));
	return (lexer_emit(lexer, TOK_PAREN_CLOSE));
}

t_token	lex_redir_in(t_lexer *lexer)
{
	if (lexer_match(lexer, '<'))
	{
		if (lexer_match(lexer, '<'))
			return (lexer_emit(lexer, TOK_REDIR_HERESTRING));
		return (lexer_emit(lexer, TOK_REDIR_HEREDOC));
	}
	if (lexer_match(lexer, '&'))
		return (lexer_emit(lexer, TOK_REDIR_DUP_IN));
	return (lexer_emit(lexer, TOK_REDIR_IN));
}

t_token	lex_redir_out(t_lexer *lexer)
{
	if (lexer_match(lexer, '>'))
		return (lexer_emit(lexer, TOK_REDIR_APPEND));
	if (lexer_match(lexer, '&'))
		return (lexer_emit(lexer, TOK_REDIR_DUP_OUT));
	return (lexer_emit(lexer, TOK_REDIR_OUT));
}

t_token	lex_amp(t_lexer *lexer)
{
	if (lexer_match(lexer, '&'))
	{
		if (lexer_match(lexer, ';'))
			return (lexer_emit(lexer, TOK_DOUBLE_SEMI_AMP));
		return (lexer_emit(lexer, TOK_AND));
	}
	if (lexer_match(lexer, ';'))
		return (lexer_emit(lexer, TOK_SEMI_AMP));
	return (lexer_emit(lexer, TOK_BACKGROUND));
}

t_token	lex_word(t_lexer *lexer)
{
	while (true)
	{
		if (lexer->input[lexer->i] == '\\')
		{
			lexer_next(lexer);
			lexer_next(lexer);
		}
		if (is_operator(lexer->input[lexer->i]))
			break ;
		lexer_next(lexer);
	}
	return (lexer_emit(lexer, TOK_WORD));
}

t_token	lex_number(t_lexer *lexer)
{
	lexer->fd = lexer->input[lexer->i - 1] - '0';
	while (lexer->input[lexer->i] >= '0'
		&& lexer->input[lexer->i] <= '9')
	{
		if (lexer->fd > INT_MAX / 10 || (
				lexer->fd == INT_MAX / 10 && lexer->input[lexer->i] > '7'))
			return (lexer->fd = 1, lex_word(lexer));
		lexer->fd = (lexer->fd << 3) + (lexer->fd << 1)
			+ (lexer_next(lexer) - '0');
	}
	if (lexer_match(lexer, '>'))
		return (lex_redir_out(lexer));
	if (lexer_match(lexer, '<'))
		return (lex_redir_in(lexer));
	lexer->fd = 1;
	return (lex_word(lexer));
}

t_token	lex_letter_e(t_lexer *lexer)
{
	if (lexer_match(lexer, 'l'))
	{
		if (lexer_match(lexer, 's')
			&& lexer_match(lexer, 'e')
			&& is_operator(lexer->input[lexer->i]))
			return (lexer_emit(lexer, TOK_ELSE));
		if (lexer_match(lexer, 'i')
			&& lexer_match(lexer, 'f')
			&& is_operator(lexer->input[lexer->i]))
			return (lexer_emit(lexer, TOK_ELIF));
	}
	return (lex_word(lexer));
}

t_token	lex_letter_i(t_lexer *lexer)
{
	if (lexer_match(lexer, 'f') && is_operator(lexer->input[lexer->i]))
		return (lexer_emit(lexer, TOK_IF));
	if (lexer_match(lexer, 'n') && is_operator(lexer->input[lexer->i]))
		return (lexer_emit(lexer, TOK_IN));
	return (lex_word(lexer));
}

t_token	lex_letter_t(t_lexer *lexer)
{
	if (lexer_match(lexer, 'i')
		&& lexer_match(lexer, 'm')
		&& lexer_match(lexer, 'e')
		&& is_operator(lexer->input[lexer->i]))
		return (lexer_emit(lexer, TOK_TIME));
	if (lexer_match(lexer, 'h')
		&& lexer_match(lexer, 'e')
		&& lexer_match(lexer, 'n')
		&& is_operator(lexer->input[lexer->i]))
		return (lexer_emit(lexer, TOK_THEN));
	return (lex_word(lexer));
}

t_token	lex_letter_w(t_lexer *lexer)
{
	if (lexer_match(lexer, 'h')
		&& lexer_match(lexer, 'i')
		&& lexer_match(lexer, 'l')
		&& lexer_match(lexer, 'e')
		&& is_operator(lexer->input[lexer->i]))
		return (lexer_emit(lexer, TOK_WHILE));
	return (lex_word(lexer));
}

t_token	lex_comment(t_lexer *lexer)
{
	while (lexer->input[lexer->i] != '\n' && lexer->input[lexer->i] != '\0')
		lexer_next(lexer);
	return (lexer_emit(lexer, TOK_COMMENT));
}

t_token	lex_dquote(t_lexer *lexer)
{
	bool	err;

	err = false;
	while (lexer->input[lexer->i] != '"')
	{
		if (lexer->input[lexer->i] == '\n'
			|| lexer->input[lexer->i] == '\0')
		{
			err = true;
			break ;
		}
		if (lexer->input[lexer->i] == '\\')
			lexer_next(lexer);
		lexer_next(lexer);
	}
	if (err)
		return (lexer_emit(lexer, TOK_ERROR));
	lexer_next(lexer);
	return (lexer_emit(lexer, TOK_WORD));
}

t_token	lex_squote(t_lexer *lexer)
{
	bool	err;

	err = false;
	while (lexer->input[lexer->i] != '\'')
	{
		if (lexer->input[lexer->i] == '\n'
			|| lexer->input[lexer->i] == '\0')
		{
			err = true;
			break ;
		}
		lexer_next(lexer);
	}
	if (err)
		return (lexer_emit(lexer, TOK_ERROR));
	lexer_next(lexer);
	return (lexer_emit(lexer, TOK_WORD));
}

t_token	lex_dollar(t_lexer *lexer)
{
	if (lexer_match(lexer, '('))
	{
		if (lexer_match(lexer, '('))
			return (lexer_emit(lexer, TOK_MATH_OPEN));
		return (lexer_emit(lexer, TOK_SUB_OPEN));
	}
	return (lex_word(lexer));
}

#define KEY0 "\x1b[94m"
#define KEY1 "\x1b[96m"
#define TEXT "\x1b[93m"
#define VALUE "\x1b[93m"
#define CLEAR "\x1b[m"
#define ITALIC "\x1b[3m"
#define GREY "\x1b[37m"

static const char *get_data(t_token t)
{
	return ((const char *[]){"error", "word", "var", "asgn", "<", ">", ">>",
		"<<", "<<??", "<<<", "<&", ">&", "<(", ">(", "|", "&&", "||", ";", "&",
		"\\n", "$(", "(", ")", "$((", "))", "[", "]", "[[", "]]", ";;", ";&", ";;&", "if",
		"then", "else", "fi", "while", "do", "done", "for", "in", "case",
		"esac", "select", "time", "function", "coproc", "until", "elif",
		"comment", "EOF"}[t.type]);
}

void	print_token(t_token token)
{
	printf(ITALIC GREY"Token"CLEAR" ");
	printf("<"TEXT"%s"CLEAR"> ", get_data(token));
	printf("{"KEY0" type"CLEAR": ");
	printf(VALUE"%i"CLEAR","KEY0" pos"CLEAR": {"KEY1" row"CLEAR": ",
		token.type);
	printf(VALUE"%i"CLEAR","KEY1" col"CLEAR": ", token.pos.row);
	printf(VALUE"%i"CLEAR","KEY1" start"CLEAR": ", token.pos.col);
	printf(VALUE"%i"CLEAR","KEY1" len"CLEAR": ", token.pos.start);
	printf(VALUE"%i"CLEAR" }\n", token.pos.len);
}
