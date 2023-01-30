/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monicaharutyunyan <monicaharutyunyan@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:42:59 by mharutyu          #+#    #+#             */
/*   Updated: 2023/01/30 15:31:29 by monicaharut      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_data	*info;

	info = data;
	info->last_ate_time = get_time();
	if (info->ind_struct % 2 == 0)
		usleep(100);
	while (1)
	{
		taking_forks(info);
		info->count_eat++;
		print(info, 1);
		timer(info->t_eat);
		info->last_ate_time = get_time();
		putting_down_forks(info);
		print(info, 2);
		timer(info->t_sleep);
		print(info, 3);
	}
	return (0);
}

int	init_threads(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nmb_of_philo)
	{
		info[i].print = info[0].print;
		info[i].start_time = get_time();
		if ((pthread_create(&info[i].thread, 0, &routine, &info[i])) == -1)
		{
			printf("Error: Threads didn't creat!");
			return (-1);
		}
		pthread_detach(info[i].thread);
		i++;
	}
	usleep(10);
	return (0);
}

int	init_mutex(t_data *info)
{
	int	i;

	i = 0;
	info->print = malloc(sizeof(pthread_mutex_t));
	info->mutex = malloc(sizeof(pthread_mutex_t) * info->nmb_of_philo);
	pthread_mutex_init(info->print, NULL);
	while (i < info[0].nmb_of_philo)
	{
		pthread_mutex_init(&info->mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < info[0].nmb_of_philo)
	{
		if (info[0].nmb_of_philo == (i + 1))
			info[i].mutex_left = &info->mutex[0];
		else
			info[i].mutex_left = &info->mutex[i + 1];
		info[i].mutex_right = &info->mutex[i];
		i++;
	}
	if (init_threads(info) == -1)
		return (-1);
	return (0);
}
