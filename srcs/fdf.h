/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiskakov <iiskakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 18:15:05 by iiskakov          #+#    #+#             */
/*   Updated: 2019/07/05 15:52:49 by iiskakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx/mlx.h"
# include "../libft/get_next_line.h"
# include <math.h>
# include "../libft/libft.h"

typedef struct		s_star
{
	float			x;
	float			y;
	float			z;
	int				h;
	int				w;
	int				color;
	char			*name;
	int				is_head;
	char			*com;
	struct s_star	*next;
}					t_star;

typedef struct		s_point
{
	int				x;
	int				y;
	float			z;
	int				h;
	int				w;
	int				is_head;
	struct s_point	*next;
	struct s_point	*down;
}					t_point;

typedef struct		s_scene
{
	int				fd;
	int				dist;
	int				color;
	int				width;
	int				height;
	int				offset_x;
	int				offset_y;
	float			offset_z;
	void			*mlx;
	void			*win;
	struct s_point	**first;
	struct s_star	**first_star;
	int				zerox;
	int				zeroy;
	int				projection_type;
	int				change_alt;
	int				type_prog;
	int				pixel_color;
}					t_scene;

int					get_next_line(const int fd, char **l);
void				scene_reset(t_scene *fdf);
t_scene				*scene_init(void);
void				scene_render(t_scene *v);
int					scene_close(t_scene *v);
void				key_altitude(int key, t_scene *v);
void				key_move(int key, t_scene *v);
void				key_zoom(int key, t_scene *v);
int					key_press(int keycode, t_scene *v);
void				key_listener(t_scene *v);
void				graphic_pixel_put(t_scene *p, int x0, int y0);
void				graphic_put_legend(t_scene *v);
int					graphic_get_color(int z);
void				graphic_bresenham(int x0, int y0, int x1, int y1);
void				graphic_draw_lines(t_point **head, t_scene *v);
int					projection_isometric(t_point **head, t_scene *v);
int					projection_plane(t_point **head, t_scene *v);
void				projection_types(t_scene *v);
void				projection_change_type(int key, t_scene *v);
char				***parse_file_to_arrays(int fd);
t_point				*parse_create_head(void);
void				parse_list_add_to_last(t_point *head, int j, int i, int k);
void				parse_link_bottom_point(t_point **head);
t_point				**parse_array_to_lists(char ***arr);
void				star_graphic_draw_stars(t_star **head,
	t_scene *v, int color);
void				star_graphic_erase_stars(t_scene *v);
int					star_projection(t_star **head, t_scene *v);
t_star				**star_array_to_lists(char ***arr);
void				star_list_add_to_last(t_star *head, int j, int i, int k,
					int color, char *name);
t_star				*star_create_head(void);
char				***star_file_to_arrays(int fd);
void				star_scene_render(t_scene *v);
int					star_color(char c);

#endif
