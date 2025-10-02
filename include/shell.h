/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:00:10 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 13:39:33 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "environment.h"
# include "cli/cli.h"
# include "parser.h"
# include "lexer.h"

typedef struct s_shell
{
	t_cli			cli;
	t_lexer			lexer;
	t_parser		parser;
	t_environment	env;
	t_vector		pids;
	int				pipefd[2];
	int				prev_fd;
}	t_shell;

#endif
