/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:41:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 10:47:00 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAGIC_H
# define MAGIC_H

# include <stdint.h>

# define DBL_MAX_INTEGER 9007199254740992.0

# if UINTPTR_MAX == 0xfffffffful

#  define NBYTES 4
#  define ALIGN_MASK 3

#  define STRLEN_HIMAGIC 0x80808080ul
#  define STRLEN_LOMAGIC 0x01010101ul

#  define MEMSET_MAGIC 0x01010101ul

# elif UINTPTR_MAX == 0xffffffffffffffffull

#  define NBYTES 8
#  define ALIGN_MASK 7

#  define STRLEN_HIMAGIC 0x8080808080808080ull
#  define STRLEN_LOMAGIC 0x0101010101010101ull

#  define MEMSET_MAGIC 0x0101010101010101ull

# else

#  error "Unsupported architecture"

# endif

#endif // MAGIC_H
