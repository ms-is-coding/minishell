/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:53:31 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/16 18:40:38 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "core/string.h"
#include "builtins/builtins.h"

static const char	*g_bad_words[] = {
	"shit",
	"damn",
	"fuck",
	"cunt",
	NULL
};

/**
 * @brief Checks if any of the provided arguments contain bad words.
 *
 * @param argv Array of command-line arguments
 * @return true if bad words are found, false otherwise.
 */
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

/**
 * @brief Checks if the user is excessively asking for help.
 *
 * @param argv Array of command-line arguments
 * @return true if help is requested three times or more, false otherwise.
 */
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

/**
 * @brief Sanitizes the help command arguments.
 *
 * @param argv Array of command-line arguments
 * @return 0 if arguments are clean, non-zero error code otherwise.
 */
int	sanitize_help(char **argv)
{
	if (find_bad_words(argv))
		return (builtin_error(ctx("help", NULL), ERR_HELP_DIRTY, 69));
	if (is_begging_for_help(argv))
		return (builtin_error(ctx("help", NULL), ERR_HELP_EXCESS, 2));
	return (0);
}
