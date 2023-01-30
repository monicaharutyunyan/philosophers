/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharutyu <mharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:19:01 by mharutyu          #+#    #+#             */
/*   Updated: 2023/01/30 16:55:37 by mharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_6(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nmb_of_philo)
	{
		if (info[i].count_eat >= info[i].nmb_of_each_philo_eat)
			info[i].died = -1;
		i++;
	}
	i = 0;
	while (i < info->nmb_of_philo)
	{
		if (info[i].died == -1)
			i++;
		else
			return (0);
	}
	return (-1);
}

int	check_died(t_data *info)
{
	size_t	tm;

	tm = get_time();
	tm -= info->last_ate_time;
	if (tm >= (size_t)info->t_die)
		return (-1);
	return (0);
}

int	is_died(t_data *info, char **argv)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->nmb_of_philo)
		{
			if (argv[5] && check_arg_6(info) == -1)
			{
				print(info, 4);
				return (-3);
			}
			if (check_died(&info[i]) == -1)
			{
				print(&info[i], 5);
				return (-1);
			}
			i++;
		}
	}
	return (0);
}

size_t	time_thread(t_data *info)
{
	struct timeval	tm;

	gettimeofday(&tm, 0);
	tm.tv_sec *= 1000;
	tm.tv_usec /= 1000;
	info->time = (tm.tv_sec + tm.tv_usec) - info->start_time;
	return (info->time);
}

void	print(t_data *info, int i)
{
	pthread_mutex_lock(info->print);
	time_thread(info);
	if (i == 5)
		printf("%ld:\tPhilosopher %d\t is died ☠️\n", \
				info->time, info->ind_struct);
	if (i == 0)
		printf("%ld:\tPhilosopher %d\t has taken a fork 🍴\n", \
				info->time, info->ind_struct);
	else if (i == 1)
		printf("%ld:\tPhilosopher %d\t is eating 🍽\n", \
				info->time, info->ind_struct);
	else if (i == 2)
		printf("%ld:\tPhilosopher %d\t is sleeping 😴\n", \
				info->time, info->ind_struct);
	else if (i == 3)
		printf("%ld:\tPhilosopher %d\t is thinking 🤔\n", \
				info->time, info->ind_struct);
	else if (i == 4)
	{
		printf("%ld:\t all ate %d times\n", info->time,
			info->nmb_of_each_philo_eat);
		return ;
	}
	pthread_mutex_unlock(info->print);
}
