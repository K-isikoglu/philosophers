/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:02:38 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/11 15:08:20 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	take_fork(t_data *data, int phil, int occupied, char act);
char	take_left_fork(t_data *data, int phil, int occupied, char act);
char	ft_think_loop(t_data *data, int phil, struct timeval start);
void	is_wait(t_data *data, int phil);

char	ft_think(t_data *data, int phil)
{
	struct timeval	start;

	get_msecs(&start, 0);
	pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
	data[phil].action = 't';
	pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
	print_message(data, phil, 't');
	return (ft_think_loop(data, phil, start));
}

char	take_fork(t_data *data, int phil, int occupied, char act)
{
	pthread_mutex_lock(&data[data[0].philo_num + 3].fork);
	occupied = data[phil].occupied;
	pthread_mutex_unlock(&data[data[0].philo_num + 3].fork);
	if (occupied == 0)
	{
		pthread_mutex_lock(&data[data[0].philo_num + 3].fork);
		data[phil].occupied++;
		pthread_mutex_unlock(&data[data[0].philo_num + 3].fork);
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		if (data[phil].left_x->action != 'w')
			data[phil].action = 'w';
		else
			data[phil].action = 'l';
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		print_message(data, phil, 'f');
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		act = data[phil].left_x->action;
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		pthread_mutex_lock(&data[data[0].philo_num + 3].fork);
		occupied = data[phil].left_x->occupied;
		pthread_mutex_unlock(&data[data[0].philo_num + 3].fork);
		if (occupied > 0 && act != 'e' && act != 'w')
			return (1);
	}
	return (0);
}

char	take_left_fork(t_data *data, int phil, int occupied, char act)
{
	pthread_mutex_lock(&data[data[0].philo_num + 3].fork);
	occupied = data[phil].left_x->occupied;
	pthread_mutex_unlock(&data[data[0].philo_num + 3].fork);
	if (occupied == 0)
	{
		pthread_mutex_lock(&data[data[0].philo_num + 3].fork);
		data[phil].left_x->occupied++;
		pthread_mutex_unlock(&data[data[0].philo_num + 3].fork);
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		if (data[phil].right_x->action != 'w')
			data[phil].action = 'w';
		else
			data[phil].action = 'r';
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		print_message(data, phil, 'f');
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		act = data[phil].right_x->action;
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		pthread_mutex_lock(&data[data[0].philo_num + 3].fork);
		occupied = data[phil].occupied;
		pthread_mutex_unlock(&data[data[0].philo_num + 3].fork);
		if (occupied > 0 && act != 'e' && act != 'w')
			return (1);
	}
	return (0);
}

char	ft_think_loop(t_data *data, int phil, struct timeval start)
{
	char	occupied;
	char	act;

	act = 0;
	occupied = 0;
	while (1)
	{
		if (is_stop(data))
			return (1);
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		if (data[phil].action == 'l' || data[phil].action == 'r')
			is_wait(data, phil);
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		if (take_fork(data, phil, occupied, act) == 1)
			return (0);
		if (take_left_fork(data, phil, occupied, act) == 1)
			return (0);
		usleep(500);
		pthread_mutex_lock(&data[data[0].philo_num + 2].fork);
		data[phil].time_since_eat += get_msecs(&start, 1);
		pthread_mutex_unlock(&data[data[0].philo_num + 2].fork);
		get_msecs(&start, 0);
	}
}

void	is_wait(t_data *data, int phil)
{
	if (data[phil].action == 'l' && data[phil].left_x->action != 'w')
		data[phil].action = 'w';
	else if (data[phil].action == 'r' && data[phil].right_x->action != 'w')
		data[phil].action = 'w';
}
