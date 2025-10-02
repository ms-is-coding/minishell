/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 08:34:21 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/05 09:00:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft_printf.h"

static char	*find_exec(char *arg)
{
	const char	*paths[] = {
		"./", "/bin", "/usr/bin", "/usr/local/bin",
		"/sbin", "/usr/sbin", "/usr/local/sbin", NULL};
	char		*path;
	int			i;
	size_t		len;

	i = -1;
	if (!arg)
		return (NULL);
	while (paths[++i])
	{
		len = ft_strlen(paths[i]) + ft_strlen(arg) + 2;
		path = ft_malloc(len);
		if (!path)
			return (NULL);
		ft_snprintf(path, len, "%s/%s", paths[i], arg);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

static char **env;

static void	push_env(size_t idx, t_value val)
{
	env[idx] = val.value.str;
}

// todo:
// - decrement shlvl
int	builtin_exec(t_shell *sh, int argc, char **argv)
{
	char	*cmd;

	if (argc == 1)
		return (0);
	cmd = find_exec(argv[1]);
	if (!cmd)
		ft_printf("exec: %s: command not found\n", argv[1]);
	env = malloc(sizeof(char *) * (sh->env.public.length + 1));
	if (!env)
		return (0);
	ft_vector_foreach(&sh->env.public, push_env);
	execve(cmd, argv + 1, env);
	exit(0);
	return (0);
}
