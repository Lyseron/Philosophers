/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 01:56:06 by lyaberge          #+#    #+#             */
/*   Updated: 2026/03/02 01:56:06 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to free and destroy in case of error 
void	ft_clean_if_error(t_all *a)
{
	int	i;

	i = 0;
	while (i < a->nb_of_p)
	{
		pthread_mutex_destroy(&a->fork[i]);
		i++;
	}
	free(a->fork);
	free(a->tab_philo);
	pthread_mutex_destroy(&a->lock_dead);
	pthread_mutex_destroy(&a->lock_print);
}

// clean all at the end of the program
void	ft_clean_all(t_all *a)
{
	int	i;

	i = 0;
	while (i < a->nb_of_p)
	{
		pthread_mutex_destroy(&a->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&a->lock_dead);
	pthread_mutex_destroy(&a->lock_print);
	ft_destroy_lock_meal(a);
	free(a->tab_philo);
	free(a->fork);
}

// dstroy the lock meal mutex on each philo
void	ft_destroy_lock_meal(t_all *a)
{
	int	i;

	i = 0;
	while (i < a->nb_of_p)
	{
		pthread_mutex_destroy(&a->tab_philo[i].lock_meal);
		i++;
	}
}
