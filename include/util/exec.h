/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 03:03:54 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 14:19:59 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// On error, this function silently returns NULL
// its max output is 1024 bytes
char		*exec_with_output(char **argv);

int			secure_open(const char *file, int oflag);

#endif // EXEC_H
