/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:04:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/07 00:27:37 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env/env.h"
#include "shell.h"
#include "vm/vm_internal.h"
#include "common.h"
#include <stddef.h>

static char	*alloc_strndup(
	t_vm *vm,
	const char *s,
	const size_t n)
{
	char	*str;
	size_t	i;

	str = allocator_alloc(vm->allocator, n + 1, vm->frame.arena).data;
	if (!str)
		return (NULL);
	i = -1LU;
	while (++i < n)
		str[i] = s[i];
	str[i] = 0;
	return (str);
}

static char	*expand_argument(t_vm *vm, const char *arg)
{
	char	*expanded;

	(void)vm;
	expanded = (char *)(intptr_t)arg;
	if (ft_strcmp("$VERSION", arg) == 0
		|| ft_strcmp("$TRASH_VERSION", arg) == 0)
		expanded = (char *)(intptr_t)TRASH_VERSION;
	else if (arg[0] == '$')
		expanded = (char *)(intptr_t)env_get(
				&((t_shell *)vm->shell)->env, arg + 1);
	return (expanded);
}

void	vm_arg(t_vm *vm, t_program *program)
{
	size_t	len;

	len = program->data[++program->pc];
	vm->frame.argv[vm->frame.i]
		= alloc_strndup(vm, (char *)program->data + program->pc + 1, len);
	vm->frame.argv[vm->frame.i]
		= expand_argument(vm, vm->frame.argv[vm->frame.i]);
	vm->frame.i++;
	program->pc += len;
}
