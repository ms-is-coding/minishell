/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:50:32 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/19 22:38:04 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define TRASH_VERSION "0.0.1"

# define MAX_REDIRS 64
# define MAX_ALIASES 64

# define DEFAULT_PATH "/usr/local/sbin:/usr/local/bin:/usr/bin"

# define CLI_OPTION_COUNT 8

# define ERROR_CHARACTERS 10
// would write ERROR_CHARACTERS * 2 + 3, but norm...
# define ERROR_MAX_LENGTH 23

#endif // COMMON_H
