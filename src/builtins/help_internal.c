/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:53:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2025/11/18 17:22:54 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include "builtins/builtins.h"

static const char	*g_bad_words[] = {
	"shit",
	"damn",
	"fuck",
	"cunt",
	NULL
};

static bool	find_bad_words(char **argv)
{
	size_t	i;

	while (*argv)
	{
		i = 0;
		while (g_bad_words[i])
		{
			if (ft_strstr(*argv, g_bad_words[i]) != NULL)
				return (true);
			i++;
		}
		argv++;
	}
	return (false);
}

static bool	is_begging_for_help(char **argv)
{
	size_t	help_count;

	help_count = 0;
	while (*argv)
	{
		if (ft_strncmp("help", *argv, 5) == 0)
			help_count++;
		argv++;
	}
	return (help_count >= 2);
}

int	sanitize_help(char **argv)
{
	if (find_bad_words(argv))
		return (builtin_error(ctx("help", NULL), ERR_HELP_DIRTY, 69));
	if (is_begging_for_help(argv))
		return (builtin_error(ctx("help", NULL), ERR_HELP_EXCESS, 2));
	return (0);
}
