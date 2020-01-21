/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbocqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:16:34 by arbocqui          #+#    #+#             */
/*   Updated: 2020/01/20 16:21:04 by arbocqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*read_line(void)
{
	char	*res;

	res = NULL;
	get_next_line(0, &res);
	return (res);
}

void	cd_para(char *path, char **env)
{
	if (path == NULL)
	{
		if (chdir(find_home(env)) == -1)
			ft_error("cd", find_home(env));
	}
	else
	{
		if (chdir(path) == -1)
			ft_error("cd", path);
	}
}
