/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbocqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:16:34 by arbocqui          #+#    #+#             */
/*   Updated: 2020/02/25 16:47:59 by arbocqui         ###   ########.fr       */
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

void	cd_para(char *path, char ***env)
{
	char	*new_oldpwd;
	char	*new_pwd;

	new_oldpwd = getcwd(NULL, 0);
	new_pwd = NULL;
	if (path == NULL)
	{
		if (chdir(find_home(*env)) == -1)
			ft_error("cd", find_home(*env));
		set_env(env, "OLDPWD", new_oldpwd);
		ft_strdel(&new_oldpwd);
		new_pwd = getcwd(NULL, 0);
		set_env(env, "PWD", new_pwd);
		ft_strdel(&new_pwd);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		if (chdir(find_oldpwd(*env)) == -1)
			ft_error("cd", find_oldpwd(*env));
		set_env(env, "OLDPWD", new_oldpwd);
		ft_strdel(&new_oldpwd);
		new_pwd = getcwd(NULL, 0);
		set_env(env, "PWD", new_pwd);
		ft_strdel(&new_pwd);
	}
	else
	{
		if (chdir(path) == -1)
			ft_error("cd", path);
		set_env(env, "OLDPWD", new_oldpwd);
		ft_strdel(&new_oldpwd);
		new_pwd = getcwd(NULL, 0);
		set_env(env, "PWD", new_pwd);
		ft_strdel(&new_pwd);
	}
}
