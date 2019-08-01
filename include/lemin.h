/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 15:35:02 by smorty            #+#    #+#             */
/*   Updated: 2019/08/01 23:15:24 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# define INF_PATH		0xABCDEF
# define ABS(x) (x > 0 ? x : -x)

typedef struct	s_vertex
{
	char			*name;
	int				index;
	int				minpath;
	int				x;
	int				y;
	int				splitted;
	int				closed;
	struct s_vertex	*path;
}				t_vertex;

typedef struct	s_queue
{
	t_vertex		*top;
	struct s_queue	*next;
	struct s_queue	*prev;
}				t_queue;

typedef struct	s_paths
{
	t_queue			*path;
	int				len;
	int				len0;
	struct s_paths	*next;
	struct s_paths	*prev;
}				t_paths;

typedef struct	s_ants
{
	int				num;
	t_vertex		*room;
	t_queue			*path;
	struct s_ants	*next;
}				t_ants;

typedef struct	s_lemin
{
	int				ants_num;
	int				verteces;
	int				**edges;
	t_vertex		**rooms;
	t_vertex		*start;
	t_vertex		*end;
	t_ants			*ants;
}				t_lemin;

t_lemin			*create_ant_colony(char *filename);
t_vertex		**process_file(t_lemin *colony, int fd);
int				check_line(char *line);
void			error(int error_type);
int				ft_printf(const char *s, ...);

t_queue			*new_queue(t_vertex *start);
void			push(t_queue **q, t_vertex *val);
void			push_front(t_queue **q, t_vertex *val);
void			pop(t_queue **q);

void			clean_after_search(t_vertex **rooms, int verteces);
t_paths			*find_paths(t_lemin *colony);
t_queue			*dijkstra(t_lemin *colony, int *len);
t_queue			*bfs(t_lemin *colony, int *len);
void			open_the_gates(t_lemin *colony, t_paths *path_list);

#endif
