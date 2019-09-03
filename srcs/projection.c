/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiskakov <tradeshells@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:10:15 by iiskakov          #+#    #+#             */
/*   Updated: 2019/06/30 18:14:20 by iiskakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		projection_isometric(t_point **head, t_scene *v)
{
	int		i;
	t_point	*dot;

	i = 0;
	while (head[i])
	{
		dot = head[i];
		while (dot->next)
		{
			if (dot->is_head == 0)
			{
				if ((v->change_alt == 1 || v->change_alt == 3) && dot->z != 5)
				{
					dot->z = dot->z + v->offset_z;
				}
				dot->h = ((v->zerox - v->offset_x) + (v->dist
				* ((dot->x - dot->y) * 0.86602529158)));
				dot->w = ((v->zeroy - v->offset_y) + (v->dist * ((-1 * dot->z)
				+ (dot->x + dot->y) * 0.50000019433)));
			}
			dot = dot->next;
		}
		i++;
	}
	return (0);
}

int		projection_plane(t_point **head, t_scene *v)
{
	int		i;
	t_point	*dot;

	i = 0;
	while (head[i])
	{
		dot = head[i];
		while (dot->next)
		{
			if (dot->is_head == 0)
			{
				dot->h = ((v->zerox - v->offset_x) + (v->dist * dot->x));
				dot->w = ((v->zeroy - v->offset_y) + (v->dist * dot->y));
			}
			dot = dot->next;
		}
		i++;
	}
	return (0);
}

void	projection_types(t_scene *v)
{
	if (v->projection_type == 3)
		projection_isometric(v->first, v);
	if (v->projection_type == 2)
		projection_plane(v->first, v);
	else
		projection_isometric(v->first, v);
}

void	projection_change_type(int key, t_scene *v)
{
	if (key == 34)
		v->projection_type = 3;
	if (key == 35)
		v->projection_type = 2;
	scene_render(v);
}
