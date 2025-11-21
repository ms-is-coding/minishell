/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:09:25 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/19 00:41:09 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GIT_H
# define GIT_H

typedef struct git_status {
	char	branch[128];
	char	upstream[128];
	int		ahead;
	int		behind;

	int		staged;
	int		dirty;
	int		untracked;
	int		conflicts;
}	t_git_status;

t_git_status	git_status_read(void);

#endif // GIT_H
