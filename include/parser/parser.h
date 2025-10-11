/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:25:58 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 14:45:58 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer/lexer.h"
# include "vm/bytecode.h"
# include "libft.h"
# include <stdbool.h>

typedef struct s_parser
{
	t_lexer		*lexer;
	t_program	program;

	t_token		curr_token;
	t_token		prev_token;

	int			argc;
	bool		in_cmd;
	uint8_t		redirs;
	char		reserved[2];
}	t_parser;

typedef enum e_precedence
{
	PREC_NUL,
	PREC_LIT,
	PREC_PIPE,
	PREC_LIST,
	PREC_LOGIC,
	PREC_REDIR,
	PREC_MAX
}	t_precedence;

typedef t_result	(*t_nud_fn)(t_parser *, t_token);
typedef t_result	(*t_led_fn)(t_parser *, t_token);

typedef struct s_parse_rule
{
	t_precedence	precedence;
	char			reserved[4];
	t_nud_fn		nud;
	t_led_fn		led;
}	t_parse_rule;

t_parse_rule	parser_get_rule(t_token_type type);

void			print_error(t_parser *p, t_token token, const char *message);

t_result		parse_error(t_parser *p, t_token t);
t_result		parse_word(t_parser *p, t_token t);
t_result		parse_pipe(t_parser *p, t_token t);
t_result		parse_group(t_parser *p, t_token t);
t_result		parse_and(t_parser *p, t_token t);
t_result		parse_or(t_parser *p, t_token t);
t_result		parse_semi(t_parser *p, t_token t);
t_result		parse_r_out(t_parser *p, t_token t);
t_result		parse_r_in(t_parser *p, t_token t);

void			parser_advance(t_parser *p);
t_result		parser_consume(t_parser *p, t_token_type type, const char *err);
bool			parser_match(t_parser *p, t_token_type type);

t_result		parser_init(t_parser *p, t_lexer *lexer);
t_result		parser_parse(t_parser *p, char *line);
t_result		parser_parse_expr(t_parser *p, t_precedence prec);

#endif
