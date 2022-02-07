/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:20:47 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/06 18:20:54 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

uint64_t	get_time(void)
{
	static struct timeval	time;

	if (gettimeofday(&time, NULL))
		print_err(ERROR);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

uint64_t	current_time(uint64_t now, uint64_t start)
{
	return (now - start);
}
