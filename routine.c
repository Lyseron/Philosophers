/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-29 13:15:42 by lyaberge          #+#    #+#             */
/*   Updated: 2026-01-29 13:15:42 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// delay the even nb philo by t_to_eat / 2
// and the off nb philo by t_to_eat / 4
// if t_to_eat = 200 the even nb wait 100 before starting the routine
// and the off nb philo wait 50
// -> to prevent all philo to try to take the fork at the same time at
// the begining 
static void	ft_routine_delay(t_philo *p)
{
	if (p->id % 2 == 0)
		ft_usleep(p->all->t_to_eat / 2, p->all);
	else
		ft_usleep(p->all->t_to_eat / 4, p->all);
}

// routine of a philo before death 
// check if no philo has died then take the forks then eat
// put the fork back then sleep and think while the other eat
// ft_stop_philo_has_enough(p) -> stop 1 philo for eating too much
// ft_check_enough_meal stop all the routine cause all philo has eat enough
void	*ft_routine(void *argument)
{
	t_philo	*p;

	p = (t_philo *)argument;
	ft_routine_delay(p);
	while (ft_dead_philo(p->all) != 1 && ft_check_enough_meal(p->all) != 1)
	{
		if (ft_stop_each_philo_eat(p) == 1)
			break ;
		if (ft_lock_fork(p) == 1)
			break ;
		if (ft_dead_philo(p->all) == 1 || ft_check_enough_meal(p->all) == 1
			|| ft_stop_each_philo_eat(p) == 1)
		{
			ft_unlock_fork(p);
			break ;
		}
		ft_philo_eat(p);
		ft_unlock_fork(p);
		if (ft_dead_philo(p->all) == 1 || ft_check_enough_meal(p->all) == 1
			|| ft_stop_each_philo_eat(p) == 1)
			break ;
		ft_other_actions(p);
	}
	return (NULL);
}
