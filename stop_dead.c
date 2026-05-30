/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_dead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:19:52 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/06 17:19:52 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check dead_p safely to see if a philo has died
// to stop the routine if dead
int	ft_dead_philo(t_all *a)
{
	int	is_philo_dead;

	pthread_mutex_lock(&a->lock_dead);
	is_philo_dead = a->dead_p;
	pthread_mutex_unlock(&a->lock_dead);
	return (is_philo_dead);
}

// to say that a philo is indeed dead by updtating dead_p
void	ft_put_philo_dead(t_all *a)
{
	pthread_mutex_lock(&a->lock_dead);
	a->dead_p = 1;
	pthread_mutex_unlock(&a->lock_dead);
}

// fonction to check if a philo has died
//because the time that he eat last got over the time_to_die
int	ft_check_philo_dead(t_philo *p)
{
	unsigned long	time_now;
	unsigned long	dernier_meal;

	if (ft_dead_philo(p->all) == 1)
		return (1);
	time_now = ft_get_time();
	pthread_mutex_lock(&p->lock_meal);
	dernier_meal = p->last_meal;
	pthread_mutex_unlock(&p->lock_meal);
	if (time_now - dernier_meal >= p->all->t_to_die)
		return (1);
	return (0);
}
