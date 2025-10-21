/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:10:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/21 23:04:53 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "builtins/builtins.h"
#include "shell.h"
#include "vm/vm_internal.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

struct s_builtin
{
	const char		*cmd;
	t_builtin_fn	fn;
};

static char	*find_exec(const char *arg, const char *env_path)
{
	static char	path[PATH_MAX];
	size_t		len;

	if (!arg)
		return (NULL);
	while (ft_strchr(env_path, ':'))
	{
		len = ft_strcspn(env_path, ":");
		ft_snprintf(path, PATH_MAX, "%.*s/%s", (int)len, env_path, arg);
		if (access(path, X_OK) == 0)
			return (path);
		env_path += len + 1;
	}
	return ((char *)(intptr_t)arg);
}

static t_builtin_fn	find_builtin(char *arg)
{
	static struct s_builtin	builtins[] = {
	{"cd", builtin_cd}, {"echo", builtin_echo}, {"exec", builtin_exec},
	{"exit", builtin_exit}, {"false", builtin_false}, {"true", builtin_true},
	{":", builtin_true}, {"pwd", builtin_pwd}, {"env", builtin_env},
	{"export", builtin_export}, {"alias", builtin_alias},
	{"unalias", builtin_unalias}, {"type", builtin_type},
	{"unset", builtin_unset}, {"readonly", builtin_readonly}, {NULL, NULL}};
	int						i;

	i = -1;
	while (builtins[++i].fn)
	{
		if (ft_strcmp(builtins[i].cmd, arg) == 0)
			return (builtins[i].fn);
	}
	return (NULL);
}

static void	close_pipes(t_vm *vm)
{
	if (vm->prev_fd > 2)
		close(vm->prev_fd);
	if (vm->pipe_fd[STDIN_FILENO] > 2)
		close(vm->pipe_fd[STDIN_FILENO]);
	if (vm->pipe_fd[STDOUT_FILENO] > 2)
		close(vm->pipe_fd[STDOUT_FILENO]);
}

static void	sh_destroy(t_shell *sh)
{
	cli_destroy(&sh->cli);
	ft_vector_free(&sh->vm.exit_codes);
	ft_vector_free(&sh->vm.pids);
	allocator_destroy(&sh->allocator);
	close_pipes(&sh->vm);
}

static void	setup_fds(t_vm *vm)
{
	int	i;

	/*
	ft_dprintf(2, "===== FDS =====\n");
	ft_dprintf(2, "prev_fd: %6i\n", vm->prev_fd);
	ft_dprintf(2, "pipe[0]: %6i\n", vm->pipe_fd[0]);
	ft_dprintf(2, "pipe[1]: %6i\n", vm->pipe_fd[1]);
	i = -1;
	while (++i < vm->redir_count)
	{
		ft_dprintf(2, "[%i].file: %5i\n", i, vm->redirs[i].file_fd);
		ft_dprintf(2, "[%i].target: %3i\n", i, vm->redirs[i].target_fd);
	}
	*/
	if (vm->prev_fd != STDIN_FILENO)
		dup2(vm->prev_fd, STDIN_FILENO);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		dup2(vm->pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
	i = -1;
	while (++i < vm->redir_count)
		dup2(vm->redirs[i].file_fd, vm->redirs[i].target_fd);
	close_pipes(vm);
}

static void	reset_fds(t_vm *vm)
{
	int	i;

	if (vm->prev_fd != STDIN_FILENO)
		close(vm->prev_fd);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(vm->pipe_fd[1]);
	vm->prev_fd = vm->pipe_fd[STDIN_FILENO];
	vm->pipe_fd[STDIN_FILENO] = STDIN_FILENO;
	vm->pipe_fd[STDOUT_FILENO] = STDOUT_FILENO;
	i = -1;
	while (++i < vm->redir_count)
	{
		if (vm->redirs[i].file_fd >= 0)
			close(vm->redirs[i].file_fd);
	}
	vm->redir_count = 0;
}

static bool	is_command_in_pipeline(t_vm *vm)
{
	return (vm->prev_fd != STDIN_FILENO
		|| vm->pipe_fd[STDIN_FILENO] != STDIN_FILENO
		|| vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO);
}

void	vm_spawn(t_vm *vm, t_program *program)
{
	char			**env;
	char			*exec;
	t_builtin_fn	builtin;
	int				pid;
	t_shell			*sh;
	int				exit_code;

	if (vm->pids.length == 0)
		vm->exit_codes.length = 0;
	if (vm->had_error)
	{
		vm->had_error = false;
		ft_vector_push(&vm->exit_codes,
			ft_gen_val(TYPE_OTHER, (t_any){.i32 = 1}));
		return ;
	}
	(void)program;
	sh = vm->shell;
	if (vm->frame.argc == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			setup_fds(vm);
			sh_destroy(vm->shell);
			_exit(0);
		}
		if (pid > 0)
			ft_vector_push(&vm->pids,
				ft_gen_val(TYPE_OTHER, (t_any){.i32 = pid}));
		reset_fds(vm);
		allocator_arena_free(vm->allocator, vm->frame.arena);
		return ;
	}
	env = env_build(&sh->env, vm->frame.arena);
	vm->frame.argv[vm->frame.argc] = NULL;
	builtin = find_builtin(vm->frame.argv[0]);
	if (builtin && !is_command_in_pipeline(vm))
	{
		auto int saved_stdin = dup(STDIN_FILENO);
		auto int saved_stdout = dup(STDOUT_FILENO);
		auto int saved_stderr = dup(STDERR_FILENO);
		setup_fds(vm);
		exit_code = builtin(sh, vm->frame.argc, vm->frame.argv, env);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stderr, STDERR_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		close(saved_stderr);
		ft_vector_push(&vm->exit_codes,
			ft_gen_val(TYPE_OTHER, (t_any){.i32 = exit_code}));
		close_pipes(vm);
		vm->redir_count = 0;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		setup_fds(vm);
		if (builtin)
		{
			exit_code = builtin(sh, vm->frame.argc, vm->frame.argv, env);
			sh_destroy(sh);
			exit(exit_code);
		}
		exec = find_exec(vm->frame.argv[0], env_get(&sh->env, "PATH"));
		if (!exec)
		{
			ft_dprintf(2, "command not found: %s\n", vm->frame.argv[0]);
			sh_destroy(sh);
			exit(127);
		}
		execve(exec, vm->frame.argv, env);
		if (exec != vm->frame.argv[0])
			free(exec);
		ft_dprintf(2, "execve failed: %m\n");
		sh_destroy(sh);
		exit(1);
	}
	else if (pid < 0)
		ft_dprintf(2, "fork failed: %m\n");
	reset_fds(vm);
	ft_vector_push(&vm->pids, ft_gen_val(TYPE_OTHER, (t_any){.i32 = pid}));
	allocator_arena_free(vm->allocator, vm->frame.arena);
	return ;
}
