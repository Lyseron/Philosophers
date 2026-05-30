/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:23:48 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/06 17:23:48 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// in case of error when creating thread join the thread before
// destroying them and put philo dead for the monitor to see
static void	ft_error_create_thread(t_all *a, int i)
{
	ft_put_philo_dead(a);
	while (i > 0)
	{
		i--;
		pthread_join(a->tab_philo[i].thread, NULL);
	}
}

// create all the thread and set the starting time
int	ft_thread_create_and_join(t_all *a)
{
	int				i;
	pthread_t		monitor;

	a->starting_time = ft_get_time();
	i = -1;
	while (++i < a->nb_of_p)
	{
		pthread_mutex_lock(&a->tab_philo[i].lock_meal);
		a->tab_philo[i].last_meal = a->starting_time;
		pthread_mutex_unlock(&a->tab_philo[i].lock_meal);
		if (pthread_create(&a->tab_philo[i].thread, NULL,
				ft_routine, &a->tab_philo[i]) != 0)
			return (ft_error_create_thread(a, i), 1);
	}
	if (pthread_create(&monitor, NULL, ft_monitor, a) != 0)
		return (ft_error_create_thread(a, a->nb_of_p), 1);
	if (pthread_join(monitor, NULL) != 0)
		return (ft_error_create_thread(a, a->nb_of_p), 1);
	i = -1;
	while (++i < a->nb_of_p)
		if (pthread_join(a->tab_philo[i].thread, NULL) != 0)
			return (1);
	return (0);
}
