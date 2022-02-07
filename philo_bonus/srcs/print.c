/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:46:28 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/06 18:22:25 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	echo(int flag, char *str, uint64_t time, t_philo *ph)
{
	sem_wait(ph->data->print);
	printf("%lldms %d philo %s", time, ph->id + 1, str);
	if (flag)
		sem_post(ph->data->print);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_err(char *str)
{
	ft_putstr_fd(str, 1);
	exit(0);
}
