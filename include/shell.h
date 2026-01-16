/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:00:10 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 16:29:53 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "allocator/allocator.h"
# include "expander/expander.h"
# include "parser/parser.h"
# include "lexer/lexer.h"
# include "cli/cli.h"
# include "env/env.h"
# include "vm/vm.h"

typedef struct s_shell
{
	t_allocator	allocator;
	t_expander	expander;
	t_parser	parser;
	t_lexer		lexer;
	t_cli		cli;
	t_env		env;
	t_vm		vm;

	bool		should_exit;
	char		reserved[7];
}	t_shell;

void	sh_destroy(t_shell *sh);

#endif
