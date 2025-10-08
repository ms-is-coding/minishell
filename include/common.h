/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:50:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/08 20:02:13 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define TRASH_VERSION "0.0.1"

# define OPCODE_MASK 0x3f
# define REDIR_APPEND_BIT 0x80
# define REDIR_FD_BIT 0x40

# define MAX_REDIRS 64

# define CLI_OPTION_COUNT 8

# define ERROR_CHARACTERS 10
// would write ERROR_CHARACTERS * 2 + 3, but norm...
# define ERROR_MAX_LENGTH 23

#endif // COMMON_H
