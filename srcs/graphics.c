/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiskakov <iiskakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 08:43:04 by iiskakov          #+#    #+#             */
/*   Updated: 2019/07/01 01:32:25 by iiskakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	graphic_put_legend(t_scene *v)
{
	mlx_string_put(v->mlx, v->win, 20, 20, 0xAAAAAA,
		"Fils de fer - iiskakov");
	mlx_string_put(v->mlx, v->win, 20, 60, 0xAAAAAA,
		"Controls:");
	mlx_string_put(v->mlx, v->win, 20, 80, 0xAAAAAA,
		"Move - arrows");
	mlx_string_put(v->mlx, v->win, 20, 100, 0xAAAAAA,
		"Altitude up\\down - \"h\\l\" ");
	mlx_string_put(v->mlx, v->win, 20, 120, 0xAAAAAA,
		"Zoom in\\out - \"j\\k\" ");
	mlx_string_put(v->mlx, v->win, 20, 140, 0xAAAAAA,
		"Axonometric projection - \"i\" ");
	mlx_string_put(v->mlx, v->win, 20, 160, 0xAAAAAA,
		"Plan projection - \"p\" ");
	mlx_string_put(v->mlx, v->win, 20, 180, 0xAAAAAA,
		"Recenter - \"r\" ");
	mlx_string_put(v->mlx, v->win, 20, 200, 0xAAAAAA,
		"Quit - \"esc\" ");
}

void	graphic_pixel_put(t_scene *p, int x0, int y0)
{
	static	t_scene *v;

	if (p)
		v = p;
	if (!p)
	{
		mlx_pixel_put(v->mlx, v->win, x0, y0, v->pixel_color);
	}
}

void	graphic_bresenham(int x0, int y0, int x1, int y1)
{
	int		d[4];
	int		err[2];

	d[1] = abs(y1 - y0);
	d[0] = abs(x1 - x0);
	d[3] = y0 < y1 ? 1 : -1;
	err[0] = (d[0] > d[1] ? d[0] : -d[1]) / 2;
	d[2] = x0 < x1 ? 1 : -1;
	while (1)
	{
		graphic_pixel_put(NULL, x0, y0);
		if (x0 == x1 && y0 == y1)
			break ;
		err[1] = err[0];
		if (err[1] > -d[0])
		{
			err[0] -= d[1];
			x0 += d[2];
		}
		if (err[1] < d[1])
		{
			err[0] += d[0];
			y0 += d[3];
		}
	}
}

int		graphic_get_color(int z)
{
	if (z < -10)
		return (0x7100A5);
	else if (z < -5)
		return (0x392AA2);
	else if (z < -3)
		return (0x6B6CB3);
	else if (z < 0)
		return (0xCCFFFF);
	else if (z < 2)
		return (0x42B517);
	else if (z < 4)
		return (0x87BE30);
	else if (z < 6)
		return (0xCCCC4A);
	else if (z < 8)
		return (0xE7DE72);
	else if (z < 10)
		return (0x87633F);
	else if (z < 20)
		return (0x582424);
	else
		return (0xE5BFE4);
}

void	graphic_draw_lines(t_point **head, t_scene *v)
{
	int		i;
	t_point	*ptr;

	i = 0;
	graphic_put_legend(v);
	while (head[i])
	{
		ptr = head[i];
		while (ptr->next && head[i])
		{
			if (ptr->is_head == 0 && ptr->next->is_head == 0)
			{
				v->pixel_color = graphic_get_color(ptr->z);
				if (ptr->next && ptr->next->h && ptr->next->w)
					graphic_bresenham(ptr->h, ptr->w, ptr->next->h,
						ptr->next->w);
				if (ptr->down && ptr->down->h && ptr->down->w)
					graphic_bresenham(ptr->h, ptr->w, ptr->down->h,
						ptr->down->w);
			}
			ptr = ptr->next;
		}
		i++;
	}
}
