/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:27:16 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 16:53:43 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "core/stdlib.h"

t_result	lexer_init(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->end = false;
	lexer->curr_char = '\0';
	lexer->next_char = input[0];
	lexer->i = 0;
	lexer->col = 1;
	lexer->row = 1;
	lexer->len = 0;
	lexer->fd = -1;
	return (RESULT_OK);
}
