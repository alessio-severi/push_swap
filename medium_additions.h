/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_additions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseveri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 06:16:44 by aseveri           #+#    #+#             */
/*   Updated: 2026/06/19 21:39:53 by aseveri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEDIUM_ADDITIONS_H
# define MEDIUM_ADDITIONS_H

# include "pushswap.h"
# include "small_bfs_additions.h"

typedef struct s_rebuild
{
	int	target;
	int	parked_count;
	int	parked_bottom;
	int	has_next_target;
	int	ignore_parking_direction;
}	t_rebuild;

/* medium.c */
void		medium_sort(t_ps *ps, int block_size);
int			ceil_div(int a, int b);

/* medium_rebuild_a.c */
void		rebuild_a_with_parking(t_ps *ps, int n);

/* medium_parking_cond.c */
int			can_park(int value, t_rebuild *r);
int			dir_to_target_is_forward_b(t_ps *ps, int target);

/* medium_recover_parked_chain.c */
void		recover_parked_chain(t_ps *ps, t_rebuild *r);

/* medium_push_to_b.c */
void		push_bucket_to_b(t_ps *ps, int n, int bucket, int bucket_count);

#endif
