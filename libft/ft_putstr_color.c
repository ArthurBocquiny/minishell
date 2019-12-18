/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbocqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:11:59 by arbocqui          #+#    #+#             */
/*   Updated: 2018/12/05 19:05:17 by arbocqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkcolor(char *color)
{
	if (color == RED || color == GREEN || color == YELLOW || color == BLUE ||
		color == CYAN || color == MAGENTA)
		return (1);
	return (0);
}

void		ft_putstr_color(const char *s, char *color, int fd)
{
	if (ft_checkcolor(color))
	{
		ft_putstr_fd(color, fd);
		ft_putstr_fd(s, fd);
		ft_putstr_fd(RESET, fd);
	}
}
