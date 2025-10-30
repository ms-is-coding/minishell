/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:34:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 16:43:16 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer_internal.h"

t_token	lex_pip(t_lexer *lexer)
{
	if (lexer_match(lexer, '|'))
		return (lexer_emit(lexer, TOK_OR));
	return (lexer_emit(lexer, TOK_PIPE));
}
