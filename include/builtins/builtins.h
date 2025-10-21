/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:22:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/21 22:28:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

typedef enum e_error
{
	ERR_NONE,
	ERR_INVALID_NAME,
	ERR_TOO_MANY_ARGS,
	ERR_INVALID_OPT,
	ERR_INVALID_ALIAS,
	ERR_INVALID_UNALIAS,
	ERR_INVALID_ID,
	ERR_NO_HOME,
	ERR_NO_OLDPWD,
	ERR_BAD_SET,
	ERR_BAD_RM,
	ERR_TOO_LONG,
	ERR_NOT_NUMERIC,
	ERR_NOT_FOUND,
	ERR_NO_PERM,
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

int			builtin_alias(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_cd(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_echo(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_env(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_exec(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_exit(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_export(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_false(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_pwd(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_readonly(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_true(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_type(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_unalias(t_shell *sh, int argc, char **argv, char **envp);
int			builtin_unset(t_shell *sh, int argc, char **argv, char **envp);

t_context	ctx(const char *builtin, const char *subject);
int			builtin_error(t_context ctx, t_error err, int int_code);

#endif
