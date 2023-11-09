/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shifterpro <shifterpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:21:58 by shifterpro        #+#    #+#             */
/*   Updated: 2023/11/09 16:44:51 by shifterpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->eat_nbr != -1
			&& philo->nbr_eat == philo->data->eat_nbr)
			return (NULL);
		if (check_good(philo->data))
			return (NULL);
		philo_eat(philo);
		if (check_good(philo->data))
			return (NULL);
		print_message(philo, "is sleeping");
		ft_usleep(philo->data, philo->data->sleep_time);
		if (check_good(philo->data))
			return (NULL);
		print_message(philo, "is thinking");
	}
}

void	ft_clear(t_main *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		pthread_detach(data->philos[i].thread);
	free(data->philos);
	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_good);
	pthread_mutex_destroy(&data->m_eat_count);
}

int	create_philo(t_main *data)
{
	int	i;

	i = -1;
	data->eat_count = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (data->philos == NULL || data->forks == NULL)
		return (ft_clear(data), 1);
	while (++i < data->nbr_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_good, NULL);
	pthread_mutex_init(&data->m_eat_count, NULL);
	data->time = get_time();
	start_half(data, 0);
	ft_usleep(data, 10);
	start_half(data, 1);
	pthread_create(&data->monitor, NULL, monitor, data);
	pthread_join(data->monitor, NULL);
	ft_clear(data);
	return (0);
}

int	check_args(t_main *data)
{
	if (!(data->nbr_philo > 0))
		return (1);
	if (!(data->death_time > 0))
		return (1);
	if (!(data->eat_time > 0))
		return (1);
	if (!(data->sleep_time > 0))
		return (1);
	if (!(data->eat_nbr > 0) && data->eat_nbr != -1)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	data;

	if (ac >= 5 && ac <= 6)
	{
		data.nbr_philo = ft_atoi(av[1]);
		data.death_time = ft_atoi(av[2]);
		data.eat_time = ft_atoi(av[3]);
		data.sleep_time = ft_atoi(av[4]);
		data.eat_nbr = -1;
		if (ac == 6)
			data.eat_nbr = ft_atoi(av[5]);
		if (check_args(&data))
			return (printf("Wrong arguments\n"), 1);
		data.good = 1;
		if (create_philo(&data) == 1)
			return (printf("Malloc failed"), 1);
	}
	else
		return (printf("Wrong number of arguments\n"), 1);
	return (0);
}
