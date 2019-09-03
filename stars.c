	#include "fdf.h"



void key_altitude(int key, t_scene *v)
{
	v->change_alt = 3;
	if (key == 4)
		v->offset_z = 0.02;
	else if (key == 37)
		v->offset_z = -0.02;
	star_scene_render(v);
	v->change_alt = 0;
}
void	key_move(int key, t_scene *v)
{
	if (key == 125)
		v->offset_y += 50;
	else if (key == 126)
		v->offset_y -= 50;
	else if (key == 124)
		v->offset_x += 50;
	else if (key == 123)
		v->offset_x -= 50;
	star_scene_render(v);
}

void	key_zoom(int key, t_scene *v)
{
	if (key == 38)
		v->dist += 1;
	else if (key == 40)
		v->dist -= 2;
	if (v->dist < 1)
		v->dist = 1;
	star_scene_render(v);
}

int key_press(int keycode, t_scene *v)
{

	if (keycode == 53)
		scene_close(v);
	if (keycode == 15)
	{
		scene_reset(v);
		star_scene_render(v);
	}
	if (keycode == 38 || keycode == 40)
		key_zoom(keycode, v);
	if (keycode == 123 || keycode == 124 || keycode == 126 || keycode == 125)
		key_move(keycode, v);
	if (keycode == 4 || keycode == 37)
		key_altitude(keycode, v);
	return (0);
}


void key_listener(t_scene *v)
{
	mlx_hook(v->win, 2, 0, key_press, v);
	mlx_hook(v->win, 17, 0, close, v);
}



int		scene_close(t_scene *v)
{
	free(v);
	exit(0);
}

void scene_reset(t_scene *fdf)
{
	fdf->dist = 10;
	fdf->color 	= 0xF8F7FF;
	fdf->width = 2048;
	fdf->height = 1024;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->offset_z = 0.2;
	fdf->zerox = (fdf->width / 2);
	fdf->zeroy = (fdf->height / 2);
	fdf->projection_type = 3;
	fdf->type_prog = 2;
}

t_scene *scene_init(void)
{
	t_scene *fdf;

	fdf = (t_scene *)malloc(sizeof(t_scene));
	scene_reset(fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "FdF - iiskakov");
	graphic_pixel_put(fdf, 0, 0);
	return (fdf);
}

char ***star_file_to_arrays(int fd)
{
	int i;
	char ***arr; 
	char *line;

	i = 0;
	arr = (char ***)malloc(sizeof(char **) * 200000);
	while (get_next_line(fd , &line))
	{
		arr[i] = ft_strsplit(line, ' ');
		i++;
	}
	ft_strdel(&line);
	arr[i] = NULL;
	return (arr);
}

t_star *star_create_head(void)
{
	t_star *newNode;

	newNode = (t_star *)malloc(sizeof(t_star));
	newNode->x = 0;
    newNode->y = 0;
    newNode->z = 0;
    newNode->h = 0;
    newNode->w = 0;
    newNode->is_head = 1;
	newNode->next = NULL;
	return (newNode);
}

void star_list_add_to_last(t_star *head, int j, int i, int k, int color, char *name)
{
	t_star *newNode;
	t_star *current = head;

    if (!(newNode = (t_star *)malloc(sizeof(t_star))))
        exit(-1);
    newNode->x = j + 1;
    newNode->y = i * 10;
    newNode->z = k + 1;
    newNode->h = 0;
    newNode->w = 0;
    if (name)
    	newNode->name = ft_strdup(name);
    else
    	newNode->name = NULL;
    newNode->color = color;
    newNode->is_head = 0;	
    newNode->next = NULL; 
    if (head->next == NULL)
        head->next = newNode;
    else
    {
        current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }
}

void star_scene_render(t_scene *v)
{
	star_graphic_erase_stars(v);
	star_projection(v->first_star, v);
	star_graphic_draw_stars(v->first_star, v, v->color);
}

t_star **star_array_to_lists(char ***arr)
{
	t_star **head;
	int i;

	i = 0;
	while (arr[i])
		i++;
	head = (t_star **)malloc(sizeof(t_star *) * i);
	i = 0;
	head[0] = star_create_head();
		while (arr[i])
		{
			star_list_add_to_last(head[0], atoi(arr[i][1]), atoi(arr[i][2]), atoi(arr[i][3]), star_color(arr[i][0][0]), arr[i][4]);
			i++;
			free(arr[i]);
		}
	head[1] = NULL;
	free(arr);
	return (head);
}

int star_projection(t_star **head, t_scene *v)
{
	int i;
	t_star *dot;

	i = 0;
	while (head[i])
	{	
		dot = head[i];
		while (dot->next)
		{
			if (dot->is_head == 0)
			{
				dot->h = ((v->zerox - v->offset_x) + (v->dist * ((dot->x - dot->y) )));
				dot->w = ((v->zeroy - v->offset_y) + (v->dist * ((-dot->z) + (dot->x + dot->y))));
			}
			dot = dot->next;		
		}
		i++;
	}
	return (0);
}

int star_color(char c)
{
	if (c == 'O')
		return (0x7070FF);
	else if (c == 'B')
		return (0x50A0FF);
	else if (c == 'A')
		return (0xC0CFFF);
	else if (c == 'F')
		return (0xCFFFFF);
	else if (c == 'G')
		return (0xEFFFDF);
	else if (c == 'K')
		return (0xFFFF7F);
	else if (c == 'M')
		return (0xFF7F7F);
	else if (c == 'C')
		return (0x50A0FF);
	else
		return (0xFFFFFF);
}


void star_graphic_erase_stars(t_scene *v)
{
	mlx_clear_window(v->mlx, v->win);
}

void star_graphic_draw_stars(t_star **head, t_scene *v, int color)
{
	t_star *ptr;

	ptr = head[0];
		while (ptr->next && head[0])
		{
				if (ptr->is_head == 0 && ptr->next && ptr->next->h && ptr->next->w)
				{
					if (ptr->h <= v->width - 100 && ptr->h >= 100 && ptr->w <= v->height - 100 && ptr->w >= 100)
					{
						if (ptr->name)
						{
							graphic_bresenham(ptr->h + 19, ptr->w + 19, ptr->h + 5, ptr->w + 5);
							mlx_string_put(v->mlx, v->win, ptr->h + 20, ptr->w + 20, 0xAAAAAA, ptr->name);
						}
						mlx_pixel_put(v->mlx, v->win,  ptr->h,  ptr->w, ptr->color);
					}
				}
			ptr = ptr->next;
		}	
}


int main(int argc, char **argv)
{
	t_scene *v;
	
	if (argc != 2)
	{
		write(2, "Usage: ./fds [target_file.fds]\n", 31);
		return (1);
	}
	v = scene_init();
	v->fd = open((argv[1]), O_RDONLY);
	if (v->fd < 0)
	{
		write(2, "Error while reading the file.\n", 30);
		return (1);
	}
	v->first_star = star_array_to_lists(star_file_to_arrays(v->fd));
	star_projection(v->first_star, v);
	star_graphic_draw_stars(v->first_star, v, v->color);
	key_listener(v);
	mlx_loop(v->mlx);
	return (0);
}
