/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:33:16 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/11 10:54:51 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	make_threads(int num, t_data *data);
char	start(int num, t_data *data);

int	main(int argc, char *argv[])
{
	t_data			*data;

	if (argc != 5 && argc != 6)
	{
		print_error(NULL);
		return (1);
	}
	data = malloc(sizeof(t_data) * (ft_atoi(argv[1]) + 2));
	if (data == NULL)
		return (print_error(NULL), 1);
	if (assign_data(argc, argv, data) || start(ft_atoi(argv[1]), data))
	{
		print_error(data);
		return (1);
	}
	free(data);
	return (0);
}

char	make_threads(int num, t_data *data)
{
	int			i;
	int			error;

	i = -1;
	error = 0;
	while (++i < num)
	{
		usleep (100);
		if (pthread_create(&data[i].philo, NULL, &routine, (void *) data))
		{
			error = 1;
			num = i;
			break ;
		}
	}
	i = 0;
	while (i < num)
	{
		if (pthread_join(data[i++].philo, NULL))
			return (1);
	}
	if (error)
		return (1);
	return (0);
}

char	start(int num, t_data *data)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (++i < num + 4)
	{
		if (pthread_mutex_init(&data[i].fork, NULL))
		{
			error = 1;
			num = i - 3;
			break ;
		}
	}
	if (error == 0 && make_threads(num, data))
		return (1);
	i = 0;
	while (i < num + 4)
	{
		if (pthread_mutex_destroy(&data[i++].fork))
			return (1);
	}
	if (error)
		return (1);
	return (0);
}
