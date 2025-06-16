/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:28:26 by jorcarva          #+#    #+#             */
/*   Updated: 2025/06/16 16:48:31 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	scene_elem(t_minirt *scene)
{
	if (scene->al == 1 && scene->l == 1 && scene->c == 1)
		return (1);
	return (0);
}
