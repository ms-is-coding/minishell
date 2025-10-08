/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delim.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:32:43 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 18:32:56 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_delim(t_lexer *lexer)
{
	if (lexer_match(lexer, ';'))
		return (lexer_emit(lexer, TOK_DOUBLE_SEMI));
	return (lexer_emit(lexer, TOK_SEMI));
}
