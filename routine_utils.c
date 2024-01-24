/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:57:40 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/11 10:58:43 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	static int				i;
	static struct timeval	start;
	struct timeval			current;
	int						time;

	if (i == 0)
		gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000 + current.tv_usec / 1000)
		- (start.tv_sec * 1000 + start.tv_usec / 1000);
	i = 1;
	return (time);
}

int	get_msecs(struct timeval *start, char c)
{
	struct timeval			current;
	int						time;

	if (c == 0)
	{
		gettimeofday(start, NULL);
		return (0);
	}
	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000 + current.tv_usec / 1000)
		- (start->tv_sec * 1000 + start->tv_usec / 1000);
	return (time);
}

void	is_finished(t_data data)
{
	if (data.eat_count >= data.max_eat)
		data.has_finished = 1;
	else
		data.has_finished = 0;
}

int	print_act(t_data *data, char act)
{
	if (act == 'd')
	{
		printf("%sdied%s\n", RED, NRM);
		return (0);
	}
	else if (act == 'f')
		printf("%shas taken a fork\n", GRN);
	else if (act == 'e')
	{
		printf("%sis eating\n", BLU);
		if (is_stop(data) == 1)
			return (0);
	}
	else if (act == 's')
		printf("%sis sleeping\n", YEL);
	else if (act == 't')
		printf("%sis thinking\n", MAG);
	return (1);
}

void	print_message(t_data *data, int phil, char act)
{
	pthread_mutex_t	*mut;
	int				time;
	static char		print = 1;

	mut = &data[data[0].philo_num + 1].fork;
	pthread_mutex_lock(mut);
	if (print == 0)
	{
		pthread_mutex_unlock(mut);
		return ;
	}
	time = get_time();
	printf("%s%d %s%d ", CYN, time, NRM, phil + 1);
	print = print_act(data, act);
	pthread_mutex_unlock(mut);
}
