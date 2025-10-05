/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:04:49 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/03 08:19:25 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/vm_internal.h"
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

void	vm_arg(t_vm *vm, t_program *program)
{
	size_t	len;

	len = program->data[++program->pc];
	((char **)vm->frame.argv)[vm->frame.i++]
		= alloc_strndup(vm, (char *)program->data + program->pc + 1, len);
	program->pc += len;
}
