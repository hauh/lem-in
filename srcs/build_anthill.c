/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:29:39 by smorty            #+#    #+#             */
/*   Updated: 2019/08/05 23:43:22 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	*new_room(char *line, t_vertex **rooms)
{
	static int	n = 0;
	t_vertex	*new;
	char		**split;

	if (!(new = (t_vertex *)malloc(sizeof(t_vertex)))
		|| !(split = ft_strsplit(line, ' ')))
		error(errno);
	if (!split[0] || *split[0] == 'L' || !split[1] || !split[2] || split[3])
		error(ERR_ROOM);
	new->name = split[0];
	new->x = ft_atoi(split[1]);
	new->y = ft_atoi(split[2]);
	if (!ft_strequ(ft_itoa(new->x), split[1])
		|| !ft_strequ(ft_itoa(new->y), split[2]))
		error(ERR_ROOM);
	free(split[1]);
	free(split[2]);
	free(split);
	rooms[n] = new;
	new->index = n++;
	new->minpath = INF_PATH;
	new->splitted = 0;
	new->closed = 0;
	new->path = NULL;
	return (new);
}

static int	connect(char *line, int **edges, t_vertex **rooms_list)
{
	char	**split;
	int		i1;
	int		i2;

	if (!(split = ft_strsplit(line, '-')))
		error(errno);
	i1 = 0;
	i2 = 0;
	while (rooms_list[i1] && !ft_strequ(rooms_list[i1]->name, split[0]))
		++i1;
	while (rooms_list[i2] && !ft_strequ(rooms_list[i2]->name, split[1]))
		++i2;
	if (!rooms_list[i1] || !rooms_list[i2])
		return (0);
	edges[i1][i2] = 1;
	edges[i2][i1] = 1;
	free(split[0]);
	free(split[1]);
	free(split);
	return (1);
}

static void	linking(t_mfile *map, int **edges, t_vertex **rooms)
{
	while (map)
	{
		if (map->type != COMMENT
			&& (map->type != LINK || !connect(map->line, edges, rooms)))
		{
			map->prev->next = NULL;
			while (map->next)
			{
				free(map->line);
				map = map->next;
				free(map->prev);
			}
			free(map->line);
			free(map);
			return ;
		}
		map = map->next;
	}
}

t_vertex	**build_anthill(t_mfile *map, int **edges, int verteces)
{
	t_vertex **rooms;

	while (map->type == COMMENT || !map->type)
		map = map->next;
	if (!(rooms = (t_vertex **)malloc(sizeof(t_vertex *) * (verteces + 1))))
		error(errno);
	rooms[verteces] = NULL;
	while (map->type != LINK)
	{
		if (map->type != COMMENT)
			new_room(map->line, rooms);
		map = map->next;
	}
	linking(map, edges, rooms);
	return (rooms);
}
