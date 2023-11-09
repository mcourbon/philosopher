/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shifterpro <shifterpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:24:56 by shifterpro        #+#    #+#             */
/*   Updated: 2023/11/09 14:53:04 by shifterpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->good == 1)
	{
		printf("%lld %d %s\n", get_time() - philo->data->time, philo->id + 1,
			str);
	}
	pthread_mutex_unlock(&philo->data->m_print);
}

void	pick_forks(t_main *data, int i)
{
	data->philos[i].l_fork = &data->forks[i];
	if (i + 1 >= data->nbr_philo)
		data->philos[i].r_fork = &data->forks[0];
	else
		data->philos[i].r_fork = &data->forks[i + 1];
}

void	start_half(t_main *data, int i)
{
	while (i < data->nbr_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		data->philos[i].last_eat = data->time;
		data->philos[i].limit_eat = data->time + data->death_time;
		data->philos[i].nbr_eat = 0;
		pick_forks(data, i);
		pthread_mutex_init(&data->philos[i].m_eating, NULL);
		pthread_create(&data->philos[i].thread, NULL, philosopher,
			&data->philos[i]);
		i += 2;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->m_eating);
	print_message(philo, "is eating");
	philo->last_eat = get_time();
	philo->limit_eat = philo->last_eat + philo->data->death_time;
	pthread_mutex_unlock(&philo->m_eating);
	ft_usleep(philo->data, philo->data->eat_time);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo->data->eat_nbr != -1)
	{
		pthread_mutex_lock(&philo->data->m_eat_count);
		philo->nbr_eat += 1;
		philo->data->eat_count += 1;
		pthread_mutex_unlock(&philo->data->m_eat_count);
	}
}
