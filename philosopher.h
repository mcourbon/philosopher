/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shifterpro <shifterpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:14:14 by shifterpro        #+#    #+#             */
/*   Updated: 2023/11/09 14:34:41 by shifterpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				nbr_eat;
	long long		last_eat;
	long long		limit_eat;
	pthread_t		thread;
	pthread_mutex_t	m_eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_main	*data;
}	t_philo;

typedef struct s_main
{
	int				nbr_philo;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				eat_nbr;
	int				good;
	int				eat_count;
	long long		time;
	pthread_t		monitor;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_good;
	pthread_mutex_t	m_eat_count;
}	t_main;

typedef struct s_args
{
	t_main	*data;
	t_philo	*philo;
}	t_args;

int			monitor_eat(t_main *data);
int			monitor_life(t_main *data, int i);
void		*monitor(void *arg);

int			create_philo(t_main *data);
int			check_args(t_main *data);
void		ft_clear(t_main *data);
void		*philosopher(void *arg);

void		print_message(t_philo *philo, char *str);
void		pick_forks(t_main *data, int i);
void		start_half(t_main *data, int i);
void		philo_eat(t_philo *philo);

int			ft_strlen(const char *str);
int			ft_atoi(const char *str);
void		ft_putnbr_fd(int n, int fd);
long long	get_time(void);
void		ft_usleep(t_main *data, int stop_ms);
int			check_good(t_main *data);

#endif