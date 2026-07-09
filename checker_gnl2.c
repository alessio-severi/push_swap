/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_gnl2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:22:11 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 18:33:45 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static char	*join_leftover(char *residue, char *piece)
{
	char	*new;
	int		len_a;
	int		len_b;
	int		i;

	len_a = str_len(residue);
	len_b = str_len(piece);
	new = malloc(len_a + len_b + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len_a)
	{
		new[i] = residue[i];
		i++;
	}
	while (i < len_a + len_b)
	{
		new[i] = piece[i - len_a];
		i++;
	}
	new[i] = '\0';
	free(residue);
	return (new);
}

static char	*read_until_newline(int fd, char *residue)
{
	char	piece[BUFFER_SIZE + 1];
	int		letti;

	letti = 1;
	while (find_newline(residue) == -1 && letti > 0)
	{
		letti = read(fd, piece, BUFFER_SIZE);
		if (letti < 0)
		{
			free(residue);
			return (NULL);
		}
		piece[letti] = '\0';
		residue = join_leftover(residue, piece);
	}
	return (residue);
}

char	*get_next_line(int fd)
{
	static char	*residue;
	char		*line;
	int			pos;

	if (fd < 0)
	{
		free(residue);
		residue = NULL;
		return (NULL);
	}
	residue = read_until_newline(fd, residue);
	if (!residue || residue[0] == '\0')
	{
		free(residue);
		residue = NULL;
		return (NULL);
	}
	pos = find_newline(residue);
	if (pos == -1)
		pos = str_len(residue) - 1;
	line = extract_line(residue, pos);
	residue = extract_leftover(residue, pos);
	return (line);
}
