/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:29:14 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 17:25:04 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	TOK_ERROR,
	TOK_WORD,
	TOK_VAR,
	TOK_ASSIGNMENT,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_BOTH,
	TOK_REDIR_APPEND,
	TOK_REDIR_HEREDOC,
	TOK_REDIR_HEREDOC_QUOTED,
	TOK_REDIR_HERESTRING,
	TOK_REDIR_DUP_IN,
	TOK_REDIR_DUP_OUT,
	TOK_PROC_SUB_IN,
	TOK_PROC_SUB_OUT,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_SEMI,
	TOK_BACKGROUND,
	TOK_NEWLINE,
	TOK_SUB_OPEN,
	TOK_PAREN_OPEN,
	TOK_PAREN_CLOSE,
	TOK_MATH_OPEN,
	TOK_MATH_CLOSE,
	TOK_BRACE_OPEN,
	TOK_BRACE_CLOSE,
	TOK_DOUBLE_BRACKET_OPEN,
	TOK_DOUBLE_BRACKET_CLOSE,
	TOK_DOUBLE_SEMI,
	TOK_SEMI_AMP,
	TOK_DOUBLE_SEMI_AMP,
	TOK_IF,
	TOK_THEN,
	TOK_ELSE,
	TOK_FI,
	TOK_WHILE,
	TOK_DO,
	TOK_DONE,
	TOK_FOR,
	TOK_IN,
	TOK_CASE,
	TOK_ESAC,
	TOK_SELECT,
	TOK_TIME,
	TOK_FUNCTION,
	TOK_COPROC,
	TOK_UNTIL,
	TOK_ELIF,
	TOK_COMMENT,
	TOK_EOF,
	TOK_COUNT,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				fd;
	struct s_position {
		int	row;
		int	col;
		int	start;
		int	len;
	}	pos;
}	t_token;

#endif
