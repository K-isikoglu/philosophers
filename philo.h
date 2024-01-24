/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisikogl <kisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:21:06 by kisikogl          #+#    #+#             */
/*   Updated: 2023/03/11 11:14:17 by kisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define NRM "\x1B[0m"

typedef struct s_data	t_data;

struct s_data
{
	pthread_mutex_t	fork;
	pthread_t		philo;
	t_data			*left_x;
	t_data			*right_x;
	int				philo_x;
	int				eat_count;
	int				time_since_eat;
	char			has_finished;
	char			action;
	char			occupied;

	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
};

void	*routine(void *arg);
char	ft_think(t_data *data, int phil);
char	is_stop(t_data *data);
int		get_time(void);
int		get_msecs(struct timeval *start, char c);
void	is_finished(t_data data);
t_data	*neighbor(t_data *data, int x, char c);
void	print_message(t_data *data, int phil, char act);
void	print_error(t_data *data);
char	assign_data(int argc, char *argv[], t_data *data);
int		ft_atoi(const char *str);

#endif

/*
External functions:
memset, printf, malloc, free, write,
usleep, gettimeofday,
pthread_create, pthread_detach, pthread_join,
pthread_mutex_init, pthread_mutex_destroy,
pthread_mutex_lock, pthread_mutex_unlock
*/