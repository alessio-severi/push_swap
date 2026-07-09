/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:27:55 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 14:48:37 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	str_is_int(const char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	if (!(*s >= '0' && *s <= '9'))
		return (0);
	while (*s >= '0' && *s <= '9')
		s++;
	return (*s == '\0');
}

long	ft_atol_checked(const char *s)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	if (!(*s >= '0' && *s <= '9'))
		return ((long)INT_MAX + 1L);
	while (*s >= '0' && *s <= '9')
	{
		num = num * 10 + (*s++ - '0');
		if (sign == 1 && num > INT_MAX)
			return ((long)INT_MAX + 1L);
		if (sign == -1 && num > (long)INT_MAX + 1L)
			return ((long)INT_MAX + 1L);
	}
	if (*s != '\0')
		return ((long)INT_MAX + 1L);
	return (num * sign);
}

static int	has_duplicates(int *data, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (data[i] == data[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	build_stack(t_checker *ck, int ac, char **av)
{
	int		n;
	int		i;
	long	val;

	n = ac - 1;
	ck->a.data = NULL;
	ck->b.data = NULL;
	if (!stack_init(&ck->a, n) || !stack_init(&ck->b, n))
		return (0);
	i = 0;
	while (i < n)
	{
		if (!str_is_int(av[i + 1]))
			return (0);
		val = ft_atol_checked(av[i + 1]);
		if (val > INT_MAX || val < (long)- INT_MAX - 1L)
			return (0);
		ck->a.data[i] = (int)val;
		ck->a.size++;
		i++;
	}
	if (has_duplicates(ck->a.data, n))
		return (0);
	return (1);
}
