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


void	display_env(char **env, char **av)
{
	(void)env;
	(void)av;
/*	int		i;
	char	**env_cpy;

	env_cpy = NULL;
	i = 0;
	// parse env avec option -i
	// puis creer une copie de l'env contenant uniquement les elements indiques
	// et execve dans cet env.
	else
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
