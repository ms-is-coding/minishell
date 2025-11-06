/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:32:24 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/03 17:03:50 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_INTERNAL_H
# define CD_INTERNAL_H

void	collapse_slashes(const char **src, char **dst, char **path);
void	skip_current_dir(const char **src);
void	rollback_dir(const char *src, char **dst, char *path);
void	handle_parent_dir(const char **src, char **dst, char *path);
void	finalize_path(char *path, char **dst, bool is_abs);

#endif