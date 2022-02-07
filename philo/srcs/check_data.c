/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:54:37 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/08 13:31:22 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

int	is_number(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (ft_atoi(num));
}

int	init(char **argv, t_data *data)
{
	data->number_of_philosophers = is_number(argv[1]);
	data->time_to_die = is_number(argv[2]);
	data->time_to_eat = is_number(argv[3]);
	data->time_to_sleep = is_number(argv[4]);
	if (argv[5])
		data->must_eat = is_number(argv[5]);
	else
		data->must_eat = -1;
	if (data->number_of_philosophers == 0 || data->must_eat == 0
		|| data->number_of_philosophers > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		print_err(ERROR_DATA);
	return (1);
}
