/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:33:24 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/11 16:39:07 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander/expander.h"
#include <stdint.h>

// compute length
// allocate string
// expand string
void	expander_expand(
	t_expander *exp,
	t_exec_frame *frame,
	const char *arg,
	size_t len)
{
	exp->arg = arg;
	exp->len = len;
	exp->frame = frame;
	frame->argv[frame->i++] = ft_strndup(arg, len);
}
