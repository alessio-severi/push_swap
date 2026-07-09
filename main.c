/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:05:37 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:05:39 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_general.h"

static t_ps_general	pushswap_init(t_ps *ps, int *n, int *i, char **av)
{
	t_ps_general	psg;

	init_null(ps);
	psg = check_flag(ps, n, i, av);
	psg.disorder = 0;
	if (!stack_init(&ps->a, *n))
		exit_error_ps(ps);
	if (!stack_init(&ps->b, *n))
		exit_error_ps(ps);
	if (!oplist_init(&ps->oplist, *n * 20))
		exit_error_ps(ps);
	return (psg);
}

static double	compute_disorder(t_stack a)
{
	int		i;
	int		j;
	double	mistakes;
	double	total_pairs;

	if (a.size < 2)
		return (0);
	mistakes = 0;
	total_pairs = 0;
	i = 0;
	while (i < a.size)
	{
		j = i + 1;
		while (j < a.size)
		{
			total_pairs++;
			if (a.data[i] > a.data[j])
				mistakes++;
			j++;
		}
		i++;
	}
	return (mistakes / total_pairs);
}

static void	apply_strategy(t_ps_general *psg, t_ps *ps, int n)
{
	if (psg->bench == BENCH_ON || psg->strategy == ADAPTIVE_STRATEGY
		|| (psg->strategy == COMPLEX_STRATEGY && n <= 100))
		psg->disorder = compute_disorder(ps->a);
	if ((psg->strategy == ADAPTIVE_STRATEGY && psg->disorder >= 0.5)
		|| psg->strategy == COMPLEX_STRATEGY)
		complex_sort(ps, n);
	else if ((psg->strategy == ADAPTIVE_STRATEGY && psg->disorder < 0.2)
		|| psg->strategy == SIMPLE_STRATEGY)
	{
		if (!simple_sort(ps, n))
			exit_error_ps(ps);
	}
	else
		medium_sort(ps, n);
}

int	main(int ac, char **av)
{
	t_ps			ps;
	t_ps_general	psg;
	long			val;
	int				i;
	int				n;

	if (ac < 2)
		return (0);
	n = ac - 1;
	psg = pushswap_init(&ps, &n, &i, av);
	while (i < ac)
	{
		val = ft_atol_checked(av[i]);
		if (val > INT_MAX)
			exit_error_ps(&ps);
		ps.a.data[n + i++ - ac] = (int)val;
	}
	if (check_sorted(&ps, n))
		return (pushswap_print(&ps, psg), free_ps(&ps), 0);
	if (!add_index(&ps, n))
		exit_error_ps(&ps);
	apply_strategy(&psg, &ps, n);
	if (!oplist_peephole_optimizer(&ps.oplist, n))
		exit_error_ps(&ps);
	return (pushswap_print(&ps, psg), free_ps(&ps), 0);
}
