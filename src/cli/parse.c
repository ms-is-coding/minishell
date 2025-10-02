/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:55:55 by smamalig          #+#    #+#             */
/*   Updated: 2025/10/02 15:37:57 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cli/cli_internal.h"

static t_result	parse_positional(t_cli *cli, const char *arg)
{
	(void)cli;
	(void)arg;
	//return (ft_vector_push(&cli->positional,
	//	ft_gen_val(TYPE_OTHER, (t_any){.str = (char *)arg})));
	return (RESULT_OK);
}

static t_result	parse_short(t_cli *cli, int argc, char **argv, int *i)
{
	const char		short_name = argv[*i][1];
	t_cli_option	*opt;

	opt = cli_find_short(cli, short_name);
	if (!opt || opt->short_name == '\0')
	{
		ft_printf("%s: -%c: invalid option\n", cli->name, short_name);
		return (RESULT_ERROR);
	}
	opt->is_set = 1;
	if (opt->has_value)
	{
		if (argv[*i][2] == '=')
			opt->value = argv[*i] + 3;
		else if (argv[*i][2] == '\0')
		{
			if (*i + 1 >= argc)
			{
				ft_printf("Fatal: Missing value for option\n");
				return (RESULT_ERROR);
			}
			opt->value = argv[++(*i)];
		}
		else
			opt->value = argv[*i] + 2;
	}
	else if (argv[*i][2] != '\0')
	{
		ft_printf("Fatal: Argument does not accept a value\n");
		return (RESULT_ERROR);
	}
	return (RESULT_OK);
}

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
	{
		ft_printf("%s: --%s: invalid option\n", argv[0], long_name);
		return (RESULT_ERROR);
	}
	opt->is_set = 1;
	if (opt->has_value)
	{
		if (value)
			opt->value = value;
		else
		{
			if (*i + 1 >= argc)
			{
				ft_printf("Fatal: Missing value for option\n");
				return (RESULT_ERROR);
			}
			opt->value = argv[++(*i)];
		}
	}
	else if (value)
	{
		ft_printf("Warning: Option does not accept a value\n");
		return (RESULT_ERROR);
	}
	return (RESULT_OK);
}

t_result	cli_parse(t_cli *cli, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-'
			&& parse_positional(cli, argv[i]) != RESULT_OK)
			return (RESULT_ERROR);
		else if (argv[i][1] != '-'
			&& parse_short(cli, argc, argv, &i) != RESULT_OK)
			return (RESULT_ERROR);
		else if (parse_long(cli, argc, argv, &i) != RESULT_OK)
			return (RESULT_ERROR);
	}
	return (RESULT_OK);
}
