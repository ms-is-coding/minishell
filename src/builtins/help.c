/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:13:39 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/01/16 16:46:47 by mattcarniel      ###   ########.fr       */
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
	"\tCopyright (C) 2025 ms-is-coding and SkarEye\n"
	"\tLicense GPLv3: GNU GPL v.3 <https://gnu.org/licenses/gpl-3.0.html>\n"
	"\tThis program comes with ABSOLUTELY NO WARRANTY.\n"
	"\tThis is free software, and you are welcome to redistribute it.",
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
	"\tChange the shell working directory.\n"
	"\n"
	"\tChange the current directory to DIR. The default DIR is the value of\n"
	"\tthe HOME shell variable. If DIR is '-', it is converted to $OLDPWD.\n"
	"\n"
	"\tIf DIR begins with a slash (/), DIR is considered an absolute path.\n"
	"\tOtherwise, it's considered relative to the current working directory.\n"
	"\n"
	"\tThe environment variables $PWD and $OLDPWD are updated if the\n"
	"\tdirectory is changed.\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 if the directory is changed; non-zero otherwise.",
	NULL};

static const char	*g_help_echo[] = {
	"echo",
	"Write arguments to standard output.",
	"echo [-neE] [arg ...]",
	"\tWrite arguments to standard output.\n"
	"\n"
	"\tDisplay the ARGs separated by a single space character and followed\n"
	"\tby a newline, on the standard output.\n"
	"\n"
	"\tOptions:\n"
	"\t  -n\tdo not append a newline\n"
	"\t  -e\tenable interpretation of the following backslash escapes\n"
	"\t  -E\texplicitly suppress interpretation of backslash escapes\n"
	"\n"
	"\tAn argument of '--' disables further option processing.\n"
	"\n"
	"\t`echo' interprets the following backslash-escaped characters:\n"
	"\t  \\a\talert (bell)\n"
	"\t  \\b\tbackspace\n"
	"\t  \\c\tsurpress further output\n"
	"\t  \\e\tescape character\n"
	"\t  \\E\tescape character\n"
	"\t  \\f\tform feed\n"
	"\t  \\n\tnew line\n"
	"\t  \\r\tcarriage return\n"
	"\t  \\t\thorizontal tab\n"
	"\t  \\v\tvertical tab\n"
	"\t  \\\\\tbackslash\n"
	"\t  \\0nnn\tThe character whose ASCII code is NNN (octal). NNN can be\n"
	"\t  \t0 to 3 octal digits.\n"
	"\t  \\xHH\tThe eight-bit character whose value is HH (hexadecimal). HH\n"
	"\t  \tcan be one or two hex digits.\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 unless a write error occurs.",
	NULL};

static const char	*g_help_env[] = {
	"env",
	"Print environment or run a command in a modified environment.",
	"env [cmd [arg ...]]",
	"\tPrint environment or run a command in a modified environment.\n"
	"\n"
	"\tPrint the environment variables to standard output.\n"
	"\tIf CMD is specified, it is executed with ARGs as its arguments.\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 if all variables are printed or the CMD is executed\n"
	"\tsuccessfully; non-zero otherwise.",
	NULL};

static const char	*g_help_exec[] = {
	"exec",
	"Replace the shell with the given command.",
	"exec [cmd [arg ...]]",
	"\tReplace the shell with the given command.\n"
	"\n"
	"\tExecute CMD, replacing this shell with the specified progam.\n"
	"\tARGs become the arguments to CMD.\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 if CMD is executed successfully; non-zero otherwise.",
	NULL};

static const char	*g_help_exit[] = {
	"exit",
	"Exit the shell.",
	"exit [n]",
	"\tExit the shell.\n"
	"\n"
	"\tExit the shell with a status of N. If N is omitted, the exit status\n"
	"\tis that of the last command executed.\n",
	NULL};

static const char	*g_help_export[] = {
	"export",
	"Set export attribute for shell variables.",
	"export [-n] [name[=value] ...]",
	"\tSet export attribute for shell variables.\n"
	"\n"
	"\tMark each NAME for automatic export to the environment of\n"
	"\tsubsequently executed commands. If VALUE is supplied, assign VALUE\n"
	"\tbefore exporting.\n"
	"\tIf no NAMEs are given, display the list of all exported variables.\n"
	"\n"
	"\tOptions:\n"
	"\t  -n\tremove the export property from each NAME\n"
	"\n"
	"\tAn argument of '--' disables further option processing.\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 unless an invalid option is given or NAME is invalid.",
	NULL};

static const char	*g_help_false[] = {
	"false",
	"Do nothing, unsuccessfully.",
	"false",
	"\tDo nothing, unsuccessfully.\n"
	"\n"
	"\tExit Status:\n"
	"\tAlways fails.",
	NULL};

static const char	*g_help_pwd[] = {
	"pwd",
	"Print the name of the current working directory.",
	"pwd",
	"\tPrint the name of the current working directory.\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 unless the current directory cannot be read.",
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

static const char	*g_help_true[] = {
	"true",
	"Do nothing, successfully.",
	"true",
	"\tDo nothing, successfully."
	"\n"
	"\tExit Status:\n"
	"\tAlways succeeds.",
	NULL};

static const char	*g_help_type[] = {
	"type",
	"Display information about command type.",
	"type [-aptP] [name ...]",
	"\tFor each NAME, indicate how it would be interpreted if used as a\n"
	"\tcommand name.\n"
	"\n"
	"\tOptions:\n"
	"\t  -a\tdisplay all locations containing an executable named NAME;\n"
	"\t  \tincludes builtins if the `-p' flag is not also used\n"
	"\t  -P\tforce a PATH search for each NAME, even if it is a shell\n"
	"\t  \tbuiltin, and returns the name of the disk file that would be\n"
	"\t  \texecuted\n"
	"\t  -p\treturns either the name of the disk file that would be\n"
	"\t  \texecuted, or nothing if `type -t NAME' would not return `file'\n"
	"\t  -t\toutput a single word which is one of `builtin' or `file' if\n"
	"\t  \tNAME is a shell builtin, disk file or not found respectively\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 if all NAMEs are found; fails if any are not found.",
	NULL};

static const char	*g_help_help[] = {
	"help",
	"Display information about builtin commands.",
	"help [-dms] [pattern ...]",
	"\tDisplay information about builtin commands.\n"
	"\n"
	"\tDisplay brief summaries of builtin commands. If PATTERN is\n"
	"\tspecified, gives detailed help on all commands matching PATTERN,\n"
	"\totherwise the list of help topics is printed.\n"
	"\n"
	"\tOptions:\n"
	"\t  -d\tdisplay short usage information for each topic\n"
	"\t  -m\tdisplay usage in pseudo-manpage format\n"
	"\t  -s\tdisplay only a short usage synopsis for each topic\n"
	"\n"
	"\tExit Status:\n"
	"\tReturns 0 unless PATTERN is not found or an invalid option is given.",
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
{"exec", g_help_exec},
{"exit", g_help_exit},
{"export", g_help_export},
{"false", g_help_false},
{"pwd", g_help_pwd},
{"readonly", g_help_readonly},
{"true", g_help_true},
{"type", g_help_type},
{"help", g_help_help},
{NULL, NULL}
};

/**
 * @brief Parses the command-line options and gets the corresponding flags.
 *
 * @param opt The command-line option string
 * @param flags Pointer to the flags variable to be updated
 * @return true if valid flags were found, false otherwise
 */
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

/**
 * @brief Sets the flags based on the command-line arguments.
 *
 * @param argv Pointer to the array of command-line arguments
 * @return The combined flags.
 */
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

/**
 * @brief Prints the list of available commands with brief descriptions.
 */
static void	print_cmd_list(void)
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
}

/**
 * @brief Prints help information for a specific command based on flags.
 *
 * @param topic The help topic array for the command
 * @param flags The flags indicating the format of help to print
 * @return true if help was printed, false otherwise.
 */
static bool	print_cmd_help(const char **topic, char flags)
{
	if (!topic)
		return (false);
	if (flags & FLAG_D)
		ft_printf("%s - %s\n", topic[0], topic[1]);
	else if (flags & FLAG_M)
	{
		ft_printf("NAME\n\t%s - %s\n\nSYNOPSIS\n\t%s\n\n"
			"DESCRIPTION\n%s\n\nIMPLEMENTATION\n%s\n",
			topic[0], topic[1], topic[2], topic[3], g_license_text[2]);
	}
	else if (flags & FLAG_S)
		ft_printf("%s: %s\n", topic[0], topic[2]);
	else
		ft_printf("%s: %s\n\n%s\n", topic[0], topic[2], topic[3]);
	return (true);
}

/**
 * @brief Displays help information for builtin commands.
 *
 * @param sh Pointer to the shell structure (unused)
 * @param argc Argument count (unused)
 * @param argv Array of command-line arguments
 * @param envp Environment pointer (unused)
 * @return 0 if all arguments are valid, error code otherwise.
 */
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
		return (print_cmd_list(), 0);
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
