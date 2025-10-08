/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:47:34 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 17:07:41 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"
#include "token.h"

t_token	lex_comment(t_lexer *lexer)
{
	while (lexer->input[lexer->i + 1] != '\n'
		&& lexer->input[lexer->i + 1] != '\0')
		lexer_next(lexer);
	return (lexer_emit(lexer, TOK_COMMENT));
}
