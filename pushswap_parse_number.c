/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_parse_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 00:37:40 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/14 00:37:43 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_general.h"

long	ft_atol_checked(const char *str)
{
	int		sgn;
	long	number;

	sgn = 1;
	number = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sgn *= -1;
	if (!(*str >= '0' && *str <= '9'))
		return ((long)INT_MAX + 1L);
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + *str++ - '0';
		if (sgn > 0 && number > INT_MAX)
			return ((long)INT_MAX + 1L);
		else if (sgn < 0 && number > (long)INT_MAX + 1L)
			return ((long)INT_MAX + 1L);
	}
	if (*str != '\0')
		return ((long)INT_MAX + 1L);
	return (number * sgn);
}
