/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-27 10:22:55 by lyaberge          #+#    #+#             */
/*   Updated: 2026-01-27 10:22:55 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_all	t_all;

typedef struct s_philo
{
	int				id;
	int				nb_meal_eaten;
	unsigned long	last_meal;
	t_all			*all;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock_meal;
}	t_philo;

typedef struct s_all
{
	int				nb_of_p;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_nap;
	int				nb_of_time_all_have_eat;
	int				dead_p;
	int				stop_have_all_eat;
	unsigned long	starting_time;
	t_philo			*tab_philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_print;
}	t_all;

//parsing
int				ft_check_init(int ac, char *av[], t_all *p);

// init
int				ft_init_philo(t_all *a);
int				ft_init_all(t_all *a);
void			ft_destroy_lock(t_philo *p, int i);

//routine
void			*ft_routine(void *argument);

// time
unsigned long	ft_get_time(void);
void			ft_usleep(unsigned long time_limit, t_all *a);

// monitor
void			*ft_monitor(void	*argument);

// safe print
void			ft_print_action(t_philo *p, char *msg_to_print);
void			ft_print_dead(t_philo *p);

// action_routine
void			ft_other_actions(t_philo *p);
void			ft_philo_eat(t_philo *p);
void			ft_unlock_fork(t_philo *p);
int				ft_lock_fork(t_philo *p);

//thread creation
int				ft_thread_create_and_join(t_all *a);

// stop_dead
int				ft_check_philo_dead(t_philo *p);
int				ft_dead_philo(t_all *a);
void			ft_put_philo_dead(t_all *a);

// stop_eat
int				ft_stop_each_philo_eat(t_philo *p);
int				ft_for_must_eat(t_all *a);
int				ft_check_enough_meal(t_all *a);
int				ft_stop_each_philo_eat(t_philo *p);

// cleanup
void			ft_clean_if_error(t_all *a);
void			ft_clean_all(t_all *a);
void			ft_destroy_lock_meal(t_all *a);

#endif