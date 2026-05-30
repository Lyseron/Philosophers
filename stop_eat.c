/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_eat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:18:14 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/10 17:18:14 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// return 1 if the philo all eat enough
int	ft_check_enough_meal(t_all *a)
{
	int	has_philo_eat_enough;

	pthread_mutex_lock(&a->lock_dead);
	has_philo_eat_enough = a->stop_have_all_eat;
	pthread_mutex_unlock(&a->lock_dead);
	return (has_philo_eat_enough);
}

// put the bool at 1 for the stop condition of all philo eat enough
void	ft_put_philo_eat_enough(t_all *a)
{
	pthread_mutex_lock(&a->lock_dead);
	a->stop_have_all_eat = 1;
	pthread_mutex_unlock(&a->lock_dead);
}

// return 1 if all philo eat the nb_of_time or more and put the
// stop bool at 1
// return 0 if at least 1 philo did not eat enough
int	ft_for_must_eat(t_all *a)
{
	int		nb_meal;
	int		count_philo_eat;
	int		i;

	if (a->nb_of_time_all_have_eat > 0)
	{
		i = 0;
		count_philo_eat = 0;
		while (i < a->nb_of_p)
		{
			pthread_mutex_lock(&a->tab_philo[i].lock_meal);
			nb_meal = a->tab_philo[i].nb_meal_eaten;
			pthread_mutex_unlock(&a->tab_philo[i].lock_meal);
			if (nb_meal >= a->nb_of_time_all_have_eat)
				count_philo_eat++;
			i++;
		}
		if (count_philo_eat == a->nb_of_p)
			return (ft_put_philo_eat_enough(a), 1);
	}
	return (0);
}

// to stop 1 philo individual from eating more than the input
int	ft_stop_each_philo_eat(t_philo *p)
{
	int		nb_meal;

	if (p->all->nb_of_time_all_have_eat > 0)
	{
		pthread_mutex_lock(&p->lock_meal);
		nb_meal = p->nb_meal_eaten;
		pthread_mutex_unlock(&p->lock_meal);
		if (nb_meal >= p->all->nb_of_time_all_have_eat)
			return (1);
	}
	return (0);
}
