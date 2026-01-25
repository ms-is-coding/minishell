/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:55:55 by smamalig          #+#    #+#             */
/*   Updated: 2026/01/25 13:47:25 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"
#include "core/stdio.h"
#include "core/string.h"

/**
 * @brief Handles parsing errors by printing an error message.
 *
 * @param err The CLI error code
 * @return t_result RESULT_ERROR.
 */
static t_result	parse_error(t_cli_error err)
{
	if (err == CLI_ERR_INVALID_OPT)
		ft_dprintf(STDERR_FILENO, "Fatal: Invalid option\n");
	else if (err == CLI_ERR_MISSING_VALUE)
		ft_dprintf(STDERR_FILENO, "Fatal: Missing value for option\n");
	else if (err == CLI_ERR_NO_ACCEPT)
		ft_dprintf(STDERR_FILENO, "Fatal: Option does not accept a value\n");
	return (RESULT_ERROR);
}

/**
 * @brief Parses a short option from the command-line arguments.
 *
 * @param cli Pointer to the CLI structure
 * @param argc Argument count
 * @param argv Argument vector
 * @param i Pointer to the current index in argv
 * @return t_result RESULT_OK on success, RESULT_ERROR on failure.
 */
static t_result	parse_short(t_cli *cli, int argc, char **argv, int *i)
{
	const char		short_name = argv[*i][1];
	t_cli_option	*opt;

	opt = cli_find_short(cli, short_name);
	if (!opt || opt->short_name == '\0')
		return (parse_error(CLI_ERR_INVALID_OPT));
	opt->is_set = 1;
	if (opt->has_value)
	{
		if (argv[*i][2] == '=')
			opt->value = argv[*i] + 3;
		else if (argv[*i][2] == '\0')
		{
			if (*i + 1 >= argc)
				return (parse_error(CLI_ERR_MISSING_VALUE));
			opt->value = argv[++(*i)];
		}
		else
			opt->value = argv[*i] + 2;
	}
	else if (argv[*i][2] != '\0')
		return (parse_error(CLI_ERR_NO_ACCEPT));
	return (RESULT_OK);
}

/**
 * @brief Parses a long option from the command-line arguments.
 *
 * @param cli Pointer to the CLI structure
 * @param argc Argument count
 * @param argv Argument vector
 * @param i Pointer to the current index in argv
 * @return t_result RESULT_OK on success, RESULT_ERROR on failure.
 */
static t_result	parse_long(t_cli *cli, int argc, char **argv, int *i)
{
	const char		*long_name = argv[*i] + 2;
	char			*value;
	t_cli_option	*opt;

	value = ft_strchr(argv[*i] + 2, '=');
	if (value)
		*value++ = '\0';
	opt = cli_find(cli, long_name);
	if (!opt || !opt->long_name)
		return (parse_error(CLI_ERR_INVALID_OPT));
	opt->is_set = 1;
	if (opt->has_value)
	{
		if (value)
			opt->value = value;
		else
		{
			if (*i + 1 >= argc)
				return (parse_error(CLI_ERR_MISSING_VALUE));
			opt->value = argv[++(*i)];
		}
	}
	else if (value)
		return (parse_error(CLI_ERR_NO_ACCEPT));
	return (RESULT_OK);
}

/**
 * @brief Parses command-line arguments and populates the CLI structure.
 *
 * @param cli Pointer to the CLI structure
 * @param argc Argument count
 * @param argv Argument vector
 * @return t_result RESULT_OK on success, RESULT_ERROR on failure.
 */
t_result	cli_parse(t_cli *cli, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			ft_dprintf(2, "Warning: extra argument \"%s\"\n", argv[i]);
		else if (argv[i][1] != '-')
		{
			if (parse_short(cli, argc, argv, &i) != RESULT_OK)
				return (RESULT_ERROR);
		}
		else if (parse_long(cli, argc, argv, &i) != RESULT_OK)
			return (RESULT_ERROR);
	}
	return (RESULT_OK);
}
