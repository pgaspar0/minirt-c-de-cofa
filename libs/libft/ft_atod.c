/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgaspar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:14:20 by pgaspar           #+#    #+#             */
/*   Updated: 2025/03/04 11:14:25 by pgaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static double	ft_power(double base, int exp)
{
	double	result;

	result = 1.0;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	while (exp < 0)
	{
		result /= base;
		exp++;
	}
	return (result);
}

double	ft_atod(char *str, int sign, int i, int exp)
{
	double	result;
	double	decimal_part;

	result = 0.0;
	decimal_part = 0.0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			decimal_part = (decimal_part * 10) + (str[i++] - '0');
			exp--;
		}
	}
	return (sign * (result + decimal_part * ft_power(10, exp)));
}
