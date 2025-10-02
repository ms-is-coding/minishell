/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:27:16 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/01 21:59:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_result	lexer_init(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->i = 0;
	lexer->col = 1;
	lexer->row = 1;
	lexer->len = 0;
	lexer->fd = 1;
	return (RESULT_OK);
}
