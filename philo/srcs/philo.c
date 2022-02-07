/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:45:20 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/08 12:58:48 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->last_eat = philo->data->first_time;
	thinking(philo);
	if (philo->id % 2 != 0)
		usleep_fixed(philo->data->time_to_eat / 2);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	monitoring(t_philo **ph, t_data *data, pthread_t **thread)
{
	int	i;
	int	flag;

	usleep_fixed(data->time_to_die / 2);
	while (1)
	{
		i = 0;
		flag = 1;
		while (i < data->number_of_philosophers)
		{
			if (current_time(get_time(),
					(*ph)[i].last_eat) >= data->time_to_die)
			{
				echo(0, DIED, current_time(get_time(),
						data->first_time), &(*ph)[i]);
				return (free_threads(thread, data, 0));
			}
			if (data->must_eat > 0
				&& (*ph)[i].count_eat < data->must_eat)
				flag = 0;
			i++;
		}
		if (data->must_eat > 0 && flag == 1)
			return (free_threads(thread, data, 1));
	}
}

void	threads(t_data *data, t_philo **ph)
{
	int			i;
	int			num;
	pthread_t	*thread;

	i = 0;
	num = data->number_of_philosophers;
	thread = malloc(sizeof(pthread_t) * num);
	if (!thread)
		print_err(ERROR);
	data->first_time = get_time();
	while (i < num)
	{
		pthread_create(&thread[i], NULL, simulation, &((*ph)[i]));
		i++;
	}
	monitoring(ph, data, &thread);
}

void	init_fork(t_data *data, t_philo **ph, pthread_mutex_t **mutexes)
{
	int	i;
	int	num;

	i = 0;
	num = data->number_of_philosophers;
	while (i < num)
	{
		if (pthread_mutex_init(&(*mutexes)[i], NULL) != 0 ||
			pthread_mutex_init(&(*ph)[i].mute, NULL) != 0)
			print_err(ERROR);
		(*ph)[i].id = i;
		(*ph)[i].count_eat = 0;
		(*ph)[i].data = data;
		(*ph)[i].left = &(*mutexes)[i];
		if (i == num - 1)
			(*ph)[0].right = (*ph)[i].left;
		else
			(*ph)[i + 1].right = &(*mutexes)[i];
		i++;
	}
}

void	philo(t_data *data)
{
	t_philo			*ph;
	pthread_mutex_t	*mutexes;

	ph = malloc(sizeof(t_philo) * data->number_of_philosophers);
	mutexes = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (ph && mutexes)
	{
		init_fork(data, &ph, &mutexes);
		threads(data, &ph);
	}
	else
		print_err(ERROR);
}
