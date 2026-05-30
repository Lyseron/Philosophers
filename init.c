/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:47:04 by lyaberge          #+#    #+#             */
/*   Updated: 2026/02/25 17:47:04 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if one forks fail in the loop the fonction destroy 
// all the already init mutex for the forks
// we start at i-- cause i is at the fail one
static void	ft_destroy_fork(pthread_mutex_t *fork, int i)
{
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&fork[i]);
	}
}

// if one lock in a philo fail in the loop the fonction destroy 
// all the already init lock 
// we start at i-- cause i is at the fail one
void	ft_destroy_lock(t_philo *p, int i)
{
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&p[i].lock_meal);
	}
}

// init the tab of fork (same nb of fork that nb of philo)
// init each fork as a mutex
// init the lock_dead mutex for the dead_p value
// init the lock_print mutex for the printf
int	ft_init_all(t_all *a)
{
	int	i;

	if (pthread_mutex_init(&a->lock_dead, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&a->lock_print, NULL) != 0)
		return (pthread_mutex_destroy(&a->lock_dead), 1);
	a->fork = malloc(sizeof(pthread_mutex_t) * a->nb_of_p);
	if (!a->fork)
		return (pthread_mutex_destroy(&a->lock_dead),
			pthread_mutex_destroy(&a->lock_print), 1);
	i = 0;
	while (i < a->nb_of_p)
	{
		if (pthread_mutex_init(&a->fork[i], NULL) != 0)
			return (ft_destroy_fork(a->fork, i), free(a->fork),
				pthread_mutex_destroy(&a->lock_dead),
				pthread_mutex_destroy(&a->lock_print), 1);
		i++;
	}
	return (0);
}

// create the philo_tab for nb of philo and 
// init all the value for each philo
int	ft_init_philo(t_all *a)
{
	int	i;

	a->tab_philo = malloc(sizeof(t_philo) * a->nb_of_p);
	if (!a->tab_philo)
		return (1);
	i = 0;
	while (i < a->nb_of_p)
	{
		a->tab_philo[i].id = i + 1;
		a->tab_philo[i].last_meal = 0;
		a->tab_philo[i].nb_meal_eaten = 0;
		a->tab_philo[i].all = a;
		a->tab_philo[i].left_fork = &a->fork[i];
		a->tab_philo[i].right_fork = &a->fork[(i + 1) % a->nb_of_p];
		if (pthread_mutex_init(&a->tab_philo[i].lock_meal, NULL) != 0)
			return (ft_destroy_lock(a->tab_philo, i), 1);
		i++;
	}
	return (0);
}
