/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharutyu <mharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 20:01:08 by mharutyu          #+#    #+#             */
/*   Updated: 2023/01/28 17:17:44 by mharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		if (num < -2147483648 || num > 2147483647)
			return (-1);
		i++;
	}
	return (num * neg);
}

size_t	get_time(void)
{
	struct timeval	tm;
	size_t			time;

	gettimeofday(&tm, 0);
	time = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	return (time);
}

void	taking_forks(t_data *info)
{
	pthread_mutex_lock(info->mutex_left);
	print(info, 0);
	pthread_mutex_lock(info->mutex_right);
	print(info, 0);
}

void	putting_down_forks(t_data *info)
{
	pthread_mutex_unlock(info->mutex_right);
	pthread_mutex_unlock(info->mutex_left);
}

void	timer(size_t tm)
{
	size_t	time;
	size_t	n_time;

	time = get_time();
	n_time = get_time();
	while ((n_time - time) < tm)
	{
		n_time = get_time();
		usleep(10);
	}
}
