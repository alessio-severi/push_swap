/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_general.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:10:38 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/13 21:10:40 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_GENERAL_H
# define PUSHSWAP_GENERAL_H

# include "complex_additions.h"
# include "medium_additions.h"
# include "simple_additions.h"
# include "peephole_optimizer_additions.h"

/* benchmark mode (group 1) */
# define BENCH_OFF	0
# define BENCH_ON	1

/* sort mode (group 2) */
# define COMPLEX_STRATEGY	0
# define SIMPLE_STRATEGY	1
# define MEDIUM_STRATEGY	2
# define ADAPTIVE_STRATEGY	3

# define TOTAL_STRATEGY		4

/* flag group */
# define BENCH_GROUP_FLAG			0
# define STRATEGY_GROUP_FLAG		1

# define TOTAL_GROUP_FLAGS			2

typedef struct s_ps_general
{
	int		strategy;
	int		bench;
	double	disorder;
}	t_ps_general;

/* pushswap_parse.c */
t_ps_general	check_flag(t_ps *ps, int *n, int *i, char **av);
long			ft_atol_checked(const char *str);

/* pushswap_print.c */
void			pushswap_print(t_ps *ps, t_ps_general psg);

/* pushswap_print_bench.c */
void			bench_op_print(t_ps *ps, int i, int j);
void			bench_strategy_print(t_ps *ps, t_ps_general psg);
void			bench_disorder_print(t_ps *ps, t_ps_general psg);

/* pushswap_print_utils.c */
size_t			ft_strlen(const char *s);
void			ft_putnbr_fd_ctrl(t_ps *ps, int n, int fd);

#endif
