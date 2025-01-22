/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:37:42 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/16 19:21:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_doubles(char *base, char c, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (base[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static int	check_base(char *base)
{
	int	i;

	if (base[0] == '\0' || base [1] == '\0')
		return (0);
	i = 0;
	while (base[i] != '\0')
	{
		if (check_doubles(base, base[i], i) == 0)
			return (0);
		if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] == 127)
			return (0);
		i++;
	}
	return (1);
}

static int	get_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	while (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = sign * (-1);
		(*i)++;
	}
	return (sign);
}

static int	find_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	len;
	int	sign;
	int	result;
	int	value;

	i = 0;
	len = 0;
	result = 0;
	if (check_base(base) == 1)
	{
		while (base[len] != '\0')
			len++;
		sign = get_sign(str, &i);
		value = find_in_base(ft_tolower(str[i]), base);
		while (value != -1)
		{
			result = (result * len) + value;
			i++;
			value = find_in_base(str[i], base);
		}
	}
	return (result * sign);
}
