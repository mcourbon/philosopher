/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shifterpro <shifterpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:53:37 by shifterpro        #+#    #+#             */
/*   Updated: 2023/10/26 19:13:55 by shifterpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_good(t_main *data)
{
	pthread_mutex_lock(&data->m_good);
	if (!data->good)
	{
		pthread_mutex_unlock(&data->m_good);
		return (1);
	}
	pthread_mutex_unlock(&data->m_good);
	return (0);
}
