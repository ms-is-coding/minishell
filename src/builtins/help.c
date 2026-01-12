/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:13:39 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/04 17:02:53 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "builtins/builtins.h"
#include "builtins/help_internal.h"
#include "core/string.h"
#include "core/stdio.h"

#define FLAG_D		1
#define FLAG_M		2
#define FLAG_S		4
#define FLAG_ERR	8

static const char	*g_license_text[] = {
	"TraSH - The Trash Shell",
	"0.0.0-beta",
	"    Copyright (C) 2025 ms-is-coding and SkarEye\n"
	"    License GPLv3: GNU GPL v.3 <https://gnu.org/licenses/gpl-3.0.html>\n"
	"    This program comes with ABSOLUTELY NO WARRANTY.\n"
	"    This is free software, and you are welcome to redistribute it.",
	NULL};

static const char	g_cmd_info[] = {
	"These shell commands are internal to TraSH.\n"
	"For more information for a given command, type 'help [CMD]'.\n"
	"For more information on help, type 'help help'.\n"
	"If you type 'help help help', TraSH will refuse to help you.\n"
	"\n"
	"Please, be polite to the shell."
};

static const char	*g_help_cd[] = {
	"cd",
	"Change the shell working directory.",
	"cd [dir]",
	"    Change the shell working directory.\n"
	"\n"
	"    Change the current directory to DIR. The default DIR is the value of\n"
	"    the HOME shell variable. If DIR is '-', it is converted to $OLDPWD.\n"
	"\n"
	"    If DIR begins with a slash (/), DIR is considered an absolute path.\n"
	"    Otherwise, it's considered relative to the current working directory.\n"
	"\n"
	"    The environment variables $PWD and $OLDPWD are updated if the\n"
	"    directory is changed.\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 if the directory is changed; non-zero otherwise.",
	NULL};

static const char	*g_help_echo[] = {
	"echo",
	"Write arguments to standard output.",
	"echo [-neE] [arg ...]",
	"    Write arguments to standard output.\n"
	"\n"
	"    Display the ARGs separated by a single space character and followed\n"
	"    by a newline, on the standard output.\n"
	"\n"
	"    Options:\n"
	"      -n\tdo not append a newline\n"
	"      -e\tenable interpretation of the following backslash escapes\n"
	"      -E\texplicitly suppress interpretation of backslash escapes\n"
	"\n"
	"    An argument of '--' disables further option processing.\n"
	"\n"
	"    `echo' interprets the following backslash-escaped characters:\n"
	"    \\a\talert (bell)\n"
	"    \\b\tbackspace\n"
	"    \\c\tsurpress further output\n"
	"    \\e\tescape character\n"
	"    \\E\tescape character\n"
	"    \\f\tform feed\n"
	"    \\n\tnew line\n"
	"    \\r\tcarriage return\n"
	"    \\t\thorizontal tab\n"
	"    \\v\tvertical tab\n"
	"    \\\\\tbackslash\n"
	"    \\0nnn\tThe character whose ASCII code is NNN (octal). NNN can be\n"
	"    0 to 3 octal digits.\n"
	"    \\xHH\tThe eight-bit character whose value is HH (hexadecimal). HH\n"
	"    can be one or two hex digits.\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 unless a write error occurs.",
	NULL};

static const char	*g_help_env[] = {
	"env",
	"Print environment or run a command in a modified environment.",
	"env [cmd [arg ...]]",
	"    Print environment or run a command in a modified environment.\n"
	"\n"
	"    Print the environment variables to standard output.\n"
	"    If CMD is specified, it is executed with ARGs as its arguments.\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 if all variables are printed or the CMD is executed\n"
	"    successfully; non-zero otherwise.",
	NULL};

static const char	*g_exec_help[] = {
	"exec",
	"Replace the shell with the given command.",
	"exec [cmd [arg ...]]",
	"    Replace the shell with the given command.\n"
	"\n"
	"    Execute CMD, replacing this shell with the specified progam.\n"
	"    ARGs become the arguments to CMD.\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 if CMD is executed successfully; non-zero otherwise.",
	NULL};

static const char	*g_exit_help[] = {
	"exit",
	"Exit the shell.",
	"exit [n]",
	"    Exit the shell.\n"
	"\n"
	"    Exit the shell with a status of N. If N is omitted, the exit status\n"
	"    is that of the last command executed.\n",
	NULL};

static const char	*g_export_help[] = {
	"export",
	"Set export attribute for shell variables.",
	"export [-n] [name[=value] ...]",
	"    Set export attribute for shell variables.\n"
	"\n"
	"    Mark each NAME for automatic export to the environment of\n"
	"    subsequently executed commands. If VALUE is supplied, assign VALUE\n"
	"    before exporting.\n"
	"    If no NAMEs are given, display the list of all exported variables.\n"
	"\n"
	"    Options:\n"
	"      -n\tremove the export property from each NAME\n"
	"\n"
	"    An argument of '--' disables further option processing.\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 unless an invalid option is given or NAME is invalid.",
	NULL};

static const char	*g_help_false[] = {
	"false",
	"Do nothing, unsuccessfully.",
	"false",
	"    Do nothing, unsuccessfully.\n"
	"\n"
	"    Exit Status:\n"
	"    Always fails.",
	NULL};

static const char	*g_help_logout[] = {
	"logout",
	"Exit a login shell.",
	"logout [n]",
	"    Exit a login shell.\n"
	"\n"
	"    Exit a login shell with exit status N. Returns an error if not\n"
	"    executed in a login shell.",
	NULL};

static const char	*g_help_pwd[] = {
	"pwd",
	"Print the name of the current working directory.",
	"pwd",
	"    Print the name of the current working directory.\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 unless the current directory cannot be read.",
	NULL};

static const char	*g_help_readonly[] = {
	"readonly",
	"Mark shell variavles as unchangeable.",
	"readonly [name[=value] ...]",
	"Mark shell variavles as unchangeable.\n"
	"\n"
	"Mark each NAME as read-only; the values of these NAMEs may not be\n"
	"changed by subsequent assignment. If VALUE is supplied, assign VALUE\n"
	"before marking as read-only.\n"
	"\n"
	"Exit Status:\n"
	"returns 0 success unless NAME is invalid.",
	NULL};

static const char	*g_help_return[] = {
	"return",
	"Return from a shell function.",
	"return [n]",
	"    Return from a shell function.\n"
	"\n"
	"   Causes a function of sourced script to exit with the return value\n"
	"   specified by N. If N is omitted, the return status is that of the\n"
	"   last command executed within the function or script.\n"
	"\n"
	"   Exit Status:\n"
	"   Returns N, or failure if the shell is not executing a function or\n"
	"   script.\n",
	NULL};

static const char	*g_help_true[] = {
	"true",
	"Do nothing, successfully.",
	"true",
	"    Do nothing, successfully."
	"\n"
	"    Exit Status:\n"
	"    Always succeeds.",
	NULL};

static const char	*g_help_type[] = {
	"type",
	"Display information about command type.",
	"type [-aptP] [name ...]",
	"    For each NAME, indicate how it would be interpreted if used as a\n"
	"    command name.\n"
	"\n"
	"    Options:\n"
	"      -a\tdisplay all locations containing an executable named NAME;\n"
	"        \tincludes builtins if the `-p' flag is not also used\n"
	"      -P\tforce a PATH search for each NAME, even if it is a shell\n"
	"        \tbuiltin, and returns the name of the disk file that would be\n"
	"        \texecuted\n"
	"      -p\treturns either the name of the disk file that would be\n"
	"        \texecuted, or nothing if `type -t NAME' would not return `file'\n"
	"      -t\toutput a single word which is one of `builtin' or `file' if\n"
	"        \tNAME is a shell builtin or disk file, respectively\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 if all NAMEs are found; fails if any are not found.",
	NULL};

static const char	*g_help_help[] = {
	"help",
	"Display information about builtin commands.",
	"help [-dms] [pattern ...]",
	"    Display information about builtin commands.\n"
	"\n"
	"    Display brief summaries of builtin commands. If PATTERN is\n"
	"    specified, gives detailed help on all commands matching PATTERN,\n"
	"    otherwise the list of help topics is printed.\n"
	"\n"
	"    Options:\n"
	"      -d\tdisplay short usage information for each topic\n"
	"      -m\tdisplay usage in pseudo-manpage format\n"
	"      -s\tdisplay only a short usage synopsis for each topic\n"
	"\n"
	"    Exit Status:\n"
	"    Returns 0 unless PATTERN is not found or an invalid option is given.",
	NULL};

typedef struct s_help
{
	const char	*name;
	const char	**topic;
}	t_help;

static t_help		g_help[] = {
{"cd", g_help_cd},
{"echo", g_help_echo},
{"env", g_help_env},
{"exec", g_exec_help},
{"exit", g_exit_help},
{"export", g_export_help},
{"false", g_help_false},
{"logout", g_help_logout},
{"pwd", g_help_pwd},
{"readonly", g_help_readonly},
{"return", g_help_return},
{"true", g_help_true},
{"type", g_help_type},
{"help", g_help_help},
{NULL, NULL}
};

static bool	get_flags(const char *opt, char *flags)
{
	int		i;

	if (!opt || opt[0] != '-' || ft_strcmp(opt, "-") == 0)
		return (false);
	i = 1;
	while (opt[i])
	{
		if (opt[i] == 'd')
			*flags |= FLAG_D;
		else if (opt[i] == 'm')
			*flags |= FLAG_M;
		else if (opt[i] == 's')
			*flags |= FLAG_S;
		else
		{
			*flags = FLAG_ERR;
			return (false);
		}
		i++;
	}
	return (true);
}

static char	set_flags(int *argc, char ***argv)
{
	char	flags;

	if (*argc < 2)
		return (0);
	flags = 0;
	while (*argc > 1)
	{
		if (ft_strcmp(**argv, "--") == 0)
		{
			*argc -= 1;
			*argv += 1;
			break ;
		}
		if (!get_flags(**argv, &flags))
			break ;
		*argc -= 1;
		*argv += 1;
	}
	return (flags);
}

static int	print_cmd_list(void)
{
	size_t	i;

	ft_printf("%s, version %s\n\n%s\n\n",
		g_license_text[0], g_license_text[1], g_cmd_info);
	i = 0;
	while (g_help[i].name)
	{
		ft_printf("%-8.8s - %s\n",
			g_help[i].name, g_help[i].topic[2]);
		i++;
	}
	return (0);
}

static bool	print_cmd_help(const char **topic, char flags)
{
	if (!topic)
		return (false);
	if (flags & FLAG_D)
		ft_printf("%s - %s\n", topic[0], topic[1]);
	else if (flags & FLAG_M)
	{
		ft_printf("NAME\n    %s - %s\n\nSYNOPSIS\n    %s\n\n"
			"DESCRIPTION\n%s\n\nIMPLEMENTATION\n%s\n",
			topic[0], topic[1], topic[2], topic[3], g_license_text[2]);
	}
	else if (flags & FLAG_S)
		ft_printf("%s: %s\n", topic[0], topic[2]);
	else
		ft_printf("%s: %s\n\n%s\n", topic[0], topic[2], topic[3]);
	return (true);
}

int	builtin_help(
	__attribute__((unused)) t_shell *sh,
	__attribute__((unused)) int argc,
	char **argv,
	__attribute__((unused)) char **envp)
{
	char	flags;
	size_t	i;
	int		status;

	argv++;
	flags = set_flags(&argc, &argv);
	if (flags & FLAG_ERR)
		return (builtin_error(ctx("help", argv[0]), ERR_INVALID_OPT, 1));
	if (!*argv)
		return (print_cmd_list());
	status = sanitize_help(argv);
	if (status)
		return (status);
	while (*argv)
	{
		i = 0;
		while (g_help[i].name && ft_strcmp(*argv, g_help[i].name) != 0)
			i++;
		if (!print_cmd_help(g_help[i].topic, flags))
			status = builtin_error(ctx("help", *argv), ERR_HELP_NOT_FOUND, 1);
		argv++;
	}
	return (status);
}
