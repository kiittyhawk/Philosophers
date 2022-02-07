/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:11:15 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/06 18:43:07 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	kill_proc(t_philo *ph, int num)
{
	while (num > 0)
	{
		kill(ph[num - 1].pid, SIGHUP);
		num--;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (init(argv, &data))
			philo(&data);
	}
	else
		print_err(ERROR_COUNT);
}
