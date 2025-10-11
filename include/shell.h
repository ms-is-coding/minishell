/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:00:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 16:18:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "allocator/allocator.h"
# include "expander/expander.h"
# include "parser/parser.h"
# include "lexer/lexer.h"
# include "alias/alias.h"
# include "cli/cli.h"
# include "env/env.h"
# include "vm/vm.h"

typedef struct s_shell
{
	t_allocator	allocator;
	t_expander	expander;
	t_parser	parser;
	t_lexer		lexer;
	t_alias		alias;
	t_cli		cli;
	t_env		env;
	t_vm		vm;
}	t_shell;

#endif
