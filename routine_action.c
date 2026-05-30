/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:53:15 by lyaberge          #+#    #+#             */
/*   Updated: 2026/02/25 17:53:15 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// take a fork then if one philo dead unlock the fork
// to avoid 1 keeping a ressource if they cant have both fork
static int	ft_take_fork_safe(t_philo *p, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	ft_print_action(p, "has taken a fork");
	if (ft_dead_philo(p->all) == 1)
	{
		pthread_mutex_unlock(fork);
		return (1);
	}
	return (0);
}

// to lock each fork so that the philos dont take the same one
// if the id is pair the philo take the fork1 then fork 2
// if the id is unpair the philo take the fork 2 then the fork 1
// -> avoid some deadlock if 2 philo try to take the same fork
// recheck death to avoid a thread being stuck if he cant take both
int	ft_lock_fork(t_philo *p)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	if (ft_dead_philo(p->all) == 1)
		return (1);
	if (p->id % 2 == 0)
	{
		fork1 = p->right_fork;
		fork2 = p->left_fork;
	}
	else
	{
		fork1 = p->left_fork;
		fork2 = p->right_fork;
	}
	if (ft_take_fork_safe(p, fork1) == 1)
		return (1);
	if (ft_take_fork_safe(p, fork2) == 1)
	{
		pthread_mutex_unlock(fork1);
		return (1);
	}
	return (0);
}

// give the forks back so that another philo can use it
void	ft_unlock_fork(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

// change the last_meal at the begining of the meal
// cause if at the end more chance to reach t_to_die
// update the nb of time a philo has eat
void	ft_philo_eat(t_philo *p)
{
	pthread_mutex_lock(&p->lock_meal);
	p->last_meal = ft_get_time();
	pthread_mutex_unlock(&p->lock_meal);
	ft_print_action(p, "is eating");
	ft_usleep(p->all->t_to_eat, p->all);
	pthread_mutex_lock(&p->lock_meal);
	p->nb_meal_eaten++;
	pthread_mutex_unlock(&p->lock_meal);
}

// to safly print the thinking and sleeping
// recheck the death of a philo after the sleep and don't print if dead
// 1ms of sleep after the thinking to desyncro a litle the philo
// so that for a big nb of philo all of them don't try to take the fork
// back all at the same time (syncro back)
void	ft_other_actions(t_philo *p)
{
	ft_print_action(p, "is sleeping");
	ft_usleep(p->all->t_to_nap, p->all);
	if (ft_dead_philo(p->all) == 1 || ft_check_enough_meal(p->all) == 1
		|| ft_stop_each_philo_eat(p) == 1)
		return ;
	ft_print_action(p, "is thinking");
	ft_usleep(1, p->all);
}
