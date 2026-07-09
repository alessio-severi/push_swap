/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_parse_flag.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 00:37:40 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/14 00:37:43 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_general.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == s2[i])
		{
			if (!(s1[i]))
				return (0);
			i++;
		}
		else
			return (((unsigned char) s1[i]) - ((unsigned char) s2[i]));
	}
	return (0);
}

static size_t	ft_strsize(const char *s)
{
	size_t	count;

	count = 1;
	while (*s++)
		count++;
	return (count);
}

static int	check_flag_bench(t_ps_general *psg, int *n, int *i, char **av)
{
	if (*n > 0 && !ft_strncmp(av[*i], "--bench", 8))
	{
		(*i)++;
		(*n)--;
		psg->bench = BENCH_ON;
		return (0);
	}
	return (1);
}

static int	check_flag_strategy(t_ps_general *psg, int *n, int *i, char **av)
{
	int				j;
	const char		*strategy[] = {
		"--complex", "--simple", "--medium", "--adaptive"};

	j = -1;
	while (*n > 0 && ++j < TOTAL_STRATEGY)
	{
		if (!ft_strncmp(av[*i], strategy[j], ft_strsize(strategy[j])))
		{
			(*i)++;
			(*n)--;
			psg->strategy = j;
			return (0);
		}
	}
	return (1);
}

t_ps_general	check_flag(t_ps *ps, int *n, int *i, char **av)
{
	t_ps_general	psg;
	int				group_flag[TOTAL_GROUP_FLAGS];
	int				j;

	*i = 1;
	psg.bench = BENCH_OFF;
	group_flag[BENCH_GROUP_FLAG] = 1;
	psg.strategy = ADAPTIVE_STRATEGY;
	group_flag[STRATEGY_GROUP_FLAG] = 1;
	j = -1;
	while (++j < TOTAL_GROUP_FLAGS)
	{
		if (group_flag[BENCH_GROUP_FLAG])
			group_flag[BENCH_GROUP_FLAG] = check_flag_bench(&psg, n, i, av);
		if (group_flag[STRATEGY_GROUP_FLAG])
			group_flag[STRATEGY_GROUP_FLAG] = check_flag_strategy(&psg,
					n, i, av);
	}
	if (*n < 1)
		exit_error_ps(ps);
	return (psg);
}
