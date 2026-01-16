/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rng.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:45:37 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:00:39 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdlib.h"
#include "magic.h"

__attribute__((__always_inline__))
static inline uint64_t	rol64(uint64_t x, int k)
{
	return ((x << k) | (x >> (64 - k)));
}

uint64_t	ft_rng_u64(t_rng256 *rng)
{
	uint64_t	*s;
	uint64_t	x;
	uint64_t	t;

	s = rng->s;
	x = rol64(s[0] + s[3], 23) + s[0];
	t = rng->s[1] << 17;
	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	s[2] ^= t;
	s[3] = rol64(s[3], 45);
	return (x);
}

uint32_t	ft_rng_u32(t_rng256 *rng)
{
	return ((uint32_t)(ft_rng_u64(rng) >> 32));
}

double	ft_rng_f64(t_rng256 *rng)
{
	return ((1.0 / DBL_MAX_INTEGER) * (double)(ft_rng_u64(rng) >> 11));
}
