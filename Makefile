# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/09 11:54:36 by elvigonz          #+#    #+#              #
#    Updated: 2026/07/09 11:54:42 by elvigonz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
CHECKER		= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		=	main.c \
				pushswap_utils.c \
				pushswap_free.c \
				pushswap_parse_flag.c \
				pushswap_parse_number.c \
				pushswap_rank.c \
				pushswap_ops_part1.c \
				pushswap_ops_part2.c \
				pushswap_ops_part3.c \
				pushswap_print.c \
				pushswap_print_bench.c \
				pushswap_print_utils.c \
				complex.c \
				complex_sort_core.c \
				complex_encoded_rank.c \
				complex_recode_dispatcher.c \
				complex_recode.c \
				complex_decode.c \
				complex_utils.c \
				complex_lift_bottom.c \
				complex_check_block_sorted.c \
				medium.c \
				medium_parking_cond.c \
				medium_recover_parked_chain.c \
				medium_push_to_b.c \
				medium_rebuild_a.c \
				simple.c \
				simple_push_to_b.c \
				simple_search_best_b.c \
				simple_push_to_a.c \
				small_bfs.c \
				small_bfs_utils.c \
				small_bfs_state.c \
				small_bfs_apply_no_rotate.c \
				small_bfs_apply_rotate.c \
				peephole_optimizer_core.c \
				peephole_optimizer_sizes.c \
				peephole_optimizer_try_dispatcher.c \
				peephole_optimizer_try_basic.c \
				peephole_optimizer_try_safe.c \
				peephole_optimizer_try_safe4.c \
				peephole_optimizer_try_cond.c \
				peephole_optimizer_try_cond5.c \
				peephole_optimizer_try_cond6.c

CHECKER_SRCS =	checker_stack.c \
				checker_parse.c \
				checker_ops1.c \
				checker_ops2.c \
				checker_exec.c \
				checker_gnl1.c \
				checker_gnl2.c \
				checker_main.c

OBJS		= $(SRCS:.c=.o)
CHECKER_OBJS = $(CHECKER_SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME) $(CHECKER)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(CHECKER): $(CHECKER_OBJS)
	$(CC) $(CFLAGS) $(CHECKER_OBJS) -o $(CHECKER)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(CHECKER_OBJS): %.o: %.c checker.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(CHECKER_OBJS)

fclean: clean
	rm -f $(NAME) $(CHECKER)

re: fclean all

.PHONY: all bonus clean fclean re
