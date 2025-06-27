/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:14:20 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/26 12:46:36 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static void	has_alpha(const char *nptr, int *flag)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(nptr);
	while (i < j)
	{
		if(!(nptr[i] >= 48 && nptr[i] <= 57) && nptr[i] != '.' && nptr[i] != ',' && nptr[i] != '-' && nptr[i] != '+')
		{
			*flag = 1e9;
			return ;
		}
		i++;
	}
	return ;
}

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
	has_alpha(str, &exp);
	if (exp == 1e9)
		return (-2147483647);
	return (sign * (result + decimal_part * ft_power(10, exp)));
}
