/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:22:22 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/12 17:02:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "util/time.h"
#include "core/stdlib.h"
#include "core/string.h"
#include "util/exec.h"

#if defined(__is_42sh)

int64_t	time_get(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#else

int64_t	time_get(void)
{
	char	*output;
	char	*temp;
	int64_t	time;
	int64_t	ns;

	output = exec_with_output((char *[]){
			(char *)(intptr_t)"/usr/bin/date",
			(char *)(intptr_t)"+%s %N",
			NULL});
	output && (temp = ft_strchr(output, ' '));
	if (!output || !temp)
		return (0);
	time = ft_atol_safe(output);
	ns = ft_atoi_safe(temp);
	time = time * 1000 + ns / 1000000;
	ft_free(output);
	return (time);
}

#endif
