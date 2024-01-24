/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:18:37 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/11 11:00:44 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	check_for_error(t_data *data);

char	assign_data(int argc, char *argv[], t_data *data)
{
	int	i;
	int	num;

	i = 0;
	num = ft_atoi(argv[1]);
	while (i < num)
	{
		data[i].philo_x = i;
		data[i].philo_num = num;
		data[i].time_to_die = ft_atoi(argv[2]);
		data[i].time_to_eat = ft_atoi(argv[3]);
		data[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data[i].max_eat = ft_atoi(argv[5]);
		else
			data[i].max_eat = -1;
		data[i].eat_count = 0;
		data[i].time_since_eat = 0;
		data[i].left_x = neighbor(data, i, 'l');
		data[i].right_x = neighbor(data, i, 'r');
		data[i].action = 'n';
		data[i].occupied = 0;
		i++;
	}
	return (check_for_error(data));
}

t_data	*neighbor(t_data *data, int x, char c)
{
	if (data[x].philo_num < 2)
		return (&data[x]);
	if (c == 'l')
	{
		if (x == 0)
			return (&data[data[x].philo_num - 1]);
		return (&data[x - 1]);
	}
	else
	{
		if (x == data[x].philo_num - 1)
			return (&data[0]);
		return (&data[x + 1]);
	}
}

char	check_for_error(t_data *data)
{
	int	i;

	i = 0;
	if (data[i].philo_num < 1 || data[i].time_to_die < 50
		|| data[i].time_to_eat < 50 || data[i].time_to_sleep < 50)
		return (1);
	while (i < data[i].philo_num)
	{
		i++;
	}
	return (0);
}

void	print_error(t_data *data)
{
	if (data != NULL)
		free(data);
	printf("Error\n");
}
