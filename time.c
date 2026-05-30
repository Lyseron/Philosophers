/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:21:57 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/06 17:21:57 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to get the time now (at the time of the call) in milliseconds
unsigned long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

// to get more clean time
void	ft_usleep(unsigned long time_limit, t_all *a)
{
	unsigned long	time_start;

	time_start = ft_get_time();
	while (ft_get_time() - time_start < time_limit)
	{
		if (ft_dead_philo(a) == 1 || ft_check_enough_meal(a) == 1)
			break ;
		usleep(500);
	}
}
