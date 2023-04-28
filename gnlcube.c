/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnlcube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:44:59 by mmariani          #+#    #+#             */
/*   Updated: 2023/04/28 14:45:59 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	ft_gnlstrlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}
int	toomanylines(char *s1, char *s2)
{
	if (!s2)
	{
		free (s1);
		return (0);
	}
	return (1);
}

char	*ft_gnlstrjoin(char *s1, char *s2)
{
	char	*temp;
	int		j;
	int		i;
	int		size;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	size = ft_gnlstrlen(s1) + ft_gnlstrlen(s2);
	if (!toomanylines(s1, s2))
		return (NULL);
	temp = malloc(sizeof(char) * (size + 1));
	if (temp == NULL)
		return (NULL);
	j = -1;
	while (s1[++j])
		temp[j] = s1[j];
	i = 0;
	while (s2[i])
		temp[j++] = s2[i++];
	temp[size] = '\0';
	free (s1);
	return (temp);
}

