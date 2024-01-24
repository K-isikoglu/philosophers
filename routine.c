/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:57:44 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/11 11:14:07 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	ft_eat(t_data *data, int phil);
char	ft_sleep(t_data *data, int phil);
void	routine_loop(t_data *data, int x);

void	*routine(void *arg)
{
	t_data		*data;
	int			x;
	static int	i;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->fork);
	x = data[i++].philo_x;
	pthread_mutex_unlock(&data->fork);
	usleep(100000);
	if (x % 2 != 0)
		usleep(5000);
	if (ft_think(data, x))
		return (NULL);
	routine_loop(data, x);
	return (NULL);
}

void	routine_loop(t_data *data, int x)
{
	while (1)
	{
		pthread_mutex_lock(&data[x].fork);
		pthread_mutex_lock(&data[x].left_x->fork);
		if (ft_eat(data, x))
		{
			pthread_mutex_unlock(&data[x].fork);
			pthread_mutex_unlock(&data[x].left_x->fork);
			break ;
		}
		is_finished(data[x]);
		pthread_mutex_unlock(&data[x].fork);
		pthread_mutex_unlock(&data[x].left_x->fork);
		if (ft_sleep(data, x) || ft_think(data, x))
			break ;
	}
}

char	ft_eat(t_data *data, int phil)
{
	struct timeval	delta;
	struct timeval	start;

	get_msecs(&start, 0);
	delta = start;
	pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
	data[phil].action = 'e';
	data[phil].time_since_eat = 0;
	data[phil].eat_count++;
	pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
	print_message(data, phil, 'e');
	while (get_msecs(&start, 1) < data[phil].time_to_eat)
	{
		if (is_stop(data))
			return (1);
		usleep(700);
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		data[phil].time_since_eat += get_msecs(&delta, 1);
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		get_msecs(&delta, 0);
	}
	pthread_mutex_lock(&data[data[0].philo_num + 3].fork);
	data[phil].occupied = 0;
	data[phil].left_x->occupied = 0;
	return (pthread_mutex_unlock(&data[data[0].philo_num + 3].fork), 0);
}

char	ft_sleep(t_data *data, int phil)
{
	struct timeval	start;
	struct timeval	delta;

	get_msecs(&start, 0);
	delta = start;
	pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
	data[phil].action = 's';
	pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
	print_message(data, phil, 's');
	while (get_msecs(&start, 1) < data[phil].time_to_sleep)
	{
		if (is_stop(data))
			return (1);
		usleep(700);
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		data[phil].time_since_eat += get_msecs(&delta, 1);
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		get_msecs(&delta, 0);
	}
	return (0);
}
