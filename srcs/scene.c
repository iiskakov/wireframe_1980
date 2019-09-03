/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiskakov <iiskakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 11:44:30 by iiskakov          #+#    #+#             */
/*   Updated: 2019/07/01 01:33:04 by iiskakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scene_reset(t_scene *fdf)
{
	fdf->dist = 16;
	fdf->color = 0xE0C3FC;
	fdf->width = 1024;
	fdf->height = 1024;
	fdf->offset_x = 100;
	fdf->offset_y = 100;
	fdf->offset_z = 0.2;
	fdf->zerox = (fdf->width / 2);
	fdf->zeroy = (fdf->height / 2);
	fdf->projection_type = 3;
	fdf->type_prog = 1;
}

t_scene	*scene_init(void)
{
	t_scene		*fdf;

	fdf = (t_scene *)malloc(sizeof(t_scene));
	scene_reset(fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "FdF");
	graphic_pixel_put(fdf, 0, 0);
	return (fdf);
}

void	scene_render(t_scene *v)
{
	mlx_clear_window(v->mlx, v->win);
	projection_types(v);
	graphic_draw_lines(v->first, v);
}

int		scene_close(t_scene *v)
{
	unsigned int	i;

	i = 0;
	free(v);
	exit(0);
}
