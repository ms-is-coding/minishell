/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:00:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 22:05:36 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "environ/environ.h"
# include "cli/cli.h"
# include "parser/parser.h"
# include "lexer/lexer.h"
# include "vm/vm.h"

typedef struct s_shell
{
	t_cli		cli;
	t_lexer		lexer;
	t_parser	parser;
	t_environ	env;
	t_vm		vm;
}	t_shell;

#endif
