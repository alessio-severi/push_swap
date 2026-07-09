/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_gnl1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvigonz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:12:47 by elvigonz          #+#    #+#             */
/*   Updated: 2026/07/06 17:20:54 by elvigonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	str_len(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	find_newline(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_line(char *residue, int pos)
{
	char	*line;
	int		i;

	line = malloc(pos + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (i <= pos)
	{
		line[i] = residue[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_leftover(char *residue, int pos)
{
	char	*rest;
	int		lenght;
	int		i;

	lenght = str_len(residue) - pos - 1;
	rest = malloc(lenght + 1);
	if (!rest)
		return (NULL);
	i = 0;
	while (i < lenght)
	{
		rest[i] = residue[pos + 1 + i];
		i++;
	}
	rest[i] = '\0';
	free(residue);
	return (rest);
}
