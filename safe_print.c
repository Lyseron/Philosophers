/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:49:58 by lyaberge          #+#    #+#             */
/*   Updated: 2026/02/25 17:49:58 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to safely print an action and stop printing after the dead of a philo
void	ft_print_action(t_philo *p, char *msg_to_print)
{
	int				is_dead;
	int				has_eat_enough;
	unsigned long	time_of_action;

	pthread_mutex_lock(&p->all->lock_print);
	pthread_mutex_lock(&p->all->lock_dead);
	is_dead = p->all->dead_p;
	has_eat_enough = p->all->stop_have_all_eat;
	if (is_dead == 1 || has_eat_enough == 1)
	{
		pthread_mutex_unlock(&p->all->lock_dead);
		pthread_mutex_unlock(&p->all->lock_print);
		return ;
	}
	pthread_mutex_unlock(&p->all->lock_dead);
	time_of_action = ft_get_time() - p->all->starting_time;
	printf("%lu %d %s\n", time_of_action, p->id, msg_to_print);
	pthread_mutex_unlock(&p->all->lock_print);
}

// to safely print the death of a philo
void	ft_print_dead(t_philo *p)
{
	unsigned long	time_of_death;

	pthread_mutex_lock(&p->all->lock_print);
	time_of_death = ft_get_time() - p->all->starting_time;
	printf("%lu %d died\n", time_of_death, p->id);
	pthread_mutex_unlock(&p->all->lock_print);
}
