/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansi.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:00:35 by macarnie          #+#    #+#             */
/*   Updated: 2025/10/07 18:40:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSI_H
# define ANSI_H

# define ANSI_RESET			"\033[0m"
# define ANSI_BOLD			"\033[1m"
# define ANSI_ITALIC		"\033[3m"
# define ANSI_UNDERLINE		"\033[4m"
# define ANSI_BLINK			"\033[5m"
# define ANSI_REVERSE		"\033[7m"
# define ANSI_HIDDEN		"\033[8m"
# define ANSI_STRIKETHROUGH	"\033[9m"

# define ANSI_BLACK			"\033[30m"
# define ANSI_RED			"\033[31m"
# define ANSI_GREEN			"\033[32m"
# define ANSI_YELLOW		"\033[33m"
# define ANSI_BLUE			"\033[34m"
# define ANSI_MAGENTA		"\033[35m"
# define ANSI_CYAN			"\033[36m"
# define ANSI_WHITE			"\033[37m"

# define ANSI_BBLACK		"\033[90m"
# define ANSI_BRED			"\033[91m"
# define ANSI_BGREEN		"\033[92m"
# define ANSI_BYELLOW		"\033[93m"
# define ANSI_BBLUE			"\033[94m"
# define ANSI_BMAGENTA		"\033[95m"
# define ANSI_BCYAN			"\033[96m"
# define ANSI_BWHITE		"\033[97m"

# define ANSI_BG_BLACK		"\033[40m"
# define ANSI_BG_RED		"\033[41m"
# define ANSI_BG_GREEN		"\033[42m"
# define ANSI_BG_YELLOW		"\033[43m"
# define ANSI_BG_BLUE		"\033[44m"
# define ANSI_BG_MAGENTA	"\033[45m"
# define ANSI_BG_CYAN		"\033[46m"
# define ANSI_BG_WHITE		"\033[47m"

# define ANSI_BBG_BLACK		"\033[100m"
# define ANSI_BBG_RED		"\033[101m"
# define ANSI_BBG_GREEN		"\033[102m"
# define ANSI_BBG_YELLOW	"\033[103m"
# define ANSI_BBG_BLUE		"\033[104m"
# define ANSI_BBG_MAGENTA	"\033[105m"
# define ANSI_BBG_CYAN		"\033[106m"
# define ANSI_BBG_WHITE		"\033[107m"

#endif
