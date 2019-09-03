/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiskakov <iiskakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 07:10:01 by iiskakov          #+#    #+#             */
/*   Updated: 2019/07/01 02:06:25 by iiskakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	***parse_file_to_arrays(int fd)
{
	int		i;
	char	***arr;
	char	*line;

	i = 0;
	if (!(arr = (char ***)malloc(sizeof(char **) * 5000)))
		exit(-1);
	while (get_next_line(fd, &line))
	{
		arr[i] = ft_strsplit(line, ' ');
		i++;
		ft_strdel(&line);
	}
	arr[i] = NULL;
	return (arr);
}

t_point	*parse_create_head(void)
{
	t_point	*new_node;

	if (!(new_node = (t_point *)malloc(sizeof(t_point) * 1)))
		exit(-1);
	new_node->x = 0;
	new_node->y = 0;
	new_node->z = 0;
	new_node->h = 0;
	new_node->w = 0;
	new_node->is_head = 1;
	new_node->next = NULL;
	new_node->down = NULL;
	return (new_node);
}

void	parse_list_add_to_last(t_point *head, int j, int i, int k)
{
	t_point	*new_node;
	t_point	*current;

	current = head;
	if (!(new_node = (t_point *)malloc(sizeof(t_point))))
		exit(-1);
	new_node->x = j + 5;
	new_node->y = i + 5;
	new_node->z = k + 5;
	new_node->h = 0;
	new_node->w = 0;
	new_node->is_head = 0;
	new_node->down = NULL;
	new_node->next = NULL;
	if (head->next == NULL)
		head->next = new_node;
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	parse_link_bottom_point(t_point **head)
{
	t_point	*ptr;
	t_point	*ptr2;
	int		i;

	i = 0;
	while (head[i + 1])
	{
		ptr = head[i];
		ptr2 = head[i + 1];
		while (ptr)
		{
			if (ptr2)
				ptr->down = ptr2;
			ptr = ptr->next;
			if (ptr2->next)
				ptr2 = ptr2->next;
		}
		i++;
	}
}

t_point	**parse_array_to_lists(char ***arr)
{
	t_point	**head;
	int		i;
	int		j;

	i = 0;
	while (arr[i])
		i++;
	head = (t_point **)malloc(sizeof(t_point *) * (i + 1));
	i = 0;
	while (arr[i])
	{
		head[i] = parse_create_head();
		j = 0;
		while (arr[i][j])
		{
			parse_list_add_to_last(head[i], j, i, atoi(arr[i][j]));
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	head[i] = NULL;
	free(arr);
	return (head);
}
