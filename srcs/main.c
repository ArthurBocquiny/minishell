/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbocqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:22:05 by arbocqui          #+#    #+#             */
/*   Updated: 2020/01/21 16:04:29 by arbocqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	loop(char **env)
{
	char	*line;
	char	**av;
	char	**all_path;
	char	*right_path;

	right_path = NULL;
	av = NULL;
	line = NULL;
	while (1)
	{
		all_path = get_all_paths(find_path(env));
		display_prompt();
		line = read_line();
		av = ft_strsplit(line, ' ');
		if (av[0])
		{
			right_path = get_right_path(all_path, av[0]);
			if (display_builtin(av, &env) == 1)
			{
			}
			else if (1)
				display_command(av, right_path, env);
			else
			{
				ft_putstr(av[0]);
				ft_putstr(": command not found\n");
			}
		}
	}
}


int		main(int ac, char **av, char **env)
{
	char	**env_cpy;

	env_cpy = NULL;
	if (ac < 0 || !av)
		return (0);
	env_cpy = cpy_env(env, 0);
	loop(env_cpy);
	return (0);
}
