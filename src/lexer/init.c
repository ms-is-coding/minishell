/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:27:16 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/15 12:20:57 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "core/stdlib.h"

/**
 * @brief Initializes the lexer with the given input string.
 *
 * @param lexer Pointer to the lexer structure
 * @param input Input string to tokenize
 * @return Result of the initialization operation
 */
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
