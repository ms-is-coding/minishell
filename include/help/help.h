/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:05:58 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/20 17:16:31 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELP_H
# define HELP_H

typedef enum e_help_code
{
	HELP_HOME_EXPAND,
	HELP_EXPORT_NOARG,
	HELP_COUNT
}	t_help_code;

void	help_warn(t_help_code);

#endif // HELP_H
