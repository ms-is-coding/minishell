/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:58:38 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/04 16:55:14 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/git.h"
#include "core/string.h"
#include "core/stdlib.h"
#include "util/exec.h"
#include <stdio.h>
#include <string.h>

t_git_status	git_status_read(void)
{
	t_git_status	st;
	char			*line;
	char			*output;

	ft_memset(&st, 0, sizeof(st));
	output = exec_with_output((char *[]){
			(char *)(intptr_t)"/usr/bin/git",
			(char *)(intptr_t)"status",
			(char *)(intptr_t)"--porcelain=v2",
			(char *)(intptr_t)"-b",
			NULL});
	line = ft_strtok(output, "\n");
	while (line)
	{
		if (strncmp(line, "# branch.head ", 14) == 0)
			strncpy(st.branch, line + 14, sizeof(st.branch) - 1);
		else if (strncmp(line, "# branch.upstream ", 18) == 0)
			strncpy(st.upstream, line + 18, sizeof(st.upstream) - 1);
		else if (strncmp(line, "# branch.ab ", 12) == 0)
			sscanf(line + 12, "+%d -%d", &st.ahead, &st.behind);
		else if (line[0] == '?' && line[1] == ' ')
			st.untracked++;
		else if (line[0] == 'u')
			st.conflicts++;
		else if (line[0] == '1' || line[0] == '2')
		{
			if (line[2] != '.')
				st.staged++;
			if (line[3] != '.')
				st.dirty++;
		}
		line = ft_strtok(NULL, "\n");
	}
	ft_free((void *)(intptr_t)output);
	return (st);
}
