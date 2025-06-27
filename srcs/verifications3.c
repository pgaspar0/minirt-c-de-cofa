/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:28:26 by jorcarva          #+#    #+#             */
/*   Updated: 2025/06/26 12:45:11 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	scene_elem(t_minirt *scene)
{
	if (scene->al == 1 && scene->l == 1 && scene->c == 1)
		return (1);
	return (0);
}

int	verify_alpha(char *str, t_minirt *rt)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57) && str[i] != '.'
			&& str[i] != ',' && str[i] != '-' && str[i] != '+'
			&& str[i] != ' ' && str[i] != '\t')
		{
			rt->error = 0;
			return (0);
		}
		i++;
	}
	return (1);
}
