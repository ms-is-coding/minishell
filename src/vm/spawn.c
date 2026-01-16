/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:10:17 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 17:26:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "builtins/builtins.h"
#include "shell.h"
#include "util/exec.h"
#include "vm/vm_internal.h"
#include "core/string.h"
#include "core/stdio.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Finds the executable path for a given command argument.
 *
 * @param arg The command argument to find the executable for
 * @param env_path The PATH environment variable string
 * @return The full path to the executable if found, NULL otherwise
 */
static char	*find_exec(const char *arg, const char *env_path)
{
	static char	path[PATH_MAX];
	size_t		len;

	if (!arg)
		return (NULL);
	if (!env_path)
	{
		if (access(arg, F_OK) == 0)
			return ((char *)(intptr_t)arg);
		return (NULL);
	}
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

/**
 * @brief Closes the pipes used in the virtual machine.
 *
 * @param vm Pointer to the virtual machine instance
 */
static void	close_pipes(t_vm *vm)
{
	if (vm->prev_fd > 2)
		close(vm->prev_fd);
	if (vm->pipe_fd[STDIN_FILENO] > 2)
		close(vm->pipe_fd[STDIN_FILENO]);
	if (vm->pipe_fd[STDOUT_FILENO] > 2)
		close(vm->pipe_fd[STDOUT_FILENO]);
}

/**
 * @brief Sets up the file descriptors for the command execution.
 *
 * @param vm Pointer to the virtual machine instance
 */
static void	setup_fds(t_vm *vm)
{
	int	i;

	if (vm->prev_fd != STDIN_FILENO)
		dup2(vm->prev_fd, STDIN_FILENO);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		dup2(vm->pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
	i = -1;
	while (++i < vm->redir_count)
		dup2(vm->redirs[i].file_fd, vm->redirs[i].target_fd);
	close_pipes(vm);
}

/**
 * @brief Resets the file descriptors in the virtual machine after command
 * execution.
 *
 * @param vm Pointer to the virtual machine instance
 */
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

/**
 * @brief Checks if the current command is part of a pipeline.
 *
 * @param vm Pointer to the virtual machine instance
 * @return true if the command is in a pipeline, false otherwise.
 */
static bool	is_command_in_pipeline(t_vm *vm)
{
	return (vm->prev_fd != STDIN_FILENO
		|| vm->pipe_fd[STDIN_FILENO] != STDIN_FILENO
		|| vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO);
}

/**
 * @brief Runs an empty command in the virtual machine.
 *
 * @param vm Pointer to the virtual machine instance
 */
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
		vec_push(vm->pids, (void *)(intptr_t)pid);
	reset_fds(vm);
	allocator_arena_free(vm->allocator, vm->frame.arena);
	return ;
}

/**
 * @brief Executes a built-in command in the virtual machine.
 *
 * @param sh Pointer to the shell structure
 * @param vm Pointer to the virtual machine instance
 * @param env Array of environment variables
 * @return Exit status code of the built-in command
 */
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
	vec_push(vm->exit_codes, (void *)(intptr_t)exit_code);
	return (exit_code);
}

/**
 * @brief Spawns a new process to execute a command in the virtual machine.
 *
 * @param vm Pointer to the virtual machine instance
 */
void	vm_spawn(t_vm *vm)
{
	char			**env;
	char			*exec;
	int				pid;
	t_shell			*sh;
	t_builtin_fn	builtin;
	int				exit_code;
	struct stat		path_stat;

	if (vm->had_error)
	{
		vm->had_error = false;
		vec_push(vm->exit_codes, (void *)1);
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
			if (stat(vm->frame.argv[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_dprintf(2, "%s: Is a directory\n", vm->frame.argv[0]);
					sh_destroy(sh);
					exit(126);
				}
			}
			if (access(vm->frame.argv[0], X_OK | F_OK) == -1)
			{
				ft_dprintf(2, "%s: %m\n", vm->frame.argv[0]);
				exit(127);
			}
			secure_execve(vm->frame.argv[0], vm->frame.argv, env);
			ft_dprintf(2, "%s: cannot execute binary file: %m\n",
				vm->frame.argv[0]);
			sh_destroy(sh);
			exit(126);
		}
		exec = find_exec(vm->frame.argv[0], env_get(&sh->env, "PATH"));
		if (!exec)
		{
			ft_dprintf(2, "command not found: %s\n", vm->frame.argv[0]);
			sh_destroy(sh);
			exit(127);
		}
		if (stat(vm->frame.argv[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				ft_dprintf(2, "%s: Is a directory\n", vm->frame.argv[0]);
				sh_destroy(sh);
				exit(126);
			}
		}
		secure_execve(exec, vm->frame.argv, env);
		ft_dprintf(2, "%s: cannot execute binary file: %m\n", vm->frame.argv[0]);
		sh_destroy(sh);
		exit(126);
	}
	else if (pid < 0)
		ft_dprintf(2, "fork failed: %m\n");
	reset_fds(vm);
	vec_push(vm->pids, (void *)(intptr_t)pid);
	allocator_arena_free(vm->allocator, vm->frame.arena);
}
