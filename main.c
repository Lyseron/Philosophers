/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-27 10:26:39 by lyaberge          #+#    #+#             */
/*   Updated: 2026-01-27 10:26:39 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// use if there is only 1 philo in input
static void	ft_for_one_philo(t_all *a)
{
	printf("0 1 has taken a fork\n");
	usleep(a->t_to_die * 1000);
	printf("%ld 1 died\n", a->t_to_die);
}

int	main(int ac, char *av[])
{
	t_all	a;

	if (ac == 1)
		return (0);
	if (ac < 5 || ac > 6)
		return (printf("Error\n"), 1);
	memset(&a, 0, sizeof(t_all));
	if (ft_check_init(ac, av, &a) == 1)
		return (printf("Error\n"), 1);
	if (a.nb_of_p == 1)
		return (ft_for_one_philo(&a), 0);
	if (ft_init_all(&a) == 1)
		return (printf("Error\n"), 1);
	if (ft_init_philo(&a) == 1)
		return (ft_clean_if_error(&a), printf("Error\n"), 1);
	if (ft_thread_create_and_join(&a) == 1)
		return (ft_destroy_lock_meal(&a), ft_clean_if_error(&a),
			printf("Error\n"), 1);
	ft_clean_all(&a);
	return (0);
}
