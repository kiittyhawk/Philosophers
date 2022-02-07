/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:47:31 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/08 12:35:23 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	usleep_fixed(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}

void	eating(t_philo *ph)
{
	sem_wait(ph->data->mute);
	sem_wait(ph->data->forks);
	echo(1, LEFT_FORK, current_time(get_time(), ph->data->first_time), ph);
	sem_wait(ph->data->forks);
	echo(1, RIGHT_FORK, current_time(get_time(), ph->data->first_time), ph);
	sem_post(ph->data->mute);
	ph->last_eat = get_time();
	echo(1, EAT, current_time(ph->last_eat, ph->data->first_time), ph);
	usleep_fixed(ph->data->time_to_eat);
	ph->count_eat++;
	sem_post(ph->data->forks);
	sem_post(ph->data->forks);
}

void	sleeping(t_philo *ph)
{
	echo(1, SLEEP, current_time(get_time(), ph->data->first_time), ph);
	usleep_fixed(ph->data->time_to_sleep);
}

void	thinking(t_philo *ph)
{
	echo(1, THINK, current_time(get_time(), ph->data->first_time), ph);
}
