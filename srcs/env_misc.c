/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbocqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:05:57 by arbocqui          #+#    #+#             */
/*   Updated: 2020/01/21 16:06:18 by arbocqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	exec_env(char **av, char **env, char *right_path)
{
	pid_t	pid;
	char	*binary_path;

	binary_path = ft_strjoin(right_path, "/");
	binary_path = ft_strjoin(binary_path, av[0]);
	pid = fork();
	if (pid < 0)
		exit(0);
	if (pid > 0)
		wait(0);
	if (pid == 0)
	{
		if (execve(binary_path, av, NULL) != -1)
			execve(binary_path, av, env);
		else if (execve(binary_path, av, NULL) == -1)
			execve(av[0], av, env);
	}
}

int		count_var(char **av)
{
	int		i;
	int		nb;

	i = 1;
	nb = 0;
	while (av[++i])
	{
		if (ft_strchr(av[i], '=') == 0)
			return (nb);
		nb++;
	}
	return (nb);
}

char	**new_env(char **av)
{
	char	**n_env;
	int		i;
	int		j;

	n_env = NULL;
	i = 1;
	j = 0;
	if (!(n_env = (char**)malloc(sizeof(char*) * (count_var(av) + 1))))
		return (NULL);
	while (av[++i])
	{
		if (ft_strchr(av[i], '=') == 0)
		{
			n_env[j] = 0;
			return (n_env);
		}
		n_env[j] = ft_strdup(av[i]);
		j++;
	}
	n_env[j] = 0;
	return (n_env);
}

int		find_exec(char **av)
{
	int		i;

	i = 1;
	while (av[++i])
	{
		if (ft_strchr(av[i], '=') == 0)
			return (i);
	}
	return (i);
}

char	**cut_exec(char **av)
{
	int		i;
	char	**new;
	int		j;

	j = 0;
	i = 1;
	new = NULL;
	new = (char**)malloc(sizeof(char*) * (2 + 1));
	while (av[++i])
	{
		if (ft_strchr(av[i], '=') == 0)
		{
			new[j] = av[i];
			new[j + 1] = av[i + 1];
			return (new);
		}
	}
	return (NULL);
}

void	display_env(char **env, char **av)
{
	int		i;
	int		j;
	char	**env_cpy;
	char	*right_path;
	char	**all_path;
	char	**exec;

	right_path = NULL;
	env_cpy = NULL;
	j = 0;
	all_path = get_all_paths(find_path(env));
	// parse env avec option -i
	// puis creer une copie de l'env contenant uniquement les elements indiques
	// et execve dans cet env.
	if (ft_strcmp(av[1], "-i") == 0 || ft_strcmp(av[1], "-") == 0)
		env_cpy = new_env(av);
	else
		env_cpy = cpy_env(av, 0);
	i = find_exec(av);
	right_path = get_right_path(all_path, av[i]);
	exec = cut_exec(av);
	display_command(exec, right_path, env_cpy);
/*	else
	{
		while (env[++i])
		{
			ft_putstr(env[i]);
			ft_putchar('\n');
		}
	}
*/}

char	**cpy_env(char **env, int nb)
{
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	while (env[i])
		i++;
	if (!(tab = (char**)malloc(sizeof(char*) * (i + 1 + nb))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		tab[i] = ft_strdup(env[i]);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
