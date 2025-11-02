/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   license.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 22:03:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/30 22:14:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "help/help.h"
#include "libft_printf.h"
#include "common.h"

const char	g_license_text[] = 
	"Copyright (C) 2025 ms-is-coding and SkarEye\n"
	"License GPLv3: GNU GPL version 3 <https://gnu.org/licenses/gpl-3.0.html>\n"
	"This program comes with ABSOLUTELY NO WARRANTY.\n"
	"This is free software, and you are welcome to redistribute it.";

void	help_version(void)
{
	ft_printf("Trash, version " TRASH_VERSION "\n\n%s\n", g_license_text);
}
