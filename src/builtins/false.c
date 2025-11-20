/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   false.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 22:16:02 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/18 18:02:02 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

int	builtin_false(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv,
	__attribute__((unused)) char **envp)
{
	return (1);
}
