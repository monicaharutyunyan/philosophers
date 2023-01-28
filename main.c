/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mharutyu <mharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:31:56 by mharutyu          #+#    #+#             */
/*   Updated: 2023/01/28 17:33:22 by mharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	free_all(t_data *info)
{
	int	i;

	i = 0;
	if (info->print)
		free(info->print);
	while (i < info->nmb_of_philo)
	{
		pthread_mutex_destroy(&info->mutex[i]);
		i++;
	}
	if (info->mutex)
		free(info->mutex);
	if (info)
		free(info);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atoi(argv[i]) < 1)
		return (-1);
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				if (!(argv[i][j] == '-' || argv[i][j] == '+'))
				{
					printf("Error: Character in arguments!\n");
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

t_data	*fill_info(char **av)
{
	t_data	*info;
	int		i;

	i = 0;
	info = malloc(sizeof(t_data) * ft_atoi(av[1]));
	while (i < ft_atoi(av[1]))
	{
		info[i].nmb_of_philo = ft_atoi(av[1]);
		info[i].t_die = ft_atoi(av[2]);
		info[i].t_eat = ft_atoi(av[3]);
		info[i].t_sleep = ft_atoi(av[4]);
		if (av[5])
			info[i].nmb_of_each_philo_eat = ft_atoi(av[5]);
		else
			info[i].nmb_of_each_philo_eat = 0;
		++i;
	}
	return (info);
}

int	check_info(t_data *data, char **av)
{
	if (data->t_die < 1 || data->t_eat < 1
		|| data->t_sleep < 1 || data->nmb_of_philo < 1
		|| (av[5] && data->nmb_of_each_philo_eat < 0))
	{
		printf("Error: Only positive numbers allowed!\n");
		return (-1);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_data	*info;

	if (ac == 5 || ac == 6)
	{
		if (check_args(av) == -1)
			return (-1);
		info = fill_info(av);
		if (!check_info(info, av))
			return (-1);
		if (!init_mutex(info))
		{
			free_all(info);
			return (-1);
		}
		if (!is_died(info,av))
		{
			free_all(info);
			return (-1);
		}
	}
	else
		printf("Error: More or less arguments!");
	return (0);
}
