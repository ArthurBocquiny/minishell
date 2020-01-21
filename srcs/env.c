/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbocqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:56:34 by arbocqui          #+#    #+#             */
/*   Updated: 2020/01/20 14:30:29 by arbocqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		check_var_exist(char **env, char *var_name)
{
	int		i;
	int		j;
	int		diff;

	i = -1;
	j = 0;
	diff = 0;
	while (env[++i])
	{
		while (env[i][j] != '=')
		{
			if (env[i][j] != var_name[j])
				diff++;
			j++;
		}
		if (diff == 0)
			return (i);
		j = 0;
		diff = 0;
	}
	return (-1);
}

void	create_new_var(char ***env, char **av)
{
	char	**env_cpy;
	int		i;
	char	*var;

	i = 0;
	env_cpy = cpy_env(*env, 1);
	var = NULL;
	var = ft_strjoin(av[1], "=");
	var = ft_strjoin(var, av[2]);
	while (env_cpy[i])
		i++;
	env_cpy[i - 1] = ft_strdup(var);
	free(var);
	env_cpy[i] = 0;
	ft_free_tab(*env);
	*env = env_cpy;
}

void	change_var(char ***env, char **av)
{
	int		i;
	char	*tmp;
	char	**env_cpy;

	i = check_var_exist(*env, av[1]);
	tmp = ft_strjoin(av[1], "=");
	tmp = ft_strjoin(tmp, av[2]);
	env_cpy = cpy_env(*env, 1);
	env_cpy[i] = ft_strdup(tmp);
	free(tmp);
	ft_free_tab(*env);
	*env = env_cpy;
}

void	set_env(char ***env, char **av)
{
	if (check_var_exist(*env, av[1]) == -1)
		create_new_var(env, av);
	else
		change_var(env, av);
}

void	unset_env(char ***env, char **av)
{
	char	**tab;
	int		i;
	char	**env_cpy;
	int		j;
	char	**split;

	split = NULL;
	tab = NULL;
	env_cpy = cpy_env(*env, 0);
	i = len_tab(env_cpy);
	if (!(tab = (char**)malloc(sizeof(char*) * (i))))
		return ;
	i = 0;
	j = 0;
	while (env_cpy[i])
	{
		split = ft_strsplit(env_cpy[i], '=');
		if (ft_strcmp(split[0], av[1]) != 0)
			tab[j++] = ft_strdup(env_cpy[i]);
		i++;
	}
	tab[j] = 0;
	ft_free_tab(*env);
	*env = tab;
}
