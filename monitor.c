/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 02:25:42 by lyaberge          #+#    #+#             */
/*   Updated: 2026/02/27 02:25:42 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// to stop the check each philo and see if one of them died
// or if must_eat input is more than 0 than it check if all
// philo have eaten at least must_eat time with monitor_for_must_eat
// usleep all 500ms to check a dead without taking all the cpu
void	*ft_monitor(void *argument)
{
	t_all	*a;
	int		i;

	a = (t_all *)argument;
	while (1)
	{
		i = 0;
		while (i < a->nb_of_p)
		{
			if (ft_check_philo_dead(&a->tab_philo[i]) == 1)
				return (ft_put_philo_dead(a), ft_print_dead(&a->tab_philo[i]),
					NULL);
			i++;
		}
		if (ft_for_must_eat(a) == 1)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
