/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouto <lcouto@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:39:45 by lcouto            #+#    #+#             */
/*   Updated: 2021/09/11 19:25:38 by lcouto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_count_spaces(const char *str, int i)
{
	while ((str[i] == '\t') || (str[i] == '\v') || (str[i] == '\f')
		|| (str[i] == '\r') || (str[i] == '\n') || (str[i] == ' '))
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						is_negative;
	unsigned long long int	result;

	i = 0;
	is_negative = 1;
	result = 0;
	i = ft_count_spaces(str, i);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_negative = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= 48) && (str[i] <= 57))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (result > LONG_MAX && is_negative == 1)
		return (-1);
	else if (result > LONG_MAX && is_negative == -1)
		return (0);
	else
		return (is_negative * (int)result);
}
