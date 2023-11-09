/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shifterpro <shifterpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:54:14 by shifterpro        #+#    #+#             */
/*   Updated: 2023/10/26 19:24:23 by shifterpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	monitor_eat(t_main *data)
{
	pthread_mutex_lock(&data->m_eat_count);
	if (data->eat_count >= data->nbr_philo * data->eat_nbr
		&& data->eat_nbr != -1)
	{
		pthread_mutex_lock(&data->m_good);
		data->good = 0;
		pthread_mutex_unlock(&data->m_good);
		pthread_mutex_unlock(&data->m_eat_count);
		return (1);
	}
	pthread_mutex_unlock(&data->m_eat_count);
	return (0);
}

int	monitor_life(t_main *data, int i)
{
	if (get_time() > data->philos[i].limit_eat)
	{
		pthread_mutex_lock(&data->m_print);
		pthread_mutex_lock(&data->m_good);
		data->good = 0;
		pthread_mutex_unlock(&data->m_good);
		printf("%lld %d died\n", get_time() - data->time, i + 1);
		pthread_mutex_unlock(&data->m_print);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_main	*data;
	int		i;

	data = (t_main *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->philos[i].m_eating);
			if (monitor_life(data, i) || monitor_eat(data))
			{
				pthread_mutex_unlock(&data->philos[i].m_eating);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].m_eating);
		}
		usleep(100);
	}
}
