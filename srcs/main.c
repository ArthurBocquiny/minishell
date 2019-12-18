/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbocqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:22:05 by arbocqui          #+#    #+#             */
/*   Updated: 2019/11/21 17:09:31 by arbocqui         ###   ########.fr       */
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

void	display_prompt(void)
{
	write(1, "$> ", 2);
}

void	display_line(char *line)
{
	ft_putstr(line);
	ft_putchar('\n');
}

void	display_command(char *line, char **av, char *right_path)
{
	pid_t	pid;
	char	*binary_path;

	binary_path = ft_strjoin(right_path, "/");
	binary_path = ft_strjoin(binary_path, av[0]);
	line = NULL;
	pid = fork();
	if (pid < 0)
		exit(0);
	if (pid > 0)
		wait(0);
	if (pid == 0)
	{
		if (execve(binary_path, av, NULL) != -1)
			execve(binary_path, av, NULL);
		else if (execve(binary_path, av, NULL) == -1)
			execve(av[0], av, NULL);
	}
}

char	**get_all_paths(char *path)
{
	char	**all_path;

	all_path = ft_strsplit(path, ':');
	return (all_path);
}

char	*get_right_path(char **all_path, char *binary)
{
	DIR				*files;
	struct dirent	*read;
	int				i;

	i = 0;
	while (all_path[i])
	{
		if (!(files = opendir(all_path[i])))
			return (NULL);
		while ((read = readdir(files)))
		{
			if (ft_strcmp(read->d_name, binary) == 0)
			{
				closedir(files);
				return (all_path[i]);
			}
		}
		closedir(files);
		i++;
	}
	return (NULL);
}

void	display_echo(char **av)
{
	int		i;

	i = 1;
	if (ft_strcmp(av[1], "-n") == 0)
		i++;
	while (av[i])
	{
		ft_putstr(av[i]);
		if (av[i + 1])
			ft_putchar(' ');
		i++;
	}
}

char	*find_home(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'H' && env[i][1] == 'O' && env[i][2] == 'M'
			&& env[i][3] == 'E' && env[i][4] == '=')
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_path(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

void	ft_error_cd(char *path)
{
	t_stat	file_stat;

	lstat(path, &file_stat);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
	else if (access(path, X_OK) == -1 && S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
	else if (!S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
}

void	ft_error(char *builtin, char *path)
{

	if (ft_strcmp(builtin, "cd") == 0)
		ft_error_cd(path);
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

void	display_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		ft_putstr(env[i]);
		ft_putchar('\n');
	}
}

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

int		len_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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
	display_env(tab);
	ft_free_tab(*env);
	*env = tab;
}

int		display_builtin(char **av, char ***env)
{
	if (ft_strcmp(av[0], "echo") == 0)
	{
		display_echo(av);
		if (ft_strcmp(av[1], "-n") != 0)
			ft_putchar('\n');
		return (1);
	}
	else if (ft_strcmp(av[0], "cd") == 0)
	{
		cd_para(av[1], *env);
		return (1);
	}
	else if (ft_strcmp(av[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(av[0], "setenv") == 0)
	{
		set_env(env, av);
		return (1);
	}
	else if (ft_strcmp(av[0], "unsetenv") == 0)
	{
		unset_env(env, av);
		return (1);
	}
	else if (ft_strcmp(av[0], "env") == 0)
	{
		display_env(*env);
		return (1);
	}
	return (0);
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
		av = ft_strsplit(line, ' ');
		if (av[0])
		{
			right_path = get_right_path(all_path, av[0]);
			if (display_builtin(av, &env) == 1)
			{
			}
			else if (1)
				display_command(line, av, right_path);
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
