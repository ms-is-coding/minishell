/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:01:36 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/16 18:21:47 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <sys/types.h>

typedef struct s_shell	t_shell;

void		prompt_exit_codes(t_shell *sh, char *prompt, ssize_t *len);
void		prompt_pwd(t_shell *sh, char *prompt, ssize_t *len);
const char	*generate_prompt(t_shell *sh);

#endif
