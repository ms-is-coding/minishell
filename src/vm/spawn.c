/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:10:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/17 23:49:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "builtins/builtins.h"
#include "shell.h"
#include "vm/vm_internal.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

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
		if (access(path, F_OK) == 0)
			return (path);
		env_path += len + 1;
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
	env_destroy(&sh->env);
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

static void	run_empty_command(t_vm *vm)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_fds(vm);
		sh_destroy(vm->shell);
		_exit(0);
	}
	if (pid > 0)
		ignore((void *)ft_vector_push(&vm->pids,
				ft_gen_val(TYPE_OTHER, (t_any){.i32 = pid})));
	reset_fds(vm);
	allocator_arena_free(vm->allocator, vm->frame.arena);
	return ;
}

static int	execute_builtin(t_shell *sh, t_vm *vm, char **env)
{
	t_builtin_fn	builtin;
	int				exit_code;
	int				saved_stdin;
	int				saved_stdout;
	int				saved_stderr;

	builtin = _builtin_find(vm->frame.argv[0]);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	setup_fds(vm);
	exit_code = builtin(sh, vm->frame.argc, vm->frame.argv, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	close(saved_stderr);
	close_pipes(vm);
	vm->redir_count = 0;
	ignore((void *)ft_vector_push(&vm->exit_codes,
			ft_gen_val(TYPE_OTHER, (t_any){.i32 = exit_code})));
	return (exit_code);
}

void	vm_spawn(t_vm *vm)
{
	char			**env;
	char			*exec;
	int				pid;
	t_shell			*sh;
	t_builtin_fn	builtin;
	int				exit_code;

	if (vm->pids.length == 0)
		vm->exit_codes.length = 0;
	if (vm->had_error)
	{
		vm->had_error = false;
		ignore((void *)ft_vector_push(&vm->exit_codes,
				ft_gen_val(TYPE_OTHER, (t_any){.i32 = 1})));
		return ;
	}
	sh = vm->shell;
	if (vm->frame.argc == 0)
		run_empty_command(vm);
	env = env_build(&sh->env, vm->frame.arena);
	vm->frame.argv[vm->frame.argc] = NULL;
	builtin = _builtin_find(vm->frame.argv[0]);
	if (_builtin_find(vm->frame.argv[0]) && !is_command_in_pipeline(vm))
	{
		execute_builtin(sh, vm, env);
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
		if (ft_strchr(vm->frame.argv[0], '/'))
		{
			if (access(vm->frame.argv[0], X_OK | F_OK) == -1)
				ft_dprintf(2, "%s: %m\n", vm->frame.argv[0]);
			execve(vm->frame.argv[0], vm->frame.argv, env);
			ft_dprintf(2, "%s: cannot execute binary file: %m\n",
				vm->frame.argv[0]);
			exit(126);
		}
		exec = find_exec(vm->frame.argv[0], env_get(&sh->env, "PATH"));
		if (!exec)
		{
			ft_dprintf(2, "command not found: %s\n", vm->frame.argv[0]);
			sh_destroy(sh);
			exit(127);
		}
		execve(exec, vm->frame.argv, env);
		ft_dprintf(2, "%s: cannot execute binary file: %m\n", vm->frame.argv[0]);
		sh_destroy(sh);
		exit(126);
	}
	else if (pid < 0)
		ft_dprintf(2, "fork failed: %m\n");
	reset_fds(vm);
	ignore((void *)
		ft_vector_push(&vm->pids, ft_gen_val(TYPE_OTHER, (t_any){.i32 = pid})));
	allocator_arena_free(vm->allocator, vm->frame.arena);
}
