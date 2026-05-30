/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-02-17 10:25:51 by lyaberge          #+#    #+#             */
/*   Updated: 2026-02-17 10:25:51 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

static int	ft_verif_digit(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (1);
	if (s[0] == '+')
		i++;
	if (s[i] == '\0')
		return (1);
	while (s[i])
	{
		if (ft_is_digit(s[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_atol(char *s, long *nb_return)
{
	int		i;

	i = 0;
	*nb_return = 0;
	if (!s || s[0] == '\0')
		return (1);
	if (ft_verif_digit(s) == 1)
		return (1);
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			return (1);
		i++;
	}
	if (s[i] == '\0')
		return (1);
	while (ft_is_digit(s[i]) == 0)
	{
		*nb_return = *nb_return * 10 + (s[i] - 48);
		if (*nb_return > INT_MAX)
			return (1);
		i++;
	}
	*nb_return = *nb_return;
	return (0);
}

int	ft_check_init(int ac, char *av[], t_all *a)
{
	long	nb;

	nb = 0;
	if (ft_check_atol(av[1], &nb) == 1 || nb == 0)
		return (1);
	a->nb_of_p = nb;
	if (ft_check_atol(av[2], &nb) == 1 || nb == 0)
		return (1);
	a->t_to_die = nb;
	if (ft_check_atol(av[3], &nb) == 1 || nb == 0)
		return (1);
	a->t_to_eat = nb;
	if (ft_check_atol(av[4], &nb) == 1 || nb == 0)
		return (1);
	a->t_to_nap = nb;
	if (ac == 6)
	{
		if (ft_check_atol(av[5], &nb) == 1 || nb == 0)
			return (1);
		a->nb_of_time_all_have_eat = nb;
	}
	return (0);
}
