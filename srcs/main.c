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

char	**parse_line(char *line, char **env)
{
	char 	**new_arg;
	int		i;

	i = -1;
	new_arg = ft_strsplit(line, ' ');
	while (new_arg[++i])
	{
		if (new_arg[i][0] == '~')
		{
			ft_strdel(&new_arg[i]);
			new_arg[i] = ft_strdup(find_home(env));
		}
	}
	return (new_arg);
}

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
		av = parse_line(line, env);
		if (av[0])
		{
			right_path = get_right_path(all_path, av[0]);
			if (display_builtin(av, &env) == 1)
			{
			}
			else if (display_command(av, right_path, env) == 0)
			{
				ft_putstr(av[0]);
				ft_putstr(": command not found\n");
				exit(0);
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
