/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:47:34 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 16:43:44 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_cmt(t_lexer *lexer)
{
	while (lexer->next_char != '\n'
		&& lexer->next_char != '\0')
		lexer_next(lexer);
	return (lexer_emit(lexer, TOK_COMMENT));
}
