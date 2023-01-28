/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharutyu <mharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:29:20 by mharutyu          #+#    #+#             */
/*   Updated: 2023/01/28 17:32:41 by mharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nmb_of_philo;
	int				t_eat;
	int				t_die;
	int				t_sleep;
	int				nmb_of_each_philo_eat;
	int				ind_struct;
	int				count_eat;
	int				died;
	size_t			last_ate_time;
	long int		time;
	unsigned long	start_time;
	pthread_t		thread;
	pthread_mutex_t	*print;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_right;
}				t_data;

size_t	get_time(void);
int		ft_atoi(const char *str);
int		init_mutex(t_data *info);
int		is_died(t_data *info, char **argv);
void	timer(size_t tm);
void	putting_down_forks(t_data *info);
void	taking_forks(t_data *info);
void	print(t_data *info, int i);

#endif
