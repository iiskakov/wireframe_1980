/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiskakov <iiskakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 08:49:02 by iiskakov          #+#    #+#             */
/*   Updated: 2019/07/01 01:07:43 by iiskakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_scene *v;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf [target_file.fdf]\n", 31);
		return (1);
	}
	if (!(v = scene_init()))
	{
		write(2, "Usage: ./fdf [target_file.fdf]\n", 31);
		return (1);
	}
	v->fd = open((argv[1]), O_RDONLY);
	if (v->fd < 0)
	{
		write(2, "Error while reading the file.\n", 30);
		return (1);
	}
	v->first = parse_array_to_lists(parse_file_to_arrays(v->fd));
	parse_link_bottom_point(v->first);
	projection_types(v);
	graphic_draw_lines(v->first, v);
	key_listener(v);
	mlx_loop(v->mlx);
	return (0);
}
