/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:22:29 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 12:09:51 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

typedef enum e_error
{
	ERR_NONE,
	ERR_OOM,
	ERR_TOO_MANY_ARGS,
	ERR_INVALID_OPT,
	ERR_INVALID_ID,
	ERR_NO_HOME,
	ERR_NO_OLDPWD,
	ERR_PREV_DIR,
	ERR_CURR_DIR,
	ERR_BAD_SET,
	ERR_READONLY,
	ERR_NOT_NUMERIC,
	ERR_404,
	ERR_NO_PERM,
	ERR_HELP_NOT_FOUND,
	ERR_HELP_DIRTY,
	ERR_HELP_EXCESS,
	ERR_ALLOC,
	ERR_PERROR,
	ERR_UNKNOWN,
	ERR_COUNT
}	t_error;

typedef struct s_context
{
	const char	*builtin;
	const char	*subject;
}	t_context;

typedef int	(*t_builtin_fn)(t_shell	*sh, int argc, char **argv, char **envp);

t_builtin_fn	_builtin_find(const char *name);

int				builtin_alias(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_cd(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_echo(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_env(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_exec(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_exit(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_export(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_false(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_logout(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_pwd(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_readonly(t_shell *sh, int argc, char **argv,
					char **envp);
int				builtin_return(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_set(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_true(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_type(t_shell *sh, int argc, char **argv, char **envp);
int				builtin_unalias(t_shell *sh, int argc, char **argv,
					char **envp);
int				builtin_unset(t_shell *sh, int argc, char **argv, char **envp);

int				builtin_help(t_shell *sh, int argc, char **argv, char **envp);

t_context		ctx(const char *builtin, const char *subject);
int				builtin_error(t_context ctx, t_error err, int int_code);

#endif
