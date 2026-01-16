/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:46:09 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:00:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"

static uint64_t	splitmix64(uint64_t *state)
{
	uint64_t	x;

	*state += 0x9E3779B97f4A7C15;
	x = *state;
	x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9;
	x = (x ^ (x >> 27)) * 0x94D049BB133111EB;
	return (x ^ (x >> 31));
}

void	ft_rng_init(t_rng256 *rng, uint64_t seed)
{
	uint64_t	tmp;

	rng->seed = seed;
	tmp = splitmix64(&seed);
	rng->s[0] = (uint32_t)tmp;
	rng->s[1] = (uint32_t)(tmp >> 32);
	tmp = splitmix64(&seed);
	rng->s[2] = (uint32_t)tmp;
	rng->s[3] = (uint32_t)(tmp >> 32);
}
