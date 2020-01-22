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

void	clear_env(char ***env_cpy)
{
	int		i;

	i = 0;
	while (*env_cpy[i])
	{
		free(*env_cpy[i]);
		i++;
	}	
	free(*env_cpy);
}

char	**add_var_env(char *av, char **env_cpy)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = NULL;
	if (!(new_env = (char**)malloc(sizeof(char*) * (len_tab(env_cpy) + 2))))
		return (NULL);
	while (env_cpy[i])
	{
		new_env[i] = ft_strdup(env_cpy[i]);
		free(env_cpy[i]);
		i++;
	}
	free(env_cpy);
	new_env[i++] = ft_strdup(av);
	new_env[i] = 0;
	return (new_env);
}

void	exec_env(char **av, int index, char **env_cpy)
{
	int		i;

	i = 0;
	while (env_cpy[i])
		i++;
	(void)index;
	(void)av;
}

void	display_env(char **env, char **av)
{
	int		i;
	char	**env_cpy;

	i = 1;
	env_cpy = cpy_env(env, 0);
	// parse env avec option -i
	// puis creer une copie de l'env contenant uniquement les elements indiques
	// et execve dans cet env.
	while (av[i])
	{
		if (av[i][0] == '-')
			clear_env(&env_cpy);
		else if (ft_strchr(av[i], '=') != 0)
			env_cpy = add_var_env(av[i], env_cpy);
		else
			exec_env(av, i, env_cpy);
		i++;
	}
}

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
