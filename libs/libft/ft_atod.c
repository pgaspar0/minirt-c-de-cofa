/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:14:20 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/27 19:48:19 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

double	ft_atod(char *str, t_fdi flags, int *error)
{
	double	result;
	double	decimal_part;

	result = 0.0;
	decimal_part = 0.0;
	if (!str)
		return (*error = 0, 0.0);
	while (str[flags.i] == ' ' || (str[flags.i] >= 9 && str[flags.i] <= 13))
		flags.i++;
	if (str[flags.i] == '-' || str[flags.i] == '+')
		if (str[flags.i++] == '-')
			flags.sign = -1;
	while (str[flags.i] >= '0' && str[flags.i] <= '9')
		result = (result * 10) + (str[flags.i++] - '0');
	if (str[flags.i] == '.')
	{
		flags.i++;
		while (str[flags.i] >= '0' && str[flags.i] <= '9')
		{
			decimal_part = (decimal_part * 10) + (str[flags.i++] - '0');
			flags.exp--;
		}
	}
	return (flags.sign * (result + decimal_part * ft_power(10, flags.exp)));
}
