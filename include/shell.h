/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:00:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:03 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "allocator/allocator.h"
# include "environ/environ.h"
# include "parser/parser.h"
# include "lexer/lexer.h"
# include "cli/cli.h"
# include "vm/vm.h"

typedef struct s_shell
{
	t_allocator	allocator;
	t_environ	environ;
	t_parser	parser;
	t_lexer		lexer;
	t_cli		cli;
	t_vm		vm;
}	t_shell;

#endif
