/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_print_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:09:49 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:09:51 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_general.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_print_number(t_ps *ps, long number, int fd)
{
	char	c;

	if (number > 9)
		ft_print_number(ps, number / 10, fd);
	c = (char)(number % 10 + '0');
	if (write(fd, &c, 1) == -1)
		exit_error_ps(ps);
}

void	ft_putnbr_fd_ctrl(t_ps *ps, int n, int fd)
{
	long	number;

	number = n;
	if (number < 0)
	{
		if (write(fd, "-", 1) == -1)
			exit_error_ps(ps);
		number = -number;
	}
	ft_print_number(ps, number, fd);
}
