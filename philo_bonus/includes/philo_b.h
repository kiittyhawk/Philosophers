/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:22:00 by jgyles            #+#    #+#             */
/*   Updated: 2021/12/06 18:43:14 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_B_H
# define PHILO_B_H

# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

# define ERROR_DATA		"Wrong arguments\n"
# define ERROR_COUNT	"Invalid number of arguments\n"
# define ERROR			"Error\n"
# define LEFT_FORK		"has taken LEFT fork\n"
# define RIGHT_FORK		"has taken RIGHT fork\n"
# define EAT			"\x1b[0;33mis eating\x1b[0m\n"
# define DIED			"\x1b[1;31mdied\x1b[0m\n"
# define SLEEP			"is sleeping\n"
# define THINK			"is thinking\n"

typedef struct s_philo
{
	int				id;
	int				count_eat;
	pid_t			pid;
	int				flag;
	uint64_t		last_eat;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat;
	uint64_t		first_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*mute;
}				t_data;

int			init(char **argv, t_data *data);
void		print_err(char *str);
uint64_t	get_time(void);
uint64_t	current_time(uint64_t now, uint64_t start);
void		echo(int flag, char *str, uint64_t time, t_philo *ph);
void		philo(t_data *data);
int			ft_atoi(const char *str);
void		free_threads(pthread_t **treads, t_data *data, int flag);
void		usleep_fixed(uint64_t time);
void		eating(t_philo *ph);
void		sleeping(t_philo *ph);
void		thinking(t_philo *ph);
void		kill_proc(t_philo *ph, int num);

#endif