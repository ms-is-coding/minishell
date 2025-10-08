/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:10:17 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 14:01:08 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "builtins.h"
#include "shell.h"
#include "vm/vm_internal.h"
#include <stdbool.h>
#include <unistd.h>

struct s_builtin
{
	const char		*cmd;
	t_builtin_fn	fn;
};

static char	*find_exec(char *arg)
{
	const char	*paths[] = {
		"./", "/", "/bin", "/usr/bin", "/usr/local/bin",
		"/sbin", "/usr/sbin", "/usr/local/sbin", NULL};
	char		*path;
	int			i;
	size_t		len;

	i = -1;
	if (!arg)
		return (NULL);
	while (paths[++i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(arg) + 2;
		path = ft_malloc(len);
		if (!path)
			return (NULL);
		ft_snprintf(path, len, "%s/%s", paths[i], arg);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

static t_builtin_fn	find_builtin(char *arg)
{
	static struct s_builtin	builtins[] = {
	{"cd", builtin_cd}, {"echo", builtin_echo}, {"exec", builtin_exec},
	{"exit", builtin_exit}, {"false", builtin_false}, {"true", builtin_true},
	{":", builtin_true}, {"pwd", builtin_pwd}, {"env", builtin_env},
	{"export", builtin_export},
	{NULL, NULL}};
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
	if (vm->prev_fd != STDIN_FILENO)
		dup2(vm->prev_fd, STDIN_FILENO);
	if (vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO)
		dup2(vm->pipe_fd[STDOUT_FILENO], STDOUT_FILENO);
	close_pipes(vm);
}

static bool	is_special_builtin(t_builtin_fn fn)
{
	return (fn == builtin_exec
		|| fn == builtin_cd
		|| fn == builtin_exit
		|| fn == builtin_export
	);
}

static bool	is_command_in_pipeline(t_vm *vm)
{
	return (vm->prev_fd != STDIN_FILENO
		|| vm->pipe_fd[STDIN_FILENO] != STDIN_FILENO
		|| vm->pipe_fd[STDOUT_FILENO] != STDOUT_FILENO);
}

void	vm_exec(t_vm *vm, t_program *program)
{
	char			**env;
	char			*exec;
	t_builtin_fn	builtin;
	int				pid;
	t_shell			*sh;
	int				exit_code;

	(void)program;
	sh = vm->shell;
	env = env_build(&sh->env, vm->frame.arena);
	vm->frame.argv[vm->frame.i] = NULL;
	builtin = find_builtin(vm->frame.argv[0]);
	if (is_special_builtin(builtin) && !is_command_in_pipeline(vm))
	{
		builtin(sh, vm->frame.argc, vm->frame.argv, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		setup_fds(vm);
		builtin = find_builtin(vm->frame.argv[0]);
		if (builtin)
		{
			exit_code = builtin(sh, vm->frame.argc, vm->frame.argv, env);
			sh_destroy(sh);
			exit(exit_code);
		}
		exec = find_exec(vm->frame.argv[0]);
		if (!exec)
		{
			ft_printf("command not found: %s\n", vm->frame.argv[0]);
			sh_destroy(sh);
			exit(127);
		}
		execve(exec, vm->frame.argv, env);
		free(exec);
		ft_printf("execve failed: %m\n");
		sh_destroy(sh);
		exit(1);
	}
	else if (pid < 0)
		ft_printf("fork failed: %m\n");
	if (vm->prev_fd != 0)
		close(vm->prev_fd);
	if (vm->pipe_fd[1] != 1)
		close(vm->pipe_fd[1]);
	vm->prev_fd = vm->pipe_fd[0];
	vm->pipe_fd[0] = 0;
	vm->pipe_fd[1] = 1;
	ft_vector_push(&vm->pids, ft_gen_val(TYPE_OTHER, (t_any){.i32 = pid}));
	allocator_arena_free(vm->allocator, vm->frame.arena);
}
