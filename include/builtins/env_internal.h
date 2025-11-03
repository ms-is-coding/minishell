/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:14:13 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/03 13:32:49 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERNAL_H
# define ENV_INTERNAL_H

# include <stddef.h>

bool	is_valid_assignment(const char *str);
int		is_existing_var(char **envp, const char *assignment);
void	print_env(char **envp);
size_t	get_env_size(char **argv, char **envp, char flags);

#endif