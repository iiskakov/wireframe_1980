/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiskakov <tradeshells@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 08:43:29 by iiskakov          #+#    #+#             */
/*   Updated: 2019/06/30 18:13:37 by iiskakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_altitude(int key, t_scene *v)
{
	v->change_alt = 3;
	if (key == 4)
		v->offset_z = 0.6;
	else if (key == 37)
		v->offset_z = -0.6;
	scene_render(v);
	v->change_alt = 0;
}

void	key_move(int key, t_scene *v)
{
	if (key == 125)
		v->offset_y += 70;
	else if (key == 126)
		v->offset_y -= 70;
	else if (key == 124)
		v->offset_x += 70;
	else if (key == 123)
		v->offset_x -= 70;
	scene_render(v);
}

void	key_zoom(int key, t_scene *v)
{
	if (key == 38)
		v->dist *= 2;
	else if (key == 40)
		v->dist *= -2;
	if (v->dist < 1)
		v->dist = 1;
	scene_render(v);
}

int		key_press(int keycode, t_scene *v)
{
	if (keycode == 53)
		scene_close(v);
	if (keycode == 15)
	{
		scene_reset(v);
		scene_render(v);
	}
	if (keycode == 38 || keycode == 40)
		key_zoom(keycode, v);
	if (keycode == 123 || keycode == 124 || keycode == 126 || keycode == 125)
		key_move(keycode, v);
	if (keycode == 4 || keycode == 37)
		key_altitude(keycode, v);
	if (keycode == 34 || keycode == 35)
		projection_change_type(keycode, v);
	return (0);
}

void	key_listener(t_scene *v)
{
	mlx_hook(v->win, 2, 0, key_press, v);
	mlx_hook(v->win, 17, 0, close, v);
}
