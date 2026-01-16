/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:45:24 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:22:10 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/stdio.h"
#include <unistd.h>

#define BUFFER_SIZE 1024

static inline void	noop(void)
{
	return ;
}

int	ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	char	small_buf[BUFFER_SIZE];
	char	*buf;
	va_list	ap_copy;
	int		len;

	va_copy(ap_copy, ap);
	len = ft_vsnprintf(NULL, 0, fmt, ap_copy);
	va_end(ap_copy);
	if (len < 0)
		return (len);
	buf = small_buf;
	if (len >= BUFFER_SIZE)
	{
		buf = malloc((size_t)len + 1);
		if (!buf)
			return (-1);
	}
	len = ft_vsnprintf(buf, (size_t)len + 1, fmt, ap);
	if (write(fd, buf, (size_t)len))
		noop();
	if (buf != small_buf)
		free(buf);
	return (len);
}
