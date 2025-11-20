/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:48:30 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/20 01:55:16 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_INTERNAL_H
# define TYPE_INTERNAL_H

# define FLAG_A		1
# define FLAG_P		2
# define FLAG_PP	4
# define FLAG_T		8
# define FLAG_ERR	16

# define TYPE_BUILTIN	1
# define TYPE_EXEC		2
# define TYPE_UNKNOWN	4

void	type_info(const char *name, const char *path, char type, char flags);

#endif