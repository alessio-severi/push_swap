/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:15:21 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 18:28:22 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define BUFFER_SIZE 1024
# define GNL_RESET -1

typedef struct s_stack
{
	int	*data;
	int	size;
	int	capacity;
}	t_stack;

typedef struct s_checker
{
	t_stack	a;
	t_stack	b;
}	t_checker;

# define OP_SA  1
# define OP_SB  2
# define OP_SS  3
# define OP_PA  4
# define OP_PB  5
# define OP_RA  6
# define OP_RB  7
# define OP_RR  8
# define OP_RRA 9
# define OP_RRB 10
# define OP_RRR 11

int		stack_init(t_stack *s, int capacity);
void	stack_free(t_stack *s);
void	init_checker(t_checker *ck);
void	free_ck(t_checker *ck);
int		organize_check(t_checker *ck);

int		str_is_int(const char *s);
long	ft_atol_checked(const char *s);
int		build_stack(t_checker *ck, int ac, char **av);

void	rotate(t_stack *s);
void	reverse_rotate(t_stack *s);
void	execute_op(t_checker *ck, int op);

void	execute_op2(t_checker *ck, int op);

int		str_to_opcode(char *s);
int		execute_move(t_checker *ck, char *s);

int		str_len(char *s);
int		find_newline(char *s);
char	*extract_line(char *residuo, int pos);
char	*extract_leftover(char *residuo, int pos);
char	*get_next_line(int fd);

void	final_check(t_checker *ck);

#endif
