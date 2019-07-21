/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 23:36:34 by smorty            #+#    #+#             */
/*   Updated: 2019/07/21 16:45:36 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

#include <stdio.h> //remove

typedef struct	s_room
{
	char			*name;
	int				x;
	int				y;
	int				type;
	int				edges;
	struct	s_room	**links;
}				t_room;

typedef struct	s_lemin
{
	int				ants;
	t_room			map;
}				t_lemin;

#endif
