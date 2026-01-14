/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:37:25 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/14 19:39:05 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer/lexer.h"
#include "core/stdio.h"
#include "ansi.h"

/**
 * @brief Returns the string representation of a token type.
 *
 * @param t The token.
 * @return The string representation of the token type.
 */
static const char	*get_data(t_token t)
{
	return ((const char *[]){"error", "word", "var", "asgn", "<", ">", "<>",
		">>", "<<", "<<??", "<<<", "<&", ">&", "<(", ">(", "|", "&&", "||", ";",
		"&", "\\n", "$(", "(", ")", "$((", "))", "[", "]", "[[", "]]", ";;",
		";&", ";;&", "if", "then", "else", "fi", "while", "do", "done", "for",
		"in", "case", "esac", "select", "time", "function", "coproc", "until",
		"elif", "comment", "EOF"}[t.type]);
}

/**
 * @brief Prints the details of a token.
 *
 * @param token The token to print.
 */
void	print_token(t_token token)
{
	ft_printf(ANSI_ITALIC ANSI_WHITE "Token" ANSI_RESET " ");
	ft_printf("<" ANSI_YELLOW "%s" ANSI_RESET"> ", get_data(token));
	ft_printf("{" ANSI_BLUE " type" ANSI_RESET ": ");
	ft_printf(ANSI_YELLOW "%i" ANSI_RESET "," ANSI_BLUE " pos" ANSI_RESET
		": {" ANSI_YELLOW " row" ANSI_RESET ": ", token.type);
	ft_printf(ANSI_YELLOW "%i" ANSI_RESET "," ANSI_YELLOW " col" ANSI_RESET
		": ", token.pos.row);
	ft_printf(ANSI_YELLOW "%i" ANSI_RESET "," ANSI_YELLOW " start" ANSI_RESET
		": ", token.pos.col);
	ft_printf(ANSI_YELLOW "%i" ANSI_RESET "," ANSI_YELLOW " len" ANSI_RESET
		": ", token.pos.start);
	ft_printf(ANSI_YELLOW "%i" ANSI_RESET " }\n", token.pos.len);
}
