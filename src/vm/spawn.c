/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:10:17 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 19:48:45 by smamalig         ###   ########.fr       */
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
char	*find_exec(const char *arg, const char *env_path)
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

static void	vm_spawn_absolute(t_vm *vm, char **env)
{
	struct stat	path_stat;

	if (stat(vm->frame.argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_dprintf(2, "%s: Is a directory\n", vm->frame.argv[0]);
		sh_destroy(vm->shell);
		exit(126);
	}
	if (access(vm->frame.argv[0], X_OK | F_OK) == -1)
	{
		ft_dprintf(2, "%s: %m\n", vm->frame.argv[0]);
		exit(127);
	}
	secure_execve(vm->frame.argv[0], vm->frame.argv, env);
	ft_dprintf(2, "%s: cannot execute binary file: %m\n",
		vm->frame.argv[0]);
	sh_destroy(vm->shell);
	exit(126);
}

static void	vm_spawn_command(t_vm *vm, char **env)
{
	char		*exec;
	struct stat	path_stat;

	exec = find_exec(vm->frame.argv[0], env_get(&((t_shell *)vm->shell)->env,
				"PATH"));
	if (!exec)
	{
		ft_dprintf(2, "command not found: %s\n", vm->frame.argv[0]);
		sh_destroy(vm->shell);
		_exit(127);
	}
	if (stat(vm->frame.argv[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_dprintf(2, "%s: Is a directory\n", vm->frame.argv[0]);
		sh_destroy(vm->shell);
		_exit(126);
	}
	secure_execve(exec, vm->frame.argv, env);
	ft_dprintf(2, "%s: cannot execute binary file: %m\n", vm->frame.argv[0]);
	sh_destroy(vm->shell);
	_exit(126);
}

static void	vm_spawn_child(t_vm *vm, t_builtin_fn builtin, char **env)
{
	int			exit_code;

	setup_fds(vm);
	if (builtin)
	{
		exit_code = builtin(vm->shell, vm->frame.argc, vm->frame.argv, env);
		sh_destroy(vm->shell);
		exit(exit_code);
	}
	if (ft_strchr(vm->frame.argv[0], '/'))
		vm_spawn_absolute(vm, env);
	vm_spawn_command(vm, env);
}

/**
 * @brief Spawns a new process to execute a command in the virtual machine.
 *
 * @param vm Pointer to the virtual machine instance
 */
void	vm_spawn(t_vm *vm)
{
	char			**env;
	int				pid;
	t_builtin_fn	builtin;

	if (vm->had_error)
	{
		vm->had_error = false;
		vec_push(vm->exit_codes, (void *)1);
		return ;
	}
	if (vm->frame.argc == 0)
		run_empty_command(vm);
	env = env_build(&((t_shell *)vm->shell)->env, vm->frame.arena);
	vm->frame.argv[vm->frame.argc] = NULL;
	builtin = _builtin_find(vm->frame.argv[0]);
	if (_builtin_find(vm->frame.argv[0]) && !is_command_in_pipeline(vm))
		return (execute_builtin(vm->shell, vm, env));
	pid = fork();
	if (pid == 0)
		vm_spawn_child(vm, builtin, env);
	else if (pid < 0)
		ft_dprintf(2, "fork failed: %m\n");
	reset_fds(vm);
	vec_push(vm->pids, (void *)(intptr_t)pid);
	allocator_arena_free(vm->allocator, vm->frame.arena);
}
