/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:19:11 by pgaspar           #+#    #+#             */
/*   Updated: 2025/06/26 12:50:32 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	has_alpha(const char *nptr, int *flag, int f, int s)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	j = ft_strlen(nptr);
// 	while (i < j)
// 	{
// 		if (!(nptr[i] >= 48 && nptr[i] <= 57 && nptr[i] != ','
				// && nptr[i] != '.'))
// 		{
// 			*flag = -1;
// 			return ;
// 		}
// 		i++;
// 	}
// 	*flag = f * s;
// 	return ;
// }

int	ft_atoi(const char *nptr)
{
	int	i;
	int	f;
	int	s;
	// int	flag;

	i = 0;
	f = 0;
	s = 1;
	// flag = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		f = (nptr[i] - '0') + (f * 10);
		i++;
	}
	// has_alpha(nptr, &flag, f, s);
	return (s * f);
}
