/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 22:25:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 13:40:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "libft.h"
# include <stdbool.h>

typedef struct s_lexer
{
	char	*input;
	int		i;
	int		col;
	int		row;
	int		len;
	int		fd;

	char	reserved[4];
}	t_lexer;

t_result	lexer_init(t_lexer *lexer, char *line);

t_token		lexer_advance(t_lexer *lexer);
void		print_token(t_token token);

#endif
