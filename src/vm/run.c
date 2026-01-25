/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:18:40 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 14:02:28 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
#include "vector/vector.h"
#include "core/stdio.h"
#include "shell.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

/**
 * @brief Dispatches the opcode to the corresponding handler function.
 *
 * @param opcode The opcode to dispatch
 * @return The handler function for the given opcode, or NULL if invalid.
 */
static t_exec_handler	dispatch_opcode(t_opcode opcode)
{
	if (opcode < 0 || opcode >= OP_COUNT)
		return (NULL);
	return ((t_exec_handler[OP_COUNT]){
		[OP_CMD] = vm_command,
		[OP_ARG] = vm_arg,
		[OP_EXEC] = vm_exec,
		[OP_OUT] = vm_redir_out,
		[OP_IN] = vm_redir_in,
		[OP_JUMP] = vm_jump,
		[OP_HEREDOC] = vm_heredoc,
	}[opcode]);
}

/**
 * @brief Signal handler for SIGINT and SIGQUIT.
 *
 * @param sig Signal number
 */
static void	sig_handler(int sig)
{
	t_shell	*sh;

	sh = get_shell(0);
	if (!sh->vm.active)
	{
		if (sig == SIGINT)
			rl_replace_line("", 0);
		rl_clear_visible_line();
		rl_redraw_prompt_last_line();
		rl_redisplay();
	}
}

/**
 * @brief Runs the virtual machine with the given program.
 *
 * @param vm Pointer to the virtual machine instance
 * @param program Pointer to the program to execute
 */	
void	vm_run(t_vm *vm, t_program *program)
{
	t_exec_handler	handler;

	vm->prev_fd = 0;
	vm->pipe_fd[STDIN_FILENO] = STDIN_FILENO;
	vm->pipe_fd[STDOUT_FILENO] = STDOUT_FILENO;
	program->pc = 0UL;
	vm->active = true;
	vm->redir_count = 0;
	vec_clear(vm->exit_codes);
	signal(SIGINT, SIG_IGN);
	while (program->pc < program->len)
	{
		handler = dispatch_opcode(program->data[program->pc] & OPCODE_MASK);
		if (!handler)
		{
			ft_printf("FATAL: SIGILL (%02hhx) at %lx\n",
				program->data[program->pc], program->pc);
			exit(128 + SIGILL);
		}
		handler(vm, program);
	}
	signal(SIGINT, sig_handler);
	vm->last_exit_code = (int32_t)(int64_t)vec_get(vm->exit_codes, -1);
	vm->active = false;
}
