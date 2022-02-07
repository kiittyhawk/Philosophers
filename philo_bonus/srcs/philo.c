/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:45:20 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/08 12:38:05 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	*monitoring(void *ph)
{
	t_philo	*philo;

	philo = ph;
	while (1)
	{
		if (current_time(get_time(), philo->last_eat)
			>= philo->data->time_to_die)
		{
			echo(0, DIED, current_time(get_time(),
					philo->data->first_time), philo);
			exit(2);
		}
		if (philo->data->must_eat > 0
			&& philo->count_eat >= philo->data->must_eat)
		{
			sem_post(philo->data->forks);
			sem_post(philo->data->forks);
			exit(3);
		}
		usleep(50);
	}
}

void	*simulation(t_philo *ph)
{
	pthread_t	monitor;

	ph->last_eat = get_time();
	pthread_create(&monitor, NULL, monitoring, ph);
	thinking(ph);
	if (ph->id % 2 != 0)
		usleep_fixed(ph->data->time_to_eat / 2);
	while (1)
	{
		eating(ph);
		sleeping(ph);
		thinking(ph);
	}
}

void	init_forks(t_data *data, t_philo **ph)
{
	int			i;
	int			num;
	int			code;

	i = 0;
	num = data->number_of_philosophers;
	data->first_time = get_time();
	while (i < num)
	{
		(*ph)[i].pid = fork();
		if ((*ph)[i].pid == 0)
			simulation(&((*ph)[i]));
		i++;
	}
	i = 0;
	while (i < num)
	{
		waitpid(-1, &code, 0);
		if (WEXITSTATUS(code) == 2)
			return (kill_proc(*ph, num));
		i++;
	}
}

void	init_philo(t_data *data, t_philo **ph)
{
	int	i;
	int	num;

	i = 0;
	num = data->number_of_philosophers;
	while (i < num)
	{
		(*ph)[i].id = i;
		(*ph)[i].count_eat = 0;
		(*ph)[i].data = data;
		(*ph)[i].flag = 1;
		i++;
	}
}

void	philo(t_data *data)
{
	t_philo	*ph;

	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("mute");
	ph = malloc(sizeof(t_philo) * data->number_of_philosophers);
	data->forks = sem_open("forks", O_CREAT, 0666,
			data->number_of_philosophers);
	data->print = sem_open("print", O_CREAT, 0666, 1);
	data->mute = sem_open("mute", O_CREAT, 0666, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		|| data->mute == SEM_FAILED)
		print_err(ERROR);
	else
	{
		init_philo(data, &ph);
		init_forks(data, &ph);
	}
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("mute");
	free(ph);
}
