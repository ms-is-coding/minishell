/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:22:29 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/06 16:33:51 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell.h"

typedef int	(*t_builtin_fn)(t_shell	*sh, int argc, char **argv, char **envp);

int	builtin_cd(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_echo(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_env(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_exec(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_exit(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_export(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_false(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_pwd(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_true(t_shell *sh, int argc, char **argv, char **envp);
int	builtin_unset(t_shell *sh, int argc, char **argv, char **envp);

#endif
