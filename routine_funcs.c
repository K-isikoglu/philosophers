/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:03:59 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/11 11:31:01 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	is_stop_loop(t_data *data, char *dead);

char	is_stop(t_data *data)
{
	int			i;
	int			eat_count;
	static char	dead = 'n';

	pthread_mutex_lock(&data[data[0].philo_num].fork);
	if (dead == 'y')
		return (pthread_mutex_unlock(&data[data[0].philo_num].fork), 1);
	pthread_mutex_unlock(&data[data[0].philo_num].fork);
	if (is_stop_loop(data, &dead) == 1)
		return (1);
	i = 0;
	if (data[i].max_eat == -1)
		return (0);
	while (i < data[i].philo_num)
	{
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		eat_count = data[i].eat_count;
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		if (eat_count < data[i].max_eat)
			return (0);
		i++;
	}
	return (1);
}

char	is_stop_loop(t_data *data, char *dead)
{
	int	i;
	int	time_since_eat;

	i = 0;
	while (i < data[i].philo_num)
	{
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		time_since_eat = data[i].time_since_eat;
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		if (time_since_eat >= data[i].time_to_die)
		{
			pthread_mutex_lock(&data[data[0].philo_num].fork);
			if (*dead == 'y')
			{
				pthread_mutex_unlock(&data[data[0].philo_num].fork);
				return (1);
			}
			*dead = 'y';
			pthread_mutex_unlock(&data[data[0].philo_num].fork);
			print_message(data, i, 'd');
			return (1);
		}
		i++;
	}
	return (0);
}
