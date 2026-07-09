/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:35:02 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 17:45:19 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	process_line(t_checker *ck, char *line)
{
	int	i;
	int	op;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	line[i] = '\0';
	if (line[0] == '\0')
		return (0);
	op = str_to_opcode(line);
	if (op == -1)
		return (0);
	execute_op(ck, op);
	return (1);
}

static int	read_instructions(t_checker *ck)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL)
	{
		if (!process_line(ck, line))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(0);
	}
	return (1);
}

void	final_check(t_checker *ck)
{
	if (organize_check(ck))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_ck(ck);
}

int	main(int ac, char **av)
{
	t_checker	ck;

	if (ac < 2)
		return (0);
	init_checker (&ck);
	if (!build_stack(&ck, ac, av) || !read_instructions(&ck))
	{
		free_ck(&ck);
		get_next_line(GNL_RESET);
		write(2, "Error\n", 6);
		return (1);
	}
	final_check(&ck);
	get_next_line(GNL_RESET);
	return (0);
}
